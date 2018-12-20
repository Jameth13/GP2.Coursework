#include "MainGame.h"
#include <iostream>
#include <string>
#include "Time.h"
#include "Vector3.h"
//Components
#include "CameraComponent.h"
#include "UserControl.h"
#include "Transform.h"
#include "Mesh.h"
#include "Demo.h"

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
}

MainGame::~MainGame() {}

void MainGame::Run()
{
	InitSystems();
	MainLoop();
}

void MainGame::InitSystems()
{
	_gameDisplay.initDisplay();

	//Audio Manager
	audioMan->LoadSound("..//Resources//Background.wav", "BackgroundMusic");
	audioMan->PlaySound("BackgroundMusic");

	//Cameras
	camera1->GetComponent<CameraComponent>()->Init(70.0f, (float)_gameDisplay.getWidth() / (float)_gameDisplay.getHeight(), 0.01f, 1000.0f);
	camera1->GetComponent<Transform>()->SetPos(Vector3(8.0f, 2.0f, 12.0f));
	camera1->GetComponent<Transform>()->RotateGlobal(Vector3(0.0f, -140.0f, 0.0f));
	
	camera2->GetComponent<CameraComponent>()->Init(70.0f, (float)_gameDisplay.getWidth() / (float)_gameDisplay.getHeight(), 0.01f, 1000.0f);
	camera2->GetComponent<Transform>()->SetPos(Vector3(-8.0f, 2.0f, 12.0f));
	camera2->GetComponent<Transform>()->RotateGlobal(Vector3(0.0f, 140.0f, 0.0f));
	camera2->tag = "";
	camera2->GetComponent<UserControl>()->enabled = false;

	//Monkeys
	monkey1->tag = "monkey1";
	monkey1->GetComponent<Transform>()->SetPos(Vector3(-5.0f, 0.0f, 0.0f));
	monkey2->tag = "monkey2";
	monkey2->GetComponent<Transform>()->SetPos(Vector3(5.0f, 0.0f, 0.0f));
	monkey3->tag = "monkey3";
	monkey3->GetComponent<Transform>()->SetPos(Vector3(0.5f, 5.0f, 0.0f));
	monkey3->AddComponent(new Demo);

	//Light
	light->GetComponent<Transform>()->SetPos(Vector3(0.0f, 4.0f, 8.0f));
	light->GetComponent<UserControl>()->enabled = false;
}

void MainGame::MainLoop()
{
	while (_gameState != GameState::EXIT)
	{
		//Update delta time.
		Time::Update();

		//Clear display.
		_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);

		//Update managers
		colMan->Update();
		input->Update(&_gameDisplay, &_gameState);
		goMan->Update();
		
		//Toggle cameras.
		ToggleControl();

		//Use double buffering.
		_gameDisplay.swapBuffer();
	}
}

//Swap control between the two cameras and the light source.
void MainGame::ToggleControl()
{
	//Use C to toggle between cameras.
	if (input->GetKeyToggle(SDLK_c))
	{
		camera1->tag = "";
		camera1->GetComponent<UserControl>()->enabled = false;
		camera2->tag = "MainCamera";
		camera2->GetComponent<UserControl>()->enabled = true;
	}
	else
	{
		camera1->tag = "MainCamera";
		camera1->GetComponent<UserControl>()->enabled = true;
		camera2->tag = "";
		camera2->GetComponent<UserControl>()->enabled = false;
	}

	//Control light while right-click held.
	if (input->GetMouseButton(SDL_BUTTON_RIGHT))
	{
		light->GetComponent<UserControl>()->enabled = true;
		camera1->GetComponent<UserControl>()->enabled = false;
		camera2->GetComponent<UserControl>()->enabled = false;
	}
	else
		light->GetComponent<UserControl>()->enabled = false;

}
