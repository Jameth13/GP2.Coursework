#pragma once
#include "GameObject.h"

class Monkey : public GameObject
{
public:
	Monkey(std::string texture);
	~Monkey();

	void Awake();
	void Start();
	void Update();

private:
	std::string texName;
};
