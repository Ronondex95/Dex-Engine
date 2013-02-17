#pragma once

#include <DexPreCompletion.h>
#include <DexMath.h>

namespace Dex
{
	typedef vector< Group* >::type	GroupList;

	class D_EXPORT Scene
	{
	public:
		Scene( const String& name, const String& render_window );
		~Scene( void );

		int GetNewId( void );

		Group* GetRootGroup( void );

		Camera* CreateCamera( const String& name, bool active = true );
		Camera* GetCamera( const String& name );

		Mash* CreateDMashFromFile( const String& file, const String& name );
		Mash* GetMash( const String& name );

		Light* CreateLight( const String& name, const Point4& color );
		Light* GetLight( const String& name );

		void RenderScene( void );

		const String& GetName( void );

	private:
		typedef map< String, Camera* >::type	m_CameraList;
		typedef map< String, Mash* >::type		m_MashList;
		typedef map< String, Light* >::type		m_LightList;

		m_CameraList		m_Camera;
		m_MashList			m_Mash;
		m_LightList			m_Light;

		int					m_IdCounter;

		RootGroup*			m_RootGroup;
		Camera*				m_ActiveCamera;
		String				m_Name;
		IRenderConnect*		m_pConnect;
	};
}