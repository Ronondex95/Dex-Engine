#include <DexCore.h>
#include <DexConfigFile.h>
#include <DexDynamicLibrary.h>
#include <DexScene.h>

namespace Dex
{
	Core* Core::m_pCore = 0;
	Log* Core::m_pLog = 0;
	IRenderSystem* Core::m_pRenderSystem = 0;

	Core* Core::GetCore( void )
	{
		assert( m_pCore );
		return m_pCore;
	}
	Log* Core::GetLog( void )
	{
		assert( m_pLog );
		return m_pLog;
	}
	IRenderSystem* Core::GetRenderSystem( void )
	{
		assert( m_pRenderSystem );
		return m_pRenderSystem;
	}

	Core::Core( const String& logname, const String& configfile )
	{
		m_pCore = this;
		m_pLog = new Log( logname );

		ConfigFile config_file( configfile );
		PairameterList::const_iterator it_parametor;
		const ConfigList& config = config_file.GetConfig();
		for ( size_t i = 0; i < config.size(); ++i )
		{
			if ( config.at( i ).first == "load_module" )
			{
				LoadModule( config.at( i ).second );
			}
		}

		Core::GetLog()->DrawLine("Core: Загрузка завершена!");
	}

	Core::~Core( void )
	{
		m_DynamicLibraryList::iterator it;
		for ( it = m_DynamicLibrary.begin(); it != m_DynamicLibrary.end(); ++it )
		{
			UnLoadModule( it->first );
		}
		m_DynamicLibrary.clear();

		Core::GetLog()->DrawLine("Core: Завершение работы!");
	}

	// Dynamic Library
	typedef void (*START_DLL_MODULE)( void );
	typedef void (*STOP_DLL_MODULE)( void );

	bool Core::LoadModule( const String& filename )
	{
		m_DynamicLibraryList::iterator it = m_DynamicLibrary.find( filename );

		if ( it == m_DynamicLibrary.end() )
		{
			DynamicLibrary* pModule = new DynamicLibrary( filename );

			if ( pModule->CheckWork() )
			{
				START_DLL_MODULE pFunc = (START_DLL_MODULE)pModule->GetAddress("Start_DexDynamicLibrary");
				pFunc();

				m_DynamicLibrary[filename] = pModule;

				return true;
			}
			else
			{
				Core::GetLog()->DrawLine("Core: Модуль " + filename + " не работает!", MT_ERROR );
			}
		}
		else
		{
			Core::GetLog()->DrawLine("Core: Модуль " + filename + " уже загружен", MT_WARNING );
		}

		return false;
	}

	bool Core::UnLoadModule( const String& filename )
	{
		m_DynamicLibraryList::iterator it = m_DynamicLibrary.find( filename );
		if ( it != m_DynamicLibrary.end() )
		{
			STOP_DLL_MODULE pFunc = (STOP_DLL_MODULE)m_DynamicLibrary[filename]->GetAddress("Stop_DexDynamicLibrary");
			pFunc();

			return true;
		}
		else
		{
			Core::GetLog()->DrawLine("Core: Модуль " + filename + " не загружен", MT_WARNING );
		}

		return false;
	}

	// Render System
	void Core::AddRenderSystem( IRenderSystem* system )
	{
		m_RenderSystemList::iterator it = std::find( m_RenderSystem.begin(), m_RenderSystem.end(), system );

		if ( m_RenderSystem.end() == it )
		{
			m_RenderSystem.push_back( system );
			m_AvailableRenderList.push_back( system->GetName() );
		}
	}

	void Core::RemoveRenderSystem( IRenderSystem* system )
	{
		m_RenderSystemList::iterator it = std::find( m_RenderSystem.begin(), m_RenderSystem.end(), system );
		StringVector::iterator vector_it = std::find( m_AvailableRenderList.begin(), m_AvailableRenderList.end(), system->GetName() );

		if ( m_RenderSystem.end() != it )
		{
			if ( m_pRenderSystem = system )
			{
				m_pRenderSystem = 0;
			}

			m_RenderSystem.erase( it );
			m_AvailableRenderList.erase( vector_it );
		}
	}

	const StringVector& Core::AvailableRenderSystem( void )
	{
		return m_AvailableRenderList;
	}

	IRenderSystem* Core::ChangeRenderSystem( const String& system )
	{
		if ( m_pRenderSystem && m_pRenderSystem->GetName() == system )
		{
			Core::GetLog()->DrawLine("Core: Данная система визуализации уже инициализирована!");
		}
		else
		{
			for ( size_t i = 0; i < m_RenderSystem.size(); ++i )
			{
				if ( m_RenderSystem.at( i )->GetName() == system )
				{
					m_pRenderSystem = m_RenderSystem.at( i );
					break;
				}
			}
		}

		if ( !m_pRenderSystem )
		{
			Core::GetLog()->DrawLine("Core: Не инициализировано ни одной системы визуализации!", MT_WARNING );
		}

		return m_pRenderSystem;
	}

	// Scene System
	Scene* Core::CreateScene( const String& namescene, const String& render_window )
	{
		m_SceneList::iterator it = m_Scene.find( namescene );

		if ( it == m_Scene.end() )
		{
			m_Scene[namescene] = new Scene( namescene, render_window );
		}
		else
		{
			Core::GetLog()->DrawLine("Core:CreateScene: " + namescene + " Уже сцществует", MT_WARNING );
		}

		return m_Scene[namescene];
	}

	Scene* Core::GetScene( const String& namescene )
	{
		return m_Scene[namescene];
	}

	void Core::RenderOneFrame( void )
	{
		m_SceneList::iterator it;
		for ( it = m_Scene.begin(); it != m_Scene.end(); ++it )
		{
			it->second->RenderScene();
		}
	}
}