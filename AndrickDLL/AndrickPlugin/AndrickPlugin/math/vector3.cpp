#include "vector3.h"
#include "math_util.h"

namespace ap
{
	Vector3::Vector3(const float& x, const float& y, const float& z) :
		x(x), y(y), z(z)
	{ };

	Vector3::Vector3(float vec[]) :
		x(vec[0]), y(vec[1]), z(vec[2])
	{

	}

	float Vector3::getMagnitude() const 
	{ 
		return sqrt(getMagnitudeSquared()); 
	}

	float Vector3::getMagnitudeSquared() const 
	{ 
		return dot(*this, *this); 
	}

	void Vector3::AndrewTest(float nums[])
	{
		//Vector3 vec(x, y, z);
		nums[0] = 6;
		nums[1] = 6;
		nums[2] = 6;
	}

	Vector3 Vector3::cross(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 vec;

		// a x b = <a2*b3 - a3*b2, a3*b1 - a1*b3, a1*b2 - a2*b1>

		vec.x = (lhs.y * rhs.z) - (lhs.z * rhs.y);
		vec.y = (lhs.z * rhs.x) - (lhs.x * rhs.z);
		vec.z = (lhs.x * rhs.y) - (lhs.y * rhs.x);

		return vec;
	}

	float Vector3::dot(const Vector3& lhs, const Vector3& rhs)
	{
		//dot = v1x * v2x + v1y * v2y + etc..
		float dot = lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;

		return dot;
	}

	const Vector3& Vector3::normalize()
	{
		float mag = getMagnitude();
		x /= mag;
		y /= mag;
		z /= mag;
		return *this;
	}

	Vector3 Vector3::normalized(const Vector3& vec)
	{
		Vector3 normalized = vec;
		float mag = normalized.getMagnitude();
		normalized.x /= mag;
		normalized.y /= mag;
		normalized.z /= mag;
		return normalized;
	}

	void Vector3::toFloatArray(float* f) const
	{
		f[0] = x;
		f[1] = y;
		f[2] = z;
	}

	Vector3 Vector3::operator-()
	{
		Vector3 result;
		result.x = -x;
		result.y = -y;
		result.z = -z;
		return result;
	}

	Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 result;
		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;
		result.z = lhs.z + rhs.z;
		return result;
	}

	Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 result;
		result.x = lhs.x - rhs.x;
		result.y = lhs.y - rhs.y;
		result.z = lhs.z - rhs.z;
		return result;
	}

	Vector3 operator*(const float& scalar, const Vector3& rhs)
	{
		Vector3 result;
		result.x = scalar * rhs.x;
		result.y = scalar * rhs.y;
		result.z = scalar * rhs.z;
		return result;
	}

	Vector3 operator*(const Vector3& lhs, const float& scalar)
	{
		Vector3 result;
		result.x = scalar * lhs.x;
		result.y = scalar * lhs.y;
		result.z = scalar * lhs.z;
		return result;
	}

	Vector3 operator/(const Vector3& lhs, const float& scalar)
	{
		if (scalar < EPSILON) return Vector3(-1, -1, -1);

		Vector3 result;
		result.x = lhs.x / scalar;
		result.y = lhs.y / scalar;
		result.z = lhs.z / scalar;
		return result;
	}
}