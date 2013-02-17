#include <DexLight.h>

namespace Dex
{
	Light::Light( const String& name, int id, const Point4& color )
		: Object( name, id )
	{
		m_Color = color;
	}

	const Point4& Light::GetColor( void )
	{
		return m_Color;
	}
}