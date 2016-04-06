#pragma once

#include <utility>
#include "Vector3.h"

class Ray
{
public:
	Ray() {}
	Ray( const Vector3& a, const Vector3& b, const float time = 0.f )
		: a( a )
		, b( b )
		, time( time )
	{}

	Ray( const Ray& other )
		: a( other.a )
		, b( other.b )
	{}

	Ray( Ray&& other )
		: a( other.a )
		, b( other.b )
	{}

	inline Ray& operator=( const Ray& other )
	{
		a = other.a;
		b = other.b;
		return *this;
	}

	inline Ray& operator=( Ray&& other )
	{
		a = std::move(other.a);
		b = std::move(other.b);
		return *this;
	}

	const Vector3& Origin() const { return a; }
	const Vector3& Direction() const { return b; }
	const float GetTime() const { return time; }
	Vector3 Eval( const float t ) const { return a + b * t; }

private:
	Vector3 a;
	Vector3 b;
	float time;
};