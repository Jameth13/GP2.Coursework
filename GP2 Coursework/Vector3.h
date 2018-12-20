#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>


class Vector3
{
private:
	glm::mat4 RotX(float x);
	glm::mat4 RotY(float y);
	glm::mat4 RotZ(float z);


public:
	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();

	float x, y, z;

	//Matrices
	glm::mat4 TransMat();
	glm::mat4 ScaleMat();
	glm::mat4 RotMat();

	//Normalize
	void Normalize();
	Vector3 Normalized();

	//Conversions
	Vector3 toRadians();
	Vector3 toDegrees();

	//Operators
	void operator=(Vector3 v);
	bool operator==(Vector3 v);
	Vector3 operator+(Vector3 v);
	Vector3 operator-(Vector3 v);
	Vector3 operator*(Vector3 v);
	Vector3 operator/(Vector3 v);
	void operator+=(Vector3 v);
	void operator-=(Vector3 v);
	void operator*=(Vector3 v);
	void operator/=(Vector3 v);


	//GLM Type Conversion
	//This function was created because the implicit type conversions below were sadly not completed in time for submission.
	glm::vec3 GLM();
	//Constructor
	Vector3(const glm::vec3 &vec3);
	//Assignment
	Vector3& operator= (const glm::vec3 &x);
	//Type-cast operator. Reference: http://www.cplusplus.com/doc/tutorial/typecasting/
	template <typename T, glm::precision P >
	inline operator const glm::tvec3<T, P>&()
	{
		//Warning: Returning address of local variable or temporary
		return glm::tvec3<T, P>(x, y, z);
	}


	//Used for debugging
	void print();
};
