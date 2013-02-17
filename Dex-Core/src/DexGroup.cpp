#include <DexGroup.h>
#include <DexScene.h>
#include <DexCore.h>

namespace Dex
{
	Group::Group( Group* parent, const String& name, int id )
		: Object( name, id )
	{
		m_Parent = parent;
	}

	Group::~Group( void )
	{
	}

	Group* Group::CreateChildGroup( const String& name )
	{
		if ( CheckNameChild( name ) )
		{
			Group* group = new Group( this, name, m_IdCounter++ );
			AddChild( group );

			return group;
		}

		return NULL;
	}

	bool Group::CheckNameChild( const String& name )
	{
		for ( size_t i = 0; i < m_Child.size(); ++i )
		{
			if ( m_Child.at( i )->GetName() == name )
			{
				return false;
			}
		}

		return true;
	}

	void Group::AddChild( Group* child )
	{
		m_Child.push_back( child );
	}

	Group* Group::GetParent( void )
	{
		return m_Parent;
	}

	const GroupList& Group::GetChildList( void )
	{
		return m_Child;
	}

	Group* Group::GetChild( const String& name )
	{
		for ( size_t i = 0; i < m_Child.size(); ++i )
		{
			if ( m_Child.at( i )->GetName() == name )
			{
				return m_Child.at( i );
			}
		}

		return NULL;
	}

	Group* Group::GetChild( int id )
	{
		for ( size_t i = 0; i < m_Child.size(); ++i )
		{
			if ( m_Child.at( i )->GetId() == id )
			{
				return m_Child.at( i );
			}
		}

		return NULL;
	}
}