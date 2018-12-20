#include <iostream>
#include <fstream>
#include "Shader.h"
#include "Camera.h"
#include "CameraComponent.h"
#include "Light.h"


Shader::Shader()
{
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(program, shaders[i]); //detach shader from program
		glDeleteShader(shaders[i]); //delete the sahders
	}
	glDeleteProgram(program); // delete the program
}

void Shader::Start() {}
void Shader::Update() {}

void Shader::Load(const std::string& filename)
{
	program = glCreateProgram(); // create shader program (openGL saves as ref number)
	shaders[0] = CreateShader(LoadShader(filename + ".vert"), GL_VERTEX_SHADER); // create vertex shader
	shaders[1] = CreateShader(LoadShader(filename + ".frag"), GL_FRAGMENT_SHADER); // create fragment shader

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(program, shaders[i]); //add all our shaders to the shader program "shaders" 
	}

	glBindAttribLocation(program, 0, "position"); // associate attribute variable with our shader program attribute (in this case attribute vec3 position;)
	glBindAttribLocation(program, 1, "texCoord");
	glBindAttribLocation(program, 2, "normal");

	glLinkProgram(program); //create executables that will run on the GPU shaders
	CheckShaderError(program, GL_LINK_STATUS, true, "Error: Shader program linking failed"); // cheack for error

	glValidateProgram(program); //check the entire program is valid
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	uniforms[VP] = glGetUniformLocation(program, "vp");
	uniforms[M] = glGetUniformLocation(program, "m");
	uniforms[LightColor] = glGetUniformLocation(program, "lightColor");
	uniforms[LightPosition] = glGetUniformLocation(program, "lightPosition");
}

void Shader::Bind()
{
	glUseProgram(program); //installs the program object specified by program as part of rendering state
}

void Shader::UpdateShader()
{
	Transform* transform = gameObject->GetComponent<Transform>();
	glm::mat4 vp = goMan->GetGameObjectTag<Camera>("MainCamera")->GetComponent<CameraComponent>()->GetViewProjection();
	glm::mat4 m = transform->GetModelMatrix();
	glUniformMatrix4fv(uniforms[VP], 1, GLU_FALSE, &vp[0][0]);
	glUniformMatrix4fv(uniforms[M], 1, GLU_FALSE, &m[0][0]);

	if (colMan->Check(gameObject))
		glUniform3fv(uniforms[LightColor], 1, &glm::vec3(1.0f, 0.0f, 0.0f)[0]);
	else
		glUniform3fv(uniforms[LightColor], 1, &glm::vec3(1.0f, 1.0f, 1.0f)[0]);

	glm::vec3 lightPosition = goMan->GetGameObjectTag<Light>("Light")->GetComponent<Transform>()->GetPos().GLM();

	glUniform3fv(uniforms[LightPosition], 1, &lightPosition[0]);
}


GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type); //create shader based on specified type

	if (shader == 0) //if == 0 shader no created
		std::cerr << "Error type creation failed " << type << std::endl;

	const GLchar* stringSource[1]; //convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, stringSource, lengths); //send source code to opengl
	glCompileShader(shader); //get open gl to compile shader code

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

	return shader;
}

std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

