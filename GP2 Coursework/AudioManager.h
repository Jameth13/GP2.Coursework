#pragma once
#include <SDL\SDL.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <AL\al.h>
#include <AL\alc.h>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "AssetManager.h"

class AudioManager
{
public:
	//Static method to get pointer
	static AudioManager* GetInstance();
	~AudioManager();
	void LoadSound(const char* filename, const char* soundName);
	void DeleteSound(const char* soundName);
	void PlaySound(const char* soundName);
	void PlaySound(const char* soundName, glm::vec3& pos);
	void StopSound(const char* soundName);
	void SetListener(glm::vec3& pos, glm::vec3& camLookAt);

private:
	//Private constructor, this prevents creating an instance.
	AudioManager();
	//Static pointer
	static AudioManager* instance;

	AssetManager* assetMan = AssetManager::GetInstance();

	struct data {
		int sourceID, bufferID;
		char* buffer;
		std::string name;
		data(unsigned int sI, unsigned int bI, char* b, const char* n)
		{
			this->sourceID = sI;
			this->bufferID = bI;
			this->buffer = b;
			this->name = n;
		}

	};

	std::vector<data> datas;
	ALCcontext* context;
	ALCdevice *device;
	bool IsBigEndian();
	int ConvertToInt(char* buffer, int length);
	char* LoadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size);
};

