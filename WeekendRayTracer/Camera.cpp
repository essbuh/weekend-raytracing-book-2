#include "Camera.h"

#include "Rand.h"
#include "Ray.h"

#define _USE_MATH_DEFINES	// for M_PI
#include <math.h>

Camera::Camera(const Vector3& position, const Vector3& lookAt, const Vector3& inUp, const float vertFovDegrees, const float aspectRatio, const float aperture, const float focusDist)
	: origin( position )
{
	lensRadius = aperture / 2.f;

	const double theta = vertFovDegrees * M_PI / 180.0;
	const float halfHeight = (float) std::tan( theta / 2.0 );	// assuming z is +/- 1
	const float halfWidth = aspectRatio * halfHeight;

	forward = ( position - lookAt ).GetNormalized();
	right = inUp.Cross( forward ).GetNormalized();
	up = forward.Cross( right );

	lowerLeftCorner = position - halfWidth * focusDist * right - halfHeight * focusDist * up - focusDist * forward;
	horizStride = 2.f * halfWidth * focusDist * right;
	vertStride = 2.f * halfHeight * focusDist * up;
}

const Ray Camera::GetRay( const float u, const float v ) const
{
	const Vector3 randomInDisk = lensRadius * RandInUnitDisk();
	const Vector3 offset = right * randomInDisk.x + up * randomInDisk.y;
	return Ray( origin + offset, lowerLeftCorner + u * horizStride + v * vertStride - origin - offset );
}