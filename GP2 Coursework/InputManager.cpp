#include "InputManager.h"
#include <iostream>

InputManager* InputManager::instance = 0;

InputManager* InputManager::GetInstance()
{
	//Return instance, create an instance if we don't already have one.
	if (instance == 0)
		instance = new InputManager();

	return instance;
}

InputManager::InputManager() {}
InputManager::~InputManager() {}


void InputManager::Update(Display* display, GameState* gameState)
{
	mouseX = 0.0f;
	mouseY = 0.0f;
	keysDown.clear();
	mouseButtonsDown.clear();

	SDL_Event evnt;

	while (SDL_PollEvent(&evnt))
	{
		if (evnt.type == SDL_QUIT)
		{
			*gameState = GameState::EXIT;
		}

		switch (evnt.type)
		{
		case SDL_MOUSEMOTION:
			if (cursorLocked)
			{
				mouseX = (float)(evnt.motion.x - display->getWidth() / 2);
				mouseY = (float)(evnt.motion.y - display->getHeight() / 2);
			}
			else
			{
				mouseX = (float)evnt.motion.xrel;
				mouseY = (float)evnt.motion.yrel;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			AddMouseButton(evnt.button.button);
			if (evnt.button.button == SDL_BUTTON_LEFT)
				LockCursor(true);
			break;

		case SDL_MOUSEBUTTONUP:
			RemoveMouseButton(evnt.button.button);
			break;

		case SDL_KEYDOWN:
			AddKey(evnt.key.keysym.sym);
			if (evnt.key.keysym.sym == SDLK_ESCAPE)
				LockCursor(false);
			break;

		case SDL_KEYUP:
			RemoveKey(evnt.key.keysym.sym);
			break;
		}
	}

	//Potential issue! Different systems react differently to this function.
	if (cursorLocked)
		SDL_WarpMouseInWindow(display->GetWindow(), display->getWidth() / 2, display->getHeight() / 2);

}

bool InputManager::GetKey(SDL_Keycode key)
{
	std::list<SDL_Keycode>::iterator it;
	for (it = keys.begin(); it != keys.end(); it++)
	{
		if (*it == key)
			return true;
	}
	return false;
}

bool InputManager::GetKeyDown(SDL_Keycode key)
{
	std::list<SDL_Keycode>::iterator it;
	for (it = keysDown.begin(); it != keysDown.end(); it++)
	{
		if (*it == key)
			return true;
	}
	return false;
}

bool InputManager::GetKeyToggle(SDL_Keycode key)
{
	std::list<SDL_Keycode>::iterator it;
	for (it = keysToggle.begin(); it != keysToggle.end(); it++)
	{
		if (*it == key)
			return true;
	}
	return false;
}

float InputManager::GetMouseX()
{
	return mouseX;
}

float InputManager::GetMouseY()
{
	return mouseY;
}

bool InputManager::GetMouseButton(unsigned int button)
{
	std::list<unsigned int>::iterator it;
	for (it = mouseButtons.begin(); it != mouseButtons.end(); it++)
	{
		if (*it == button)
			return true;
	}
	return false;
}

bool InputManager::GetMouseButtonDown(unsigned int button)
{
	std::list<unsigned int>::iterator it;
	for (it = mouseButtonsDown.begin(); it != mouseButtonsDown.end(); it++)
	{
		if (*it == button)
			return true;
	}
	return false;
}


void InputManager::AddKey(SDL_Keycode key)
{
	std::list<SDL_Keycode>::iterator it;
	for (it = keys.begin(); it != keys.end(); it++)
	{
		if (*it == key)
			return;
	}
	keys.push_back(key);
	keysDown.push_back(key);

	//Update list of toggled keys.
	std::list<SDL_Keycode>::iterator itDown;
	for (itDown = keysDown.begin(); itDown != keysDown.end(); itDown++)
	{
		if (std::find(keysToggle.begin(), keysToggle.end(), *itDown) != keysToggle.end())
			keysToggle.remove(*itDown);
		else
			keysToggle.push_back(*itDown);
	}
}

void InputManager::RemoveKey(SDL_Keycode key)
{
	std::list<SDL_Keycode>::iterator it;
	for (it = keys.begin(); it != keys.end();)
	{
		if (*it == key)
			it = keys.erase(it);
		else it++;
	}
}


void InputManager::AddMouseButton(unsigned int button)
{
	std::list<unsigned int>::iterator it;
	for (it = mouseButtons.begin(); it != mouseButtons.end(); it++)
	{
		if (*it == button)
			return;
	}
	mouseButtons.push_back(button);
	mouseButtonsDown.push_back(button);
}

void InputManager::RemoveMouseButton(unsigned int button)
{
	std::list<unsigned int>::iterator it;
	for (it = mouseButtons.begin(); it != mouseButtons.end();)
	{
		if (*it == button)
			it = mouseButtons.erase(it);
		else it++;
	}
}


void InputManager::LockCursor(bool lock)
{
	if (lock)
	{
		cursorLocked = true;
		SDL_ShowCursor(SDL_DISABLE);
	}
	else
	{
		cursorLocked = false;
		SDL_ShowCursor(SDL_ENABLE);
	}
}

void InputManager::print()
{
	std::list<SDL_Keycode>::iterator it;

	for (it = keys.begin(); it != keys.end(); it++)
	{
		std::cout << *it << ", ";
	}
	std::cout << std::endl;
}
