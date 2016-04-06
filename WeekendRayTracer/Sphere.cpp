#include "Sphere.h"

#include "Ray.h"

Sphere::Sphere()
	: center( VECTOR3_ZERO )
	, radius( 0.f )
	, material( nullptr )
{}

Sphere::Sphere( const Vector3& center, const float radius, const Material* material )
	: center( center )
	, radius( radius )
	, material( material )
{}

bool Sphere::Hit( const Ray& ray, float tMin, float tMax, HitRecord& OutHitRecord ) const
{
	const Vector3 centerToOrigin = ray.Origin() - center;
	const float a = ray.Direction().Dot( ray.Direction() );
	const float b = centerToOrigin.Dot( ray.Direction() );
	const float c = centerToOrigin.Dot( centerToOrigin ) - ( radius * radius );
	const float discriminant = ( b * b - a * c );

	if ( discriminant > 0.f )
	{
		float temp = ( -b - std::sqrt( discriminant ) ) / a;
		if ( temp < tMax && temp > tMin )
		{
			OutHitRecord.t = temp;
			OutHitRecord.point = ray.Eval( temp );
			OutHitRecord.normal = ( OutHitRecord.point - center ) / radius;
			OutHitRecord.material = material;
			return true;
		}

		temp = ( -b + std::sqrt( discriminant ) ) / a;
		if ( temp < tMax && temp > tMin )
		{
			OutHitRecord.t = temp;
			OutHitRecord.point = ray.Eval( temp );
			OutHitRecord.normal = ( OutHitRecord.point - center ) / radius;
			OutHitRecord.material = material;
			return true;
		}
	}

	return false;
}