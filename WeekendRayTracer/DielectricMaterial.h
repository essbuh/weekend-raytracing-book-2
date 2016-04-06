#pragma once

#include "Material.h"

class DielectricMaterial : public Material
{
public:
	DielectricMaterial( const float refractionIndex );

	virtual bool Scatter( const Ray& ray, const HitRecord& record, Vector3& attenuation, Ray& scattered ) const override;

private:
	float refractionIndex;
};