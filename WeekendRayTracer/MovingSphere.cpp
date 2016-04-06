#include "MovingSphere.h"

#include "Ray.h"

MovingSphere::MovingSphere()
	: center0( VECTOR3_ZERO )
	, center1( VECTOR3_ZERO )
	, time0( 0.f )
	, time1( 0.f )
	, radius( 0.f )
	, material( nullptr )
{}

MovingSphere::MovingSphere( const Vector3& center0, const Vector3& center1, const float time0, const float time1, const float radius, const Material* material )
	: center0( center0 )
	, center1( center1 )
	, time0( time0 )
	, time1( time1 )
	, radius( radius )
	, material( material )
{}

bool MovingSphere::Hit( const Ray& ray, float tMin, float tMax, HitRecord& OutHitRecord ) const
{
	const Vector3 center = GetCenter( ray.GetTime() );
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

Vector3 MovingSphere::GetCenter( const float time ) const
{
	return center0 + ( ( time - time0 ) / ( time1 - time0 ) ) * ( center1 - center0 );
}