#include "CollisionManager.h"

CollisionManager* CollisionManager::instance = 0;

CollisionManager* CollisionManager::GetInstance()
{
	//Return instance, create an instance if we don't already have one.
	if (instance == 0)
		instance = new CollisionManager();

	return instance;
}

CollisionManager::CollisionManager() {}
CollisionManager::~CollisionManager() {}


void CollisionManager::Update()
{
	collisions.clear();

	std::list<Collider*>::iterator it;
	std::list<Collider*>::iterator it2;

	for (it = colliders.begin(); it != colliders.end(); it++)
	{
		it2 = it;
		it2++;
		for (it2; it2 != colliders.end(); it2++)
		{
		if (it != it2)
			if (CheckCollision((*it)->sphere, (*it2)->sphere))
			{
				collisions.push_back(new Collision((*it)->gameObject, (*it2)->gameObject));
			}
		}
	}
}

//Add collider to list, called by Collider constructor.
void CollisionManager::Add(Collider* collider)
{
	colliders.push_back(collider);
}

//Remove collider from list, called by Collider destructor.
void CollisionManager::Remove(Collider* collider)
{
	std::list<Collider*>::iterator it;

	for (it = colliders.begin(); it != colliders.end(); )
	{
		if (*it == collider)
		{
			it = colliders.erase(it);
			return;
		}
		else it++;
	}
}

//Check if a game object is colliding.
bool CollisionManager::Check(GameObject* go)
{
	std::list<Collision*>::iterator it;

	for (it = collisions.begin(); it != collisions.end(); it++)
	{
		if ((*it)->objA == go || (*it)->objB == go)
			return true;
	}
	return false;
}

//Used for debugging: Print all collisions.
void CollisionManager::PrintAll()
{
	std::cout << "List of collisions:" << std::endl;

	std::list<Collision*>::iterator it;
	for (it = collisions.begin(); it != collisions.end(); it++)
	{
		(*it)->Print();
	}
	std::cout << std::endl;
}

//Check sphere and sphere collision.
bool CollisionManager::CheckCollision(Sphere* sphere1, Sphere* sphere2)
{
	Vector3 s1Pos = sphere1->GetPos();
	float s1Rad = sphere1->GetRadius();
	Vector3 s2Pos = sphere2->GetPos();
	float s2Rad = sphere2->GetRadius();

	float xs = (s1Pos.x - s2Pos.x) * (s1Pos.x - s2Pos.x);
	float ys = (s1Pos.y - s2Pos.y) * (s1Pos.y - s2Pos.y);
	float zs = (s1Pos.z - s2Pos.z) * (s1Pos.z - s2Pos.z);
	float sqDistance = xs + ys + zs;
	float sqRadii = (s1Rad + s2Rad) * (s1Rad + s2Rad);

	return sqDistance < sqRadii;
}