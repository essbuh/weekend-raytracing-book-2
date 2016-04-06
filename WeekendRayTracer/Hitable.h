#pragma once

#include "Vector3.h"

class Ray;
class Material;

struct HitRecord
{
	float t;
	Vector3 point;
	Vector3 normal;
	const Material* material;
};

class Hitable
{
public:
	virtual bool Hit( const Ray& ray, float tMin, float tMax, HitRecord& OutHitRecord ) const = 0;
};