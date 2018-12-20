#pragma once
#include <list>

//Using this to avoid Circular Dependency and Incomplete Type errors between GameObject and GameObjectManager.
class GameObject;

class GameObjectManager
{
private:
	//Private constructor, this prevents creating an instance.
	GameObjectManager();

	//Static pointer
	static GameObjectManager* instance;

	std::list<GameObject*> gameObjects;

public:
	~GameObjectManager();
	//Static method to get pointer
	static GameObjectManager* GetInstance();

	void Delete(GameObject* go);
	void Update();


	template <typename T>
	T* Instantiate()
	{
		//Ensure T inherits from GameObject
		static_assert(std::is_base_of<GameObject, T>::value, "T must derive from GameObject");
		T* gameObject = new T();
		gameObjects.push_back(gameObject);
		gameObject->Awake();
		return gameObject;
	}

	//Allow instantiation of GameObjects with one parameter in their constructor. 
	template <typename T, typename T2>
	T* Instantiate(T2 parameter)
	{
		static_assert(std::is_base_of<GameObject, T>::value, "T must derive from GameObject");
		T* gameObject = new T(parameter);
		gameObjects.push_back(gameObject);
		gameObject->Awake();
		return gameObject;
	}

	//Find game objects by tag.
	template <typename T>
	T* GetGameObjectTag(std::string tag)
	{
		std::list<GameObject*>::iterator it;

		for (it = gameObjects.begin(); it != gameObjects.end(); it++)
		{
			if ((*it)->tag == tag)
				return (T*)*it;
		}
		throw std::invalid_argument("No game object found with tag: " + tag);
	}

};
