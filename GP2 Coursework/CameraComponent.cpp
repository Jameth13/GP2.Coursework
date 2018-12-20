#include "CameraComponent.h"
#include "Transform.h"
#include "GameObject.h"


CameraComponent::CameraComponent() {}
CameraComponent::~CameraComponent() {}

void CameraComponent::Start() {}
void CameraComponent::Update() {}

void CameraComponent::Init(float fov, float aspect, float nearClip, float farClip)
{
	//Create projection matrix.
	this->projection = glm::perspective(fov, aspect, nearClip, farClip);
}


glm::mat4 CameraComponent::GetViewProjection()
{
	Transform* trans = gameObject->GetComponent<Transform>();
	//Projection Matrix multiplied by View Matrix.
	return projection * glm::lookAt(trans->GetPos().GLM(), trans->GetPos().GLM() + trans->GetForward().GLM(), trans->GetUp().GLM());
}
