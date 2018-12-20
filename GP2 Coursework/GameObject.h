#pragma once
#include <list>
#include <string>
#include <typeinfo>

//Resolve circular dependency with forward declaration.
class Component;

class GameObject
{
private:
	std::list<Component*> components;
	std::list<Component*> componentsStart;
	void UpdateGameObject();
	void UpdateComponents();
	bool startCalled;


public:
	GameObject();
	//Virtual destructor so inherited class' destructor is called.
	virtual ~GameObject();
	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;

	void AddComponent(Component* c);
	void RemoveComponent(Component* c);

	//Method must be inline to prevent linker error.
	template <typename T>
	inline T* GetComponent()
	{
		std::string type = typeid(T).name();

		std::list<Component*>::iterator it;
		for (it = components.begin(); it != components.end(); it++)
		{
			if ((*it)->type == type)
				return (T*)*it;
		}
		throw std::invalid_argument("Game object does not have component: " + type);
	}


	//Calls the Start() and Update() of both the game object and its components.
	void UpdateAll();

	std::string tag = "untagged";
	bool toDelete = false;
};
