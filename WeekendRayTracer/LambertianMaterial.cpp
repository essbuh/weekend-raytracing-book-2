#include "LambertianMaterial.h"

#include "Hitable.h"
#include "Rand.h"
#include "Ray.h"

LambertianMaterial::LambertianMaterial( const Vector3& _albedo )
	: albedo( _albedo )
{}

bool LambertianMaterial::Scatter( const Ray& /*ray*/, const HitRecord& record, Vector3& attenuation, Ray& scattered ) const
{
	Vector3 target = record.point + record.normal + RandInUnitSphere();
	scattered = Ray( record.point, target - record.point );
	attenuation = albedo;
	return true;
}