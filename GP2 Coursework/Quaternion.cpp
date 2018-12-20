#include "Quaternion.h"
#include <iostream>

//Quaternions tested with: https://quaternions.online/
//Set euler to ZYX order in radians.

Quaternion::Quaternion()
{
	w = 1.0f;
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Quaternion::Quaternion(float pitch, float roll, float yaw)
{
	Quaternion q = Quaternion::toQuaternion(pitch, roll, yaw);
	*this = q;
}

Quaternion::~Quaternion() {}


//Reference: http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
glm::mat4 Quaternion::toRotationMatrix(Quaternion q)
{
	return glm::mat4(
		1.0f - 2.0f * (q.y * q.y + q.z * q.z),        2.0f * (q.x * q.y + q.w * q.z),        2.0f * (q.x * q.z - q.w * q.y), 0.0f,
		       2.0f * (q.x * q.y - q.w * q.z), 1.0f - 2.0f * (q.x * q.x + q.z * q.z),        2.0f * (q.y * q.z + q.w * q.x), 0.0f,
		       2.0f * (q.x * q.z + q.w * q.y),        2.0f * (q.y * q.z - q.x * q.w), 1.0f - 2.0f * (q.x * q.x + q.y * q.y), 0.0f,
		0.0f,                                  0.0f,                                  0.0f,                                  1.0f
	);
}

//Reference: https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
Vector3 Quaternion::toEulerAngle(Quaternion q)
{
	float pitch, yaw, roll;

	//Pitch (x-axis rotation)
	float sinr_cosp = 2.0f * (q.w * q.x + q.y * q.z);
	float cosr_cosp = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
	pitch = atan2(sinr_cosp, cosr_cosp);

	//Yaw (y-axis rotation)
	float sinp = 2.0f * (q.w * q.y - q.z * q.x);
	if (fabs(sinp) >= 1)
		yaw = copysign(3.14f / 2.0f, sinp);
	else
		yaw = asin(sinp);

	//Yaw (z-axis rotation)
	float siny_cosp = 2.0f * (q.w * q.z + q.x * q.y);
	float cosy_cosp = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
	roll = atan2(siny_cosp, cosy_cosp);

	return Vector3(pitch, yaw, roll);
}


//Reference: https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
Quaternion Quaternion::toQuaternion(float pitch, float yaw, float roll)
{
	float cp = cos(pitch * 0.5f);
	float sp = sin(pitch * 0.5f);
	float cy = cos(yaw * 0.5f);
	float sy = sin(yaw * 0.5f);
	float cr = cos(roll * 0.5f);
	float sr = sin(roll * 0.5f);

	Quaternion q;
	q.w = cr * cp * cy + sr * sp * sy;
	q.x = cr * sp * cy - sr * cp * sy;
	q.y = cr * cp * sy + sr * sp * cy;
	q.z = sr * cp * cy - cr * sp * sy;
	return q;
}

Quaternion Quaternion::toQuaternion(Vector3 eulerAngles)
{
	return Quaternion::toQuaternion(eulerAngles.x, eulerAngles.y, eulerAngles.z);
}

//Operators
void Quaternion::operator=(Quaternion q)
{
	this->w = q.w;
	this->x = q.x;
	this->y = q.y;
	this->z = q.z;
}
bool Quaternion::operator==(Quaternion q)
{
	bool b = true;
	b &= this->w == q.w;
	b &= this->x == q.x;
	b &= this->y == q.y;
	b &= this->z == q.z;
	return b;
}
Quaternion Quaternion::operator*(Quaternion q)
{
	Quaternion result;
	result.x =  x * q.w + y * q.z - z * q.y + w * q.x;
	result.y = -x * q.z + y * q.w + z * q.x + w * q.y;
	result.z =  x * q.y - y * q.x + z * q.w + w * q.z;
	result.w = -x * q.x - y * q.y - z * q.z + w * q.w;
	return result;
}

//Used for debugging.
void Quaternion::print()
{
	std::cout << "W: " << w << " | X: " << x << " | Y: " << y << "  | Z: " << z << std::endl;
}
