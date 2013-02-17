#include <DexRootGroup.h>

namespace Dex
{
	Group::Group( Group* parent, const String& name, int id )
		: Object( name, id )
	{
		m_pParent = parent;
	}

	Group::~Group( void )
	{
	}

	Group* Group::CreateGroup( const String& name )
	{
		return NULL;
	}
}
