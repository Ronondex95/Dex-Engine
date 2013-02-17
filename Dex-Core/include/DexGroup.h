#pragma once

#include <DexPreCompletion.h>
#include <DexObject.h>

namespace Dex
{
	class D_EXPORT Group : public Object
	{
	public:
		Group( Group* parent, const String& name, int id );
		~Group( void );

		Group* CreateChildGroup( const String& name );

		bool CheckNameChild( const String& name );
		void AddChild( Group* child );
		Group* GetParent( void );

		const GroupList& GetChildList( void );
		Group* GetChild( const String& name );
		Group* GetChild( int id );

	private:
		Group*			m_Parent;
		GroupList		m_Child;
	};
}