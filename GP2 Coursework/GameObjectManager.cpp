#include "GameObject.h"
#include "GameObjectManager.h"
#include <iostream>

GameObjectManager::GameObjectManager() {}
GameObjectManager::~GameObjectManager() {}

GameObjectManager* GameObjectManager::instance = 0;

GameObjectManager* GameObjectManager::GetInstance()
{
	//Return instance, create an instance if we don't already have one.
	if (instance == 0)
		instance = new GameObjectManager();

	return instance;
}

void GameObjectManager::Delete(GameObject* go)
{
	go->toDelete = true;
}

void GameObjectManager::Update()
{
	std::list<GameObject*>::iterator it;

	for (it = gameObjects.begin(); it != gameObjects.end(); it++)
	{	
		//Update all game objects that are not scheduled to be deleted
		if (!(*it)->toDelete)
			(*it)->UpdateAll();
			//Since 'it' is an iterator to a pointer to a GameObject, we must dereference with (*it)->
			
	}

	//We must loop through the list a second time to delete, this ensures that all other objects can have their updates called before game objects are deleted.
	for (it = gameObjects.begin(); it != gameObjects.end(); )
	{
		if ((*it)->toDelete)
		{
			delete *it;
			it = gameObjects.erase(it);
		}
		else it++;
	}
}
