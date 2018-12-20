#include <string>
#include <GL\glew.h>
#include "Component.h"
#include "AssetManager.h"

class Texture : public Component
{
public:
	Texture();
	void Load();
	void Load(const std::string& fileName);
	void Init(int width, int height, unsigned char* imageData);

	void Bind(unsigned int unit); // bind upto 32 textures

	void Start();
	void Update();

	~Texture();

protected:
private:

	AssetManager* vaoMan = AssetManager::GetInstance();
	GLuint textureHandler;

	std::string tempHold = "";
};
