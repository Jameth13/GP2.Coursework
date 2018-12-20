#pragma once
#include <string>
#include <GL\glew.h>
#include "transform.h"
#include "Component.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"

class Shader : public Component
{
public:
	Shader();
	void Load(const std::string& filename);

	void Bind(); //Set gpu to use our shaders
	void UpdateShader();

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

	~Shader();

	void Start();
	void Update();

protected:
private:
	GameObjectManager * goMan = GameObjectManager::GetInstance();
	CollisionManager * colMan = CollisionManager::GetInstance();

	static const unsigned int NUM_SHADERS = 2; // number of shaders

	enum
	{
		VP,
		M,
		LightColor,
		LightPosition,

		NUM_UNIFORMS
	};

	GLuint program; // Track the shader program
	GLuint shaders[NUM_SHADERS]; //array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables
};
