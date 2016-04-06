#pragma once

#include "Material.h"
#include "Vector3.h"

class LambertianMaterial : public Material
{
public:
	LambertianMaterial( const Vector3& _albedo );

	virtual bool Scatter( const Ray& ray, const HitRecord& record, Vector3& attenuation, Ray& scattered ) const override;

private:
	Vector3 albedo;
};