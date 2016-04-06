#include "MetalMaterial.h"

#include "Hitable.h"
#include "Rand.h"
#include "Ray.h"

MetalMaterial::MetalMaterial( const Vector3& albedo, const float _fuzz )
	: albedo( albedo )
	, fuzz( _fuzz )
{
	if ( _fuzz >= 1.f )
	{
		fuzz = 1.f;
	}
}

bool MetalMaterial::Scatter( const Ray& ray, const HitRecord& record, Vector3& attenuation, Ray& scattered ) const
{
	Vector3 reflected = Reflect( ray.Direction().GetNormalized(), record.normal );
	scattered = Ray( record.point, reflected + fuzz * RandInUnitSphere() );
	attenuation = albedo;
	return ( scattered.Direction().Dot( record.normal ) > 0.f );
}