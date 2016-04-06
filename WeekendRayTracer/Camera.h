#pragma once

#include "Vector3.h"

class Ray;

class Camera
{
public:
	Camera(const Vector3& position, const Vector3& lookAt, const Vector3& inUp, const float vertFovDegrees, const float aspectRatio, const float aperture, const float focusDist );

	const Ray GetRay( const float u, const float v ) const;

private:
	Vector3 origin;
	Vector3 lowerLeftCorner;
	Vector3 horizStride;
	Vector3 vertStride;

	Vector3 forward;
	Vector3 right;
	Vector3 up;

	float lensRadius;
};