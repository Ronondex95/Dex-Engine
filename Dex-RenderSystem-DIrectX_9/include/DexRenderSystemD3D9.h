#pragma once

#include <DexPreCompletionD3D9.h>
#include <DexRenderSystem.h>

namespace Dex
{
	class D_EXPORT_D3D9 RenderSystemD3D9 : public IRenderSystem
	{
	public:
		RenderSystemD3D9( void );
		~RenderSystemD3D9( void );

	public:
		const StringVector& GetAvailableDisplayMode( void );
		const StringVector& GetAvailableAdpter( void );

		IRenderConnect* GetConnect( const String& name );

		IRenderWindow* CreateRenderWindow( const PairameterList& config );

	private:
		void InitSystem( void );
		void EnumerationAdapter( void );

	private:
		typedef map< String, RenderWindowD3D9* >::type	m_WindowList;
		typedef vector< RenderAdapterD3D9* >::type		m_DriverList;

		m_WindowList		m_Window;
		m_DriverList		m_Driver;

		// DirectX Setting
		IDirect3D9*			m_pD3D9;
	};
}