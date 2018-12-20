#pragma once
#include <map>
#include <string>
#include <GL/glew.h>

class AssetManager
{
private:
	//Private constructor, this prevents creating an instance.
	AssetManager();

	//Static pointer
	static AssetManager* instance;

public:
	~AssetManager();

	std::map<std::string, GLuint> vaos;
	std::map<std::string, unsigned int> drawCounts;
	std::map<std::string, GLuint> textures;
	std::map<std::string, unsigned int> sounds;

	//Static method to get pointer
	static AssetManager* GetInstance();
};
