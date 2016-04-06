#pragma once

#include <stdlib.h>

inline float Rand01()
{
	return ( (float) std::rand() ) / ( RAND_MAX + 1 );
}

inline Vector3 RandInUnitSphere()
{
	Vector3 p;
	do
	{
		p = 2.f * Vector3( Rand01(), Rand01(), Rand01() ) - Vector3( 1.f, 1.f, 1.f );
	} while ( p.Dot( p ) >= 1.f );
	return p;
}

inline Vector3 RandInUnitDisk()
{
	Vector3 p;
	do
	{
		p = 2.f * Vector3( Rand01(), Rand01(), 0.f ) - Vector3( 1.f, 1.f, 0.f );
	} while ( p.Dot( p ) >= 1.f );
	return p;
}