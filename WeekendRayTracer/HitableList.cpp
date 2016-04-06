#include "HitableList.h"

HitableList::HitableList()
	: list( nullptr )
	, count( 0 )
{}

HitableList::HitableList( const Hitable** list, int count )
	: list( list )
	, count( count )
{}

bool HitableList::Hit( const Ray& ray, float tMin, float tMax, HitRecord& OutHitRecord ) const
{
	HitRecord tempRecord;
	bool hitAnything = false;
	float closestSoFar = tMax;
	
	for ( int i = 0; i < count; ++i )
	{
		if ( list[i]->Hit( ray, tMin, closestSoFar, tempRecord ) )
		{
			hitAnything = true;
			closestSoFar = tempRecord.t;
			OutHitRecord = tempRecord;
		}
	}

	return hitAnything;
}