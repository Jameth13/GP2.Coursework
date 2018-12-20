#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include <map>
#include "obj_loader.h"
#include "Component.h"
#include "AssetManager.h"

class Mesh : public Component
{
public:
	Mesh();
	~Mesh();

	void draw();
	void loadModel(const std::string& filename);
	void initModel(const IndexedModel& model, const std::string& filename);

	void Start();
	void Update();

private:
	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS]; // create our array of buffers
	unsigned int drawCount; //how much of the vertexArrayObject do we want to draw

	AssetManager* assetMan = AssetManager::GetInstance();
};
