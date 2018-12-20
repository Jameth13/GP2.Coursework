#include "GameObject.h"
#include "GameObjectManager.h"
#include "Component.h"
#include <iostream>
#include <vector>


GameObject::GameObject() {}

GameObject::~GameObject()
{
	std::list<Component*>::iterator it;
	for (it = components.begin(); it != components.end(); it++)
		delete *it;
}

void GameObject::AddComponent(Component* c)
{
	c->type = typeid(*c).name();
	components.push_back(c);
	componentsStart.push_back(c);
	c->gameObject = this;
}

void GameObject::RemoveComponent(Component* c)
{
	std::list<Component*>::iterator it;
	Component* del = nullptr;

	//Components
	for (it = components.begin(); it != components.end(); )
	{
		if ((*it)->type == typeid(*c).name())
		{
			del = *it;
			it = components.erase(it);
		}
		else it++;
	}

	//ComponentsStart
	for (it = componentsStart.begin(); it != componentsStart.end(); )
	{
		if ((*it)->type == typeid(*c).name())
		{
			del = *it;
			it = componentsStart.erase(it);
		}
		else it++;
	}

	if (del != nullptr)
		delete del;
}

//Calls the Start() and Update() of both the game object and its components.
void GameObject::UpdateAll()
{
	UpdateGameObject();
	UpdateComponents();
}

void GameObject::UpdateGameObject()
{
	if (!startCalled)
	{
		startCalled = true;
		Start();
	}
	Update();
}

void GameObject::UpdateComponents()
{
	std::list<Component*>::iterator it;
	//Start
	for (it = componentsStart.begin(); it != componentsStart.end(); )
	{
		if ((*it)->enabled == true)
		{
			(*it)->Start();
			it = componentsStart.erase(it);
		}
		else
			it++;
	}
	//Update
	for (it = components.begin(); it != components.end(); it++)
	{
		if ((*it)->enabled == true)
			(*it)->Update();
	}

}
