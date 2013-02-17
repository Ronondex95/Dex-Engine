#pragma once

#include <DexPreCompletion.h>
#include <DexRenderSystem.h>
#include <DexLog.h>

namespace Dex
{
	class D_EXPORT Core
	{
	public:
		Core( const String& logname = "DexLog.html", const String& configfile = "DexConfig.cfg" );
		~Core( void );

		// Dynamic Library
		bool LoadModule( const String& filename );
		bool UnLoadModule( const String& filename );

		// Render System
		void AddRenderSystem( IRenderSystem* system );
		void RemoveRenderSystem( IRenderSystem* system );
		const StringVector& AvailableRenderSystem( void );
		IRenderSystem* ChangeRenderSystem( const String& system );

		// Scene System
		Scene* CreateScene( const String& namescene, const String& render_window );
		Scene* GetScene( const String& namescene );

		// Render
		void RenderOneFrame( void );

		// Get
		static Core* GetCore( void );
		static Log* GetLog( void );
		static IRenderSystem* GetRenderSystem( void );

	private:
		// Systems
		static Core*			m_pCore;
		static Log*				m_pLog;
		static IRenderSystem*	m_pRenderSystem;

		typedef map< String, Scene* >::type				m_SceneList;
		typedef vector< IRenderSystem* >::type			m_RenderSystemList;
		typedef map< String, DynamicLibrary* >::type	m_DynamicLibraryList;

		m_DynamicLibraryList	m_DynamicLibrary;
		m_RenderSystemList		m_RenderSystem;
		StringVector			m_AvailableRenderList;
		m_SceneList				m_Scene;
	};
}