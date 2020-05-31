#include "Quaternion.h"
#include <cmath>

using namespace sedge;

Quaternion::Quaternion()
	: w(1), x(0), y(0), z(0)
{
}

Quaternion::Quaternion(const float w, const float x, const float y, const float z)
	: w(w), x(x), y(y), z(z)
{
}

Quaternion::Quaternion(const Quaternion& q)
	: w(q.w), x(q.x), y(q.y), z(q.z)
{
}

Quaternion Quaternion::Normalize(const Quaternion& q)
{
	Quaternion result(q);

	const float magnitude = q.GetMagnitude();
	result.w /= magnitude;
	result.x /= magnitude;
	result.y /= magnitude;
	result.z /= magnitude;

	return result;
}

float Quaternion::GetMagnitude() const
{
	return sqrt(w * w + x * x + y * y + z * z);
}

Quaternion sedge::operator*(const Quaternion & q1, const Quaternion q2)
{
	Quaternion result;

	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;

	return result;
}