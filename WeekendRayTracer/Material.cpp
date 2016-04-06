#include "Material.h"

#include "Vector3.h"

Vector3 Material::Reflect( const Vector3& vector, const Vector3& normal ) const
{
	return vector - 2 * vector.Dot( normal ) * normal;
}

bool Material::Refract( const Vector3& vector, const Vector3& normal, const float NiOverNt, Vector3& refracted ) const
{
	const Vector3 unitVector = vector.GetNormalized();
	const float dt = vector.GetNormalized().Dot( normal );
	const float discriminant = 1.f - NiOverNt * NiOverNt * ( 1.f - dt * dt );

	if ( discriminant > 0.f )
	{
		refracted = NiOverNt * ( unitVector - normal * dt ) - normal * std::sqrt( discriminant );
		return true;
	}
	else
	{
		return false;
	}
}

// Simple polynomial approximation of reflectivity by Christophe Shlick
float Material::Schlick( const float cosine, const float refractionIndex ) const
{
	float r0 = ( 1.f - refractionIndex ) / ( 1.f + refractionIndex );
	r0 = r0 * r0;
	return r0 + ( 1.f - r0 ) * std::pow( ( 1.f - cosine ), 5.f );
}