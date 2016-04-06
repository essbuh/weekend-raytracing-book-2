#pragma once

#include "Hitable.h"

class Sphere : public Hitable
{
public:
	Sphere();
	Sphere( const Vector3& center, const float radius, const Material* material );
	virtual bool Hit( const Ray& ray, float tMin, float tMax, HitRecord& OutHitRecord ) const override;

private:
	Vector3 center;
	float radius;
	const Material* material;
};