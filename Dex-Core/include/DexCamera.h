#pragma once

#include <DexPreCompletion.h>
#include <DexObject.h>

namespace Dex
{
	class D_EXPORT Camera : public Object
	{
	public:
		Camera( const String& name, int id );
		~Camera( void );

		const Point3& GetTarget( void );
		const Point3& GetUp( void );

	private:
		Point3				m_Target;
		Point3				m_Up;
	};
}