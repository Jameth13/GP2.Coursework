#include "Light.h"
#include "Transform.h"
#include "Mesh.h"
#include "Shader.h"
#include "UserControl.h"
#include "Texture.h"

Light::Light() {}
Light::~Light() {}

void Light::Awake()
{
	tag = "Light";

	Transform* trans = new Transform();
	trans->SetScale(Vector3(0.3f, 0.3f, 0.2f));
	AddComponent(trans);
	AddComponent(new Mesh());
	AddComponent(new Texture());
	AddComponent(new Shader());
	AddComponent(new UserControl());
}

void Light::Start()
{
	GetComponent<Shader>()->Load("..//Resources//Shaders//Light");
	GetComponent<Mesh>()->loadModel("..//Resources//Arrow.obj");
	GetComponent<Texture>()->Load("..//Resources//Glass.jpg");
}


void Light::Update()
{
	GetComponent<Shader>()->Bind();
	GetComponent<Shader>()->UpdateShader();
	GetComponent<Texture>()->Bind(0);
	GetComponent<Mesh>()->draw();
}
