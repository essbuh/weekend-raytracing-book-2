#pragma once

#include "Hitable.h"

class MovingSphere : public Hitable
{
public:
	MovingSphere();
	MovingSphere( const Vector3& center0, const Vector3& center1, const float time0, const float time1, const float radius, const Material* material );
	virtual bool Hit( const Ray& ray, float tMin, float tMax, HitRecord& OutHitRecord ) const override;

private:

	Vector3 GetCenter( const float time ) const;

	Vector3 center0;
	Vector3 center1;
	const float time0;
	const float time1;
	float radius;
	const Material* material;
};