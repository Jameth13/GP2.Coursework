#pragma once
#include <glm/glm.hpp>
#include "Vector3.h"

class Quaternion
{
public:
	Quaternion();
	Quaternion(float pitch, float roll, float yaw);
	~Quaternion();

	float w, x, y, z;

	static glm::mat4 toRotationMatrix(Quaternion q);
	static Vector3 toEulerAngle(Quaternion q);
	static Quaternion toQuaternion(float pitch, float roll, float yaw);
	static Quaternion toQuaternion(Vector3 eulerAngles);

	void operator=(Quaternion q);
	bool operator==(Quaternion q);
	Quaternion operator*(Quaternion q);

	//Used for debugging.
	void print();
};
