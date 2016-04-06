#pragma once

#include <cmath>
#include <utility>

#define VECTOR3_ZERO Vector3(0.f, 0.f, 0.f)

class Vector3
{
public:
	Vector3() {}

	Vector3( const float x, const float y, const float z ) { e[0] = x; e[1] = y; e[2] = z; }

	Vector3( const Vector3& other )
		: x( other.x )
		, y( other.y )
		, z( other.z )
	{}

	Vector3( Vector3&& other )
		: x( std::move( other.x ) )
		, y( std::move( other.y ) )
		, z( std::move( other.z ) )
	{}

	inline Vector3& operator=( const Vector3& other )
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	inline Vector3& operator=( Vector3&& other )
	{
		x = std::move( other.x );
		y = std::move( other.y );
		z = std::move( other.z );
		return *this;
	}

	inline const Vector3& operator+() const { return *this; }
	inline Vector3 operator-() const { return Vector3( -x, -y, -z ); }
	inline float operator[]( int i ) const { return e[i]; }
	inline float& operator[]( int i ) { return e[i]; }

	inline Vector3& operator+=( const Vector3& v2 ) { x += v2.x; y += v2.y; z += v2.z; return *this; }
	inline Vector3& operator-=( const Vector3& v2 ) { x -= v2.x; y -= v2.y; z -= v2.z; return *this; }
	inline Vector3& operator*=( const Vector3& v2 ) { x *= v2.x; y *= v2.y; z *= v2.z; return *this; }
	inline Vector3& operator/=( const Vector3& v2 ) { x /= v2.x; y /= v2.y; z /= v2.z; return *this; }
	inline Vector3& operator*=( const float t ) { x *= t; y *= t; z *= t; return *this; }
	inline Vector3& operator/=( const float t ) { x /= t; y /= t; z /= t; return *this; }

	inline float Length() const { return std::sqrt( x*x + y*y + z*z ); }
	inline float LengthSq() const { return ( x*x + y*y + z*z ); }

	inline void Normalize() { (*this) /= Length(); }
	inline Vector3 GetNormalized() const { Vector3 vec(*this); vec.Normalize(); return vec; }

	inline float Dot( const Vector3& other ) const { return x * other.x + y * other.y + z * other.z; }
	inline Vector3 Cross( const Vector3& other ) const { return Vector3( ( y * other.z - z * other.y ), ( z * other.x - x * other.z ), ( x * other.y - y * other.x ) ); }

	union
	{
		float e[3];
		struct 
		{
			float x;
			float y;
			float z;
		};
		struct 
		{
			float r;
			float g;
			float b;
		};
	};
};

inline Vector3 operator+( const Vector3& v1, const Vector3& v2 )
{
	return Vector3( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z );
}

inline Vector3 operator-( const Vector3& v1, const Vector3& v2 )
{
	return Vector3( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z );
}

inline Vector3 operator*( const Vector3& v1, const Vector3& v2 )
{
	return Vector3( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z );
}

inline Vector3 operator/( const Vector3& v1, const Vector3& v2 )
{
	return Vector3( v1.x / v2.x, v1.y / v2.y, v1.z / v2.z );
}

inline Vector3 operator*( const Vector3& v1, const float s )
{
	return Vector3( v1.x * s, v1.y * s, v1.z * s );
}

inline Vector3 operator/( const Vector3& v1, const float s )
{
	return Vector3( v1.x / s, v1.y / s, v1.z / s );
}

inline Vector3 operator*( const float s, const Vector3& v1 )
{
	return Vector3( v1.x * s, v1.y * s, v1.z * s );
}

inline Vector3 operator/( const float s, const Vector3& v1 )
{
	return Vector3( v1.x / s, v1.y / s, v1.z / s );
}