#include "Camera.h"
#include "DielectricMaterial.h"
#include "HitableList.h"
#include "LambertianMaterial.h"
#include "MetalMaterial.h"
#include "MovingSphere.h"
#include "Rand.h"
#include "Ray.h"
#include "Sphere.h"

#include <iostream>

Vector3 Color( const Ray& ray, const Hitable& world, const int depth )
{
	HitRecord record;
	if ( world.Hit( ray, 0.001f, FLT_MAX, record ) )
	{
		Ray scattered;
		Vector3 attenuation;
		if ( depth < 50 && record.material->Scatter( ray, record, attenuation, scattered ) )
		{
			return attenuation * Color( scattered, world, depth + 1 );
		}
		else
		{
			return Vector3( 0.f, 0.f, 0.f );
		}
	}
	else
	{
		Vector3 unitDir = ray.Direction().GetNormalized();
		const float t = 0.5f * ( unitDir.y + 1.f );
		return ( 1.f - t ) * Vector3( 1.f, 1.f, 1.f ) + t * Vector3( 0.5f, 0.7f, 1.f );
	}
}

const Hitable* RandomScene()
{
	const int n = 500;
	const Hitable** list = new const Hitable*[n + 1];
	list[0] = new Sphere( Vector3( 0.f, -1000.f, 0.f ), 1000.f, new LambertianMaterial( Vector3( 0.5f, 0.5f, 0.5f ) ) );

	int i = 1;
	for ( int a = -11; a < 11; ++a )
	{
		for ( int b = -11; b < 11; ++b )
		{
			const float chooseMat = Rand01();
			Vector3 center( a + 0.9f * Rand01(), 0.2f, b + 0.9f * Rand01() );
			if ( ( center - Vector3( 4.f, 0.2f, 0.f ) ).Length() > 0.9f )
			{
				if ( chooseMat < 0.8f )
				{
					list[i++] = new MovingSphere( center, center + Vector3(0.f, 0.5f * Rand01(), 0.f), 0.f, 1.f, 0.2f, new LambertianMaterial( Vector3( Rand01() * Rand01(), Rand01() * Rand01(), Rand01() * Rand01() ) ) );
				}
				else if ( chooseMat < 0.95f )
				{
					list[i++] = new Sphere( center, 0.2f, new MetalMaterial( Vector3( 0.5f * ( 1 + Rand01() ), 0.5f * ( 1 + Rand01() ), 0.5f * ( 1 + Rand01() ) ), 0.5f * Rand01() ) );
				}
				else
				{
					list[i++] = new Sphere( center, 0.2f, new DielectricMaterial( 1.5f ) );
				}
			}
		}
	}

	list[i++] = new Sphere( Vector3( 0.f, 1.f, 0.f ), 1.f, new DielectricMaterial( 1.5f ) );
	list[i++] = new Sphere( Vector3( -4.f, 1.f, 0.f ), 1.f, new LambertianMaterial( Vector3( 0.4f, 0.2f, 0.1f ) ) );
	list[i++] = new Sphere( Vector3( 4.f, 1.f, 0.f ), 1.f, new MetalMaterial( Vector3( 0.7f, 0.6f, 0.5f ), 0.0f ) );

	return new HitableList( list, i );
}

int main()
{
	const int nx = 200;
	const int ny = 100;
	const int ns = 100;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	const int hitableCount = 5;
	const Hitable* list[hitableCount];
	list[0] = new Sphere( Vector3( 0.f, 0.f, -1.f ), 0.5f, new LambertianMaterial( Vector3( 0.1f, 0.2f, 0.5f ) ) );
	list[1] = new Sphere( Vector3( 0.f, -100.5f, -1.f ), 100.f, new LambertianMaterial( Vector3( 0.8f, 0.8f, 0.f ) ) );
	list[2] = new Sphere( Vector3( 1.f, 0.f, -1.f ), 0.5f, new MetalMaterial( Vector3( 0.8f, 0.6f, 0.2f ), 0.f ) );
	list[3] = new Sphere( Vector3( -1.f, 0.f, -1.f ), 0.5f, new DielectricMaterial( 1.5f ) );
	list[4] = new Sphere( Vector3( -1.f, 0.f, -1.f ), -0.45f, new DielectricMaterial( 1.5f ) );
	const Hitable* world = RandomScene(); // list, hitableCount );

	const Vector3 lookFrom( 13.f, 2.f, 3.f );
	const Vector3 lookAt( 0.f, 0.f, 0.f );
	const float distToFocus = 10.f;
	const float aperture = 0.f;

	Camera camera( lookFrom, lookAt, Vector3( 0.f, 1.f, 0.f ), 20.f, (float) nx / (float) ny, aperture, distToFocus, 0.f, 1.f );

	for ( int j = ny - 1; j >= 0; --j )
	{
		for ( int i = 0; i < nx; ++i )
		{
			Vector3 color( 0.f, 0.f, 0.f );
			for ( int s = 0; s < ns; ++s )
			{
				const float u = (float) ( i + Rand01() ) / (float) ( nx );
				const float v = (float) ( j + Rand01() ) / (float) ( ny );
				const Ray ray = camera.GetRay( u, v );
				color += Color( ray, *world, 0 );
			}

			color /= (float) ns;
			color = Vector3( std::sqrt( color.r ), std::sqrt( color.g ), std::sqrt( color.b ) );

			const int ir = (int) ( 255.99 * color.r );
			const int ig = (int) ( 255.99 * color.g );
			const int ib = (int) ( 255.99 * color.b );

			std::cout << ir << " " << ig << " " << ib << std::endl;
		}
	}

}