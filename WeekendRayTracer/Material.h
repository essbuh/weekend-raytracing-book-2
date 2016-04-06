#pragma once

class Ray;
class Vector3;
struct HitRecord;

class Material
{
public:
	virtual bool Scatter( const Ray& ray, const HitRecord& record, Vector3& attenuation, Ray& scattered ) const = 0;

protected:
	Vector3 Reflect( const Vector3& vector, const Vector3& normal ) const;
	bool Refract( const Vector3& vector, const Vector3& normal, const float NiOverNt, Vector3& refracted ) const;

	float Schlick( const float cosine, const float refractionIndex ) const;
};