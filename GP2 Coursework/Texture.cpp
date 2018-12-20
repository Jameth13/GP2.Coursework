#include "Texture.h"
#include "stb_image.h"
#include <iostream>
#include <cassert>

Texture::Texture() {}
Texture::~Texture()
{
	//Can't delete textures as other objects may be using it.
	//If I had more time, I would code the asset manager to delete textures once no objects are using them.
	//glDeleteTextures(1, &textureHandler); // number of and address of textures
}

void Texture::Start() {}
void Texture::Update() {}


void Texture::Load()
{
	const std::string& defaulTexture = "..//Resources//default.jpg";

	int width, height, numComponents;

	if (vaoMan->textures.count(defaulTexture) > 0)
	{
		textureHandler = vaoMan->textures[defaulTexture];
	}
	else
	{
		tempHold = defaulTexture;
		unsigned char* imageData = stbi_load((defaulTexture).c_str(), &width, &height, &numComponents, 4);
		Init(width, height, imageData);
	}
}

void Texture::Load(const std::string& fileName)
{
	const std::string& missingTexture = "..//Resources//missingtexture.jpg";

	int width, height, numComponents;
	unsigned char* imageData = NULL;

	if (vaoMan->textures.count(fileName) > 0)
	{
		textureHandler = vaoMan->textures[fileName];
		//Return to skip null imageData check.
		return;
	}
	else
	{
		tempHold = fileName;
		imageData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);
		Init(width, height, imageData);
	}

	//Missing texture
	if (imageData == NULL)
	{
		std::cout << "Failed to load texture: " << fileName << std::endl;
		std::cout << "Using missing texture." << std::endl;
		imageData = stbi_load((missingTexture).c_str(), &width, &height, &numComponents, 4);
		Init(width, height, imageData);
	}
}

void Texture::Init(int width, int height, unsigned char* imageData)
{
	glGenTextures(1, &textureHandler); //number of and address of textures
	glBindTexture(GL_TEXTURE_2D, textureHandler); //bind texture - define type

	vaoMan->textures[tempHold] = textureHandler;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // wrap texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // wrap texture outside height

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // linear filtering for minification (texture is smaller than area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // linear filtering for magnifcation (texture is larger)

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData); //Target, Mipmapping Level, Pixel Format, Width, Height, Border Size, Input Format, Data Type of Texture, Image Data

	stbi_image_free(imageData);
}


void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31); /// check we are working with one of the 32 textures

	glActiveTexture(GL_TEXTURE0 + unit); //set acitve texture unit
	glBindTexture(GL_TEXTURE_2D, textureHandler); //type of and texture to bind to unit
}
