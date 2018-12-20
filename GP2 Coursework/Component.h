#pragma once
#include <string>

//Resolve circular dependency with forward declaration.
class GameObject;

class Component
{
public:
	Component();
	//Virtual destructor so inherited class' destructor is called.
	virtual ~Component();

	std::string type;
	GameObject* gameObject;

	virtual void Start() = 0;
	virtual void Update() = 0;

	bool enabled = true;
};
