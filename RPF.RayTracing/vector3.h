#pragma once

#include <cmath>
#include <iostream>

class vector3
{
public:
	vector3() : vector_{0, 0, 0} { }
	vector3(const float x, const float y, const float z) : vector_{x, y, z} { }

	float x() const { return vector_[0]; }
	float y() const { return vector_[1]; }
	float z() const { return vector_[2]; }

	vector3 operator-() const { return {-vector_[0], -vector_[1], -vector_[2]}; }
	float operator[](const int i) const { return vector_[i]; }
	float& operator[](const int i) { return vector_[i]; }

	vector3& operator +=(const vector3& vector)
	{
		vector_[0] += vector.x();
		vector_[1] += vector.y();
		vector_[2] += vector.z();
		return *this;
	}

	vector3& operator *=(const float t)
	{
		vector_[0] *= t;
		vector_[1] *= t;
		vector_[2] *= t;
		return *this;
	}

	vector3& operator /=(const float t)
	{
		return *this *= 1 / t;
	}

	float length() const
	{
		return std::sqrt(length_squared());
	}

	float length_squared() const
	{
		return vector_[0] * vector_[0] + vector_[1] * vector_[1] + vector_[2] * vector_[2];
	}

private:
	float vector_[3];
};

using color = vector3;
using point3 = vector3;

inline std::ostream& operator <<(std::ostream& out, const vector3& vector)
{
	return out << vector.x() << ' ' << vector.y() << ' ' << vector.z();
}

inline vector3 operator +(const vector3& u, const vector3& v)
{
	return {u.x() + v.x(), u.y() + v.y(), u.z() + v.z()};
}

inline vector3 operator -(const vector3& u, const vector3& v)
{
	return {u.x() - v.x(), u.y() - v.y(), u.z() - v.z()};
}

inline vector3 operator *(const vector3& u, const vector3& v)
{
	return {u.x() * v.x(), u.y() * v.y(), u.z() * v.z()};
}

inline vector3 operator *(const vector3& u, const float t)
{
	return {u.x() * t, u.y() * t, u.z() * t};
}

inline vector3 operator /(const vector3& u, const float t)
{
	return u * (1 / t);
}

inline float dot(const vector3& u, const vector3& v)
{
	return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

inline vector3 cross(const vector3 u, const vector3 v)
{
	return
	{
		u.y() * v.z() - u.z() * v.y(),
		u.z() * v.x() - u.x() * v.z(),
		u.x() * v.y() - u.y() * v.x()
	};
}

inline vector3 unit_vector(const vector3 u)
{
	return u / u.length();
}