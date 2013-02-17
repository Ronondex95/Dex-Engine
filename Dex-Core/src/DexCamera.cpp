#include <DexCamera.h>

namespace Dex
{
	Camera::Camera( const String& name, int id )
		: Object( name, id )
	{
		m_Target = Point3( 0.0f, 0.0f, 0.0f );
		m_Up = Point3( 0.0f, 1.0f, 0.0f );
	}

	Camera::~Camera( void )
	{
	}

	const Point3& Camera::GetTarget( void )
	{
		return m_Target;
	}

	const Point3& Camera::GetUp( void )
	{
		return m_Up;
	}
}