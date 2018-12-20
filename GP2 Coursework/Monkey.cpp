#include "Monkey.h"
#include "Transform.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Collider.h"


Monkey::Monkey(std::string texture)
{
	texName = texture;
}

Monkey::~Monkey() {}

//Called once at initalisation of monkey.
void Monkey::Awake()
{
	//Attach components.
	AddComponent(new Transform());
	AddComponent(new Mesh());
	AddComponent(new Texture());
	AddComponent(new Shader());
	AddComponent(new Collider(1.1f));
}

//Called once at the start of next game loop.
void Monkey::Start()
{
	//Initalise components.
	GetComponent<Shader>()->Load("..//Resources//Shaders//Lighting");
	GetComponent<Mesh>()->loadModel("..//Resources//monkey.obj");
	GetComponent<Texture>()->Load(texName);
}

//Called every game loop.
void Monkey::Update()
{
	//Render monkey.
	GetComponent<Shader>()->Bind();
	GetComponent<Shader>()->UpdateShader();
	GetComponent<Texture>()->Bind(0);
	GetComponent<Mesh>()->draw();
}
