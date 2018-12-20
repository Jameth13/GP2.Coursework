#pragma once
#include "Component.h"
#include "Vector3.h"

class CollisionManager;

struct Sphere
{
private:
	Vector3 position;
	float radius;

public:
	Sphere()
	{
		position = Vector3();
		radius = 0.0f;
	}
	Sphere(Vector3 position, float radius)
	{
		this->position = position;
		this->radius = radius;
	}

	Vector3 GetPos() { return position; }
	float GetRadius() { return radius; }

	void Update(Vector3 position, float radius)
	{
		this->position = position;
		this->radius = radius;
	}
	void Update(Vector3 position)
	{
		this->position = position;
	}
	void Update(float radius)
	{
		this->radius = radius;
	}
};

class Collider : public Component
{
public:
	Collider(float radius);
	~Collider();

	CollisionManager* colMan;
	Sphere* sphere = new Sphere();

	void Start();
	void Update();
};
