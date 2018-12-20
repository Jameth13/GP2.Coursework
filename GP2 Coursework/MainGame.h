#pragma once
//External Libraries
#include <SDL/SDL.h>
#include <GL/glew.h>
//Other
#include "Display.h"
#include "Enums.h"
//Managers
#include "AudioManager.h"
#include "GameObjectManager.h"
#include "InputManager.h"
#include "CollisionManager.h"
//GameObjects
#include "Monkey.h"
#include "Camera.h"
#include "Terrain.h"
#include "Light.h"


class MainGame
{
public:
	MainGame();
	~MainGame();

	void Run();

private:
	void InitSystems();
	void MainLoop();
	void ToggleControl();

	Display _gameDisplay;
	GameState _gameState;

	GameObjectManager* goMan = GameObjectManager::GetInstance();
	InputManager* input = InputManager::GetInstance();
	AudioManager* audioMan = AudioManager::GetInstance();
	CollisionManager* colMan = CollisionManager::GetInstance();

	Camera* camera1 = goMan->Instantiate<Camera>();
	Camera* camera2 = goMan->Instantiate<Camera>();

	Light* light = goMan->Instantiate<Light>();

	Monkey* monkey1 = goMan->Instantiate<Monkey>("..//Resources//Bricks.jpg");
	Monkey* monkey2 = goMan->Instantiate<Monkey>("..//Resources//Water.jpg");
	Monkey* monkey3 = goMan->Instantiate<Monkey>("..//Resources//notexture.jpg");	//Attempt to load a texture which does not exist.


	Terrain* terrain = goMan->Instantiate<Terrain>();
};
