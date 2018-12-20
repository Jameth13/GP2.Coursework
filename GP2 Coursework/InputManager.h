#pragma once
#include <SDL\SDL.h>
#include <list>
#include "Display.h"
#include "Enums.h"

class InputManager
{
public:
	~InputManager();
	//Static method to get pointer
	static InputManager* GetInstance();

	void Update(Display* display, GameState* gameState);

	//Keyboard
	bool GetKey(SDL_Keycode key);			//Returns true while key is pressed.
	bool GetKeyDown(SDL_Keycode key);		//Returns true on first frame key is pressed.
	bool GetKeyToggle(SDL_Keycode key);		//Flip-flop each time key is pressed.

	//Mouse
	float GetMouseX();
	float GetMouseY();
	bool GetMouseButton(unsigned int button);
	bool GetMouseButtonDown(unsigned int button);

	//Used for debugging.
	void print();

private:
	//Private constructor, this prevents creating an instance.
	InputManager();

	//Static pointer
	static InputManager* instance;

	//Keyboard
	std::list<SDL_Keycode> keys;
	std::list<SDL_Keycode> keysDown;
	std::list<SDL_Keycode> keysToggle;

	void AddKey(SDL_Keycode key);
	void RemoveKey(SDL_Keycode key);

	//Mouse
	float mouseX, mouseY;
	std::list<unsigned int> mouseButtons;
	std::list<unsigned int> mouseButtonsDown;

	void AddMouseButton(unsigned int button);
	void RemoveMouseButton(unsigned int button);

	bool cursorLocked;
	void LockCursor(bool lock);

};
