#pragma once

namespace s3dge
{
	struct Quaternion
	{
		float w;
		float x;
		float y;
		float z;

		Quaternion();
		Quaternion(const float w, const float x, const float y, const float z);
		Quaternion(const Quaternion& q);

		static Quaternion Normalize(const Quaternion& q);

		inline float GetMagnitude() const;

		friend Quaternion operator*(const Quaternion& q1, const Quaternion q2);
	};
}