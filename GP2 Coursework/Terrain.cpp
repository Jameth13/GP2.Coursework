#include "Terrain.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

Terrain::Terrain() {}
Terrain::~Terrain() {}

void Terrain::Awake()
{
}

void Terrain::Start()
{
	AddComponent(new Transform());
	AddComponent(new Mesh());
	AddComponent(new Texture());
	AddComponent(new Shader());

	GetComponent<Shader>()->Load("..//Resources//Shaders//Lighting");
	GetComponent<Mesh>()->loadModel("..//Resources//Terrain.obj");
	GetComponent<Texture>()->Load("..//Resources//Grass.jpg");

	GetComponent<Transform>()->SetPos(Vector3(0.0f, -30.0f, 0.0f));
	GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 2.0f));
}


void Terrain::Update()
{
	GetComponent<Shader>()->Bind();
	GetComponent<Shader>()->UpdateShader();
	GetComponent<Texture>()->Bind(0);
	GetComponent<Mesh>()->draw();
}
