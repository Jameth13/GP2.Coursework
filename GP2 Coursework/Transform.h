#pragma once
#include <glm/glm.hpp>
#include "Component.h"
#include "Vector3.h"
#include "Quaternion.h"


class Transform : public Component
{
private:
	Vector3 pos;
	Vector3 scale;
	Vector3 eulerAngles;
	Quaternion quaternion;


public:
	Transform();
	Transform(Vector3 pos, Vector3 scale, Vector3 rot);
	Transform(Vector3 pos, Vector3 scale, Quaternion quaternion);

	void Start();
	void Update();

	glm::mat4 GetModelMatrix();

	Vector3 GetPos();
	Vector3 GetScale();
	Vector3 GetEulerAngles();
	Quaternion GetRotation();

	void SetPos(Vector3 pos);
	void SetScale(Vector3 scale);
	void SetRotate(Vector3 eulerAngles);
	void SetRotate(Quaternion q);
	
	void TranslateLocal(Vector3 pos);
	void TranslateGlobal(Vector3 pos);
	void RotateLocal(Vector3 eulerAngles);
	void RotateGlobal(Vector3 eulerAngles);

	Vector3 GetForward();
	Vector3 GetUp();
	Vector3 GetRight();
};
