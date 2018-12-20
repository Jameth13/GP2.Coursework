#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class Display
{
public:
	Display();
	~Display();
	void initDisplay();
	void swapBuffer();
	void clearDisplay(float r, float g, float b, float a);

	int getWidth();
	int getHeight();

	SDL_Window* GetWindow();

private:

	void returnError(std::string errorString);

	SDL_GLContext glContext; //global variable to hold the context
	SDL_Window* sdlWindow; //holds pointer to out window
	int screenWidth, screenHeight;
};
