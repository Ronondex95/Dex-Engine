#pragma once

#include <DexPreCompletion.h>
#include <DexObject.h>

namespace Dex
{
	class Group : public Object
	{
	public:
		Group( Group* parent, const String& name, int id );
		~Group( void );


		Group* CreateGroup( const String& name );

	private:
		Group*			m_pParent;
		GroupList		m_Child;
	};
}

