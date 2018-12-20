#include "ReindeerGirl.h"
#include <iostream>

ReindeerGirl::ReindeerGirl()
{
}

ReindeerGirl::~ReindeerGirl()
{
}

void ReindeerGirl::Start()
{
	std::cout << "Reindeer Girl born!" << std::endl;
	//mesh.loadModel("..//Resources//ReindeerGirl.obj");
	//texture.Load("..//Resources//default.jpg");
	//shader.Load("..//Resources//shader");
}


void ReindeerGirl::Update()
{
	std::cout << "Reindeer Girl still kicking!" << std::endl;

	counter += 0.01f;
	//transform.SetPos(glm::vec3(0.0, 0.0, sinf(counter) * 5));
	//transform.SetRot(glm::vec3(0.0, counter * 2, 3.14));
}
