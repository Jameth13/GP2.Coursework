#pragma once
#include <glm\glm.hpp>
#include <list>
#include <iostream>
#include "Vector3.h"
#include "GameObject.h"
#include "Collider.h"

//Forward declerations
struct Sphere;
class Collider;

struct Collision
{
public:
	GameObject * objA;
	GameObject* objB;

	Collision(GameObject* objA, GameObject* objB)
	{
		this->objA = objA;
		this->objB = objB;
	}
	void Print()
	{
		std::cout << "Collision detected between objects: " + objA->tag + " & " + objB->tag << std::endl;
	}
};

class CollisionManager
{
private:
	//Private constructor, this prevents creating an instance.
	CollisionManager();
	//Static pointer
	static CollisionManager* instance;

	std::list<Collider*> colliders;
	std::list<Collision*> collisions;

	bool CheckCollision(Sphere* sphere1, Sphere* sphere2);


public:
	//Static method to get pointer
	static CollisionManager* GetInstance();
	~CollisionManager();

	void Add(Collider* collider);
	void Remove(Collider* collider);
	void Update();
	bool Check(GameObject* go);

	//Used for debugging.
	void PrintAll();
};
