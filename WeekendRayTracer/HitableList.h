#pragma once

#include "Hitable.h"

class HitableList : public Hitable
{
public:
	HitableList();
	HitableList( const Hitable** list, int count );

	virtual bool Hit( const Ray& ray, float tMin, float tMax, HitRecord& OutHitRecord ) const;

private:
	const Hitable** list;
	int count;
};