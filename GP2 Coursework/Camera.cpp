#include "Camera.h"
#include "CameraComponent.h"
#include "UserControl.h"
#include "Transform.h"


Camera::Camera() {}
Camera::~Camera() {}

void Camera::Awake()
{
	tag = "MainCamera";
	AddComponent(new Transform());
	AddComponent(new CameraComponent());
	AddComponent(new UserControl());
}

void Camera::Start() {}
void Camera::Update() {}
