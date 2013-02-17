#include <DexMash.h>
#include <DexRenderConnect.h>

namespace Dex
{
	Mash::Mash( const String& name, int id )
		: Object( name, id )
	{
	}

	Mash::~Mash( void )
	{
	}

	void Mash::Load( const String& file )
	{
		IFStream stream( file.c_str() );

		if ( stream )
		{
			// LOAD
			stream.close();
		}

		//m_VercexBuffer = m_pConnect->CreateVertexBuffer( TYPE, MEMORY );
	}
}