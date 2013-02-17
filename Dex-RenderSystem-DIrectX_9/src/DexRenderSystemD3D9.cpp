#include <DexRenderSystemD3D9.h>
#include <DexRenderWindowD3D9.h>
#include <DexRenderAdapterD3D9.h>
#include <DexCore.h>

namespace Dex
{
	RenderSystemD3D9::RenderSystemD3D9( void )
	{
		m_Name = "DirectX 9";
		m_pD3D9 = Direct3DCreate9( D3D_SDK_VERSION );
		m_ActiveAdapter = D3DADAPTER_DEFAULT;

		InitSystem();
		EnumerationAdapter();

		Core::GetLog()->DrawLine("RenderSystemD3D9: Модуль Directx 11 инициализирован");
	}

	RenderSystemD3D9::~RenderSystemD3D9( void )
	{
		Core::GetLog()->DrawLine( "RenderSystemD3D9: Модуль Directx 9 выгружен" );

		D_RELEASE( m_pD3D9 );
	}

	void RenderSystemD3D9::InitSystem( void )
	{
	}

	void RenderSystemD3D9::EnumerationAdapter( void )
	{
		for ( UINT i = 0; i < m_pD3D9->GetAdapterCount(); i++ )
		{
			m_Driver.push_back( new RenderAdapterD3D9( i, m_pD3D9 ) );

			m_AdapterList.push_back( m_Driver.at( i )->GetName() );
		}
	}

	const StringVector& RenderSystemD3D9::GetAvailableDisplayMode( void )
	{
		return m_Driver.at( m_ActiveAdapter )->GetDisplayMode();
	}

	const StringVector& RenderSystemD3D9::GetAvailableAdpter( void )
	{
		return m_AdapterList;
	}

	IRenderConnect* RenderSystemD3D9::GetConnect( const String& name )
	{
		return m_Window[name];
	}

	IRenderWindow* RenderSystemD3D9::CreateRenderWindow( const PairameterList& config )
	{
		PairameterList::const_iterator it;

		D3DDEVTYPE type = D3DDEVTYPE_HAL;

		it = config.find("device_type");
		if ( it != config.end() )
		{
			if ( it->second == "Software" )
			{
				type = D3DDEVTYPE_REF;
			}
		}

		it = config.find("window_name");
		if ( it != config.end() )
		{
			m_WindowList::iterator it_find_window = m_Window.find( it->second );

			if ( it_find_window == m_Window.end() )
			{
				RenderWindowD3D9* window = new RenderWindowD3D9( m_ActiveAdapter, type, m_pD3D9 );

				if ( window->Create( config ) )
				{
					m_Window[it->second] = window;

					return window;
				}
			}
			else
			{
				Core::GetLog()->DrawLine("RenderSystemD3D9: Окно " + it->second + " уже существует", MT_WARNING );
			}
		}
		else
		{
			Core::GetLog()->DrawLine("RenderSystemD3D9: Не указано имя создаваемого окна!", MT_WARNING );
		}

		return NULL;
	}
}