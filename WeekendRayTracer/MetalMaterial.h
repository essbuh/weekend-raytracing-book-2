#pragma once

#include "Material.h"
#include "Vector3.h"

class MetalMaterial : public Material
{
public:
	MetalMaterial( const Vector3& albedo, const float fuzz );

	virtual bool Scatter( const Ray& ray, const HitRecord& record, Vector3& attenuation, Ray& scattered ) const override;

private:
	Vector3 albedo;
	float fuzz;
};