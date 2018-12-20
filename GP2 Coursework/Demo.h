#pragma once
#include "Component.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"
#include "Monkey.h"


class Demo : public Component
{
public:
	Demo();
	~Demo();

	void Start();
	void Update();
	void MakeMonkey1();
	void MakeMonkey2();

	GameObjectManager* goMan = GameObjectManager::GetInstance();
	CollisionManager* colMan = CollisionManager::GetInstance();

	Monkey* monkey1;
	Monkey* monkey2;
};
