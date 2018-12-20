#include "Demo.h"
#include "Transform.h"
#include "Time.h"
#include "GameObject.h"

Demo::Demo() {}
Demo::~Demo() {}

void Demo::Start()
{
	MakeMonkey1();
}

void Demo::Update()
{
	//Rotate object for demonstration.
	gameObject->GetComponent<Transform>()->SetPos(Vector3(glm::cos(Time::time) * 4.0f, glm::sin(Time::time) * 2.0f, 0.0f));

	//Continually delete and instantiate game objects to demonstrate the robust nature of the hierarchy.
	if (colMan->Check(monkey1))
	{
		goMan->Delete(monkey1);
		MakeMonkey2();
	}
	if (colMan->Check(monkey2))
	{
		goMan->Delete(monkey2);
		MakeMonkey1();
	}
}

void Demo::MakeMonkey1()
{
	monkey1 = goMan->Instantiate<Monkey>("..//Resources//Carpet.jpg");
	monkey1->GetComponent<Transform>()->SetPos(Vector3(0.0f, 2.0f, 0.0f));
}

void Demo::MakeMonkey2()
{
	monkey2 = goMan->Instantiate<Monkey>("..//Resources//Metal.jpg");
	monkey2->GetComponent<Transform>()->SetPos(Vector3(0.0f, -2.0f, 0.0f));
}
