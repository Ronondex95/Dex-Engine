#pragma once

#include <DexPreCompletion.h>
#include <DexObject.h>
#include <DexPrimitive.h>

namespace Dex
{
	class D_EXPORT Mash : public Object, public Primitive
	{
	public:
		Mash( const String& name, int id );
		~Mash( void );

		void Load( const String& file );

	private:
	};
}