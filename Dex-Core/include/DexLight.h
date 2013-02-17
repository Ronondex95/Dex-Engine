#pragma once

#include <DexPreCompletion.h>
#include <DexObject.h>

namespace Dex
{
	class D_EXPORT Light : public Object
	{
	public:
		Light( const String& name, int id, const Point4& color );
		~Light( void );

		const Point4& GetColor( void );

	private:
		Point4			m_Color;
	};
}