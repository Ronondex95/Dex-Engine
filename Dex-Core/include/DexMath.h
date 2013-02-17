#pragma once

#include <DexPreCompletion.h>

namespace Dex
{
	typedef float Point;

	class D_EXPORT Point2
	{
	public:
		inline Point2( void )
		{
			x = 0;
			y = 0;
		}

		inline Point2( Point _x, Point _y )
		{
			x = _x;
			y = _y;
		}

		inline Point2 operator + ( const Point2& p ) const
		{
			return Point2( x + p.x, y + p.y );
		}

	public:
		Point	x, y;
	};

	class D_EXPORT Point3
	{
	public:
		inline Point3( void )
		{
			x = 0;
			y = 0;
			z = 0;
		}

		inline Point3( Point _x, Point _y, Point _z )
		{
			x = _x;
			y = _y;
			z = _z;
		}

		inline Point3 operator + ( const Point3& p ) const
		{
			return Point3( x + p.x, y + p.y, z + p.z );
		}

	public:
		Point	x, y, z;
	};

	class D_EXPORT Point4
	{
	public:
		inline Point4( void )
		{
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}

		inline Point4( Point _x, Point _y, Point _z, Point _w )
		{
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}

		inline Point4 operator + ( const Point4& p ) const
		{
			return Point4( x + p.x, y + p.y, z + p.z, w + p.w );
		}

	public:
		Point	x, y, z, w;
	};

	class D_EXPORT Vector3
	{
	public:
		inline Vector3( void )
		{
			x = 0;
			y = 0;
			z = 0;
		}

		inline Vector3( Point _x, Point _y, Point _z )
		{
			x = _x;
			y = _y;
			z = _z;
		}

		inline Vector3 operator + ( const Vector3& v ) const
		{
			return Vector3( x + v.x, y + v.y, z + v.z );
		}

	public:
		Point	x, y, z;
	};

	class D_EXPORT Matrix4
	{
	public:
		inline static Matrix4 Zero( void )
		{
			return Matrix4(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1 );
		}

		inline Matrix4(
			Point m00, Point m01, Point m02, Point m03,
			Point m10, Point m11, Point m12, Point m13,
			Point m20, Point m21, Point m22, Point m23,
			Point m30, Point m31, Point m32, Point m33 )
		{
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[0][3] = m03;

			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[1][3] = m13;

			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
			m[2][3] = m23;

			m[3][0] = m30;
			m[3][1] = m31;
			m[3][2] = m32;
			m[3][3] = m33;
		}

		inline Matrix4( void )
		{
			m[0][0] = 1;
			m[0][1] = 0;
			m[0][2] = 0;
			m[0][3] = 0;

			m[1][0] = 0;
			m[1][1] = 1;
			m[1][2] = 0;
			m[1][3] = 0;

			m[2][0] = 0;
			m[2][1] = 0;
			m[2][2] = 1;
			m[2][3] = 0;

			m[3][0] = 0;
			m[3][1] = 0;
			m[3][2] = 0;
			m[3][3] = 1;
		}

	private:
		union
		{
			Point	m[4][4];
		};
	};
}