#include "Transform.h"
#include <iostream>


Transform::Transform()
{
	this->pos = Vector3();
	this->scale = Vector3(1.0f, 1.0f, 1.0f);
	this->eulerAngles = Vector3();
	this->quaternion = Quaternion();
}

Transform::Transform(Vector3 pos, Vector3 scale, Vector3 eulerAngles)
{
	this->pos = pos;
	this->scale = scale;
	Vector3 eulerAnglesRadians = eulerAngles.toRadians();
	this->eulerAngles = eulerAnglesRadians;
	this->quaternion = Quaternion::toQuaternion(eulerAnglesRadians);
}

Transform::Transform(Vector3 pos, Vector3 scale, Quaternion quaternion)
{
	this->pos = pos;
	this->scale = scale;
	this->quaternion = quaternion;
	this->eulerAngles = Quaternion::toEulerAngle(quaternion);
}


void Transform::Start() {}
void Transform::Update() {}


//Model matrix
glm::mat4 Transform::GetModelMatrix()
{
	glm::mat4 posMat = pos.TransMat();
	glm::mat4 scaleMat = scale.ScaleMat();
	glm::mat4 rotMat = Quaternion::toRotationMatrix(quaternion);

	return posMat * rotMat * scaleMat;
}


//Getters
Vector3 Transform::GetPos()			{ return pos; }
Vector3 Transform::GetScale()		{ return scale; }
Vector3 Transform::GetEulerAngles() { return eulerAngles.toDegrees(); }
Quaternion Transform::GetRotation() { return quaternion; }


//Setters
void Transform::SetPos(Vector3 pos)		{ this->pos = pos; }
void Transform::SetScale(Vector3 scale)	{ this->scale = scale; }

void Transform::SetRotate(Vector3 eulerAngles)
{
	Vector3 radians = eulerAngles.toRadians();
	this->quaternion = Quaternion::toQuaternion(radians);
	this->eulerAngles = Quaternion::toEulerAngle(this->quaternion);
}
void Transform::SetRotate(Quaternion q)
{
	this->quaternion = q;
	this->eulerAngles = Quaternion::toEulerAngle(this->quaternion);
}


//Translate
void Transform::TranslateLocal(Vector3 pos)
{
	glm::vec4 v4 = Quaternion::toRotationMatrix(quaternion) * glm::vec4(pos.x, pos.y, pos.z, 0.0f);
	this->pos += Vector3(v4.x, v4.y, v4.z);
}
void Transform::TranslateGlobal(Vector3 pos)
{
	this->pos += pos;
}


//Rotate
void Transform::RotateLocal(Vector3 eulerAngles)
{
	Quaternion q = Quaternion::toQuaternion(eulerAngles.toRadians());
	this->quaternion = this->quaternion * q;
	this->eulerAngles = Quaternion::toEulerAngle(this->quaternion);
}
void Transform::RotateGlobal(Vector3 eulerAngles)
{
	Quaternion q = Quaternion::toQuaternion(eulerAngles.toRadians());
	this->quaternion = q * this->quaternion;
	this->eulerAngles = Quaternion::toEulerAngle(this->quaternion);
}


//Direction
Vector3 Transform::GetForward()
{
	glm::vec3 v3 = Quaternion::toRotationMatrix(quaternion) * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	return Vector3(v3.x, v3.y, v3.z);
}
Vector3 Transform::GetUp()
{
	glm::vec3 v3 = Quaternion::toRotationMatrix(quaternion) * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	return Vector3(v3.x, v3.y, v3.z);
}
Vector3 Transform::GetRight()
{
	glm::vec3 v3 = Quaternion::toRotationMatrix(quaternion) * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	return Vector3(v3.x, v3.y, v3.z);
}
