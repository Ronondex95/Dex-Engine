#pragma once

#include <DexPreCompletionD3D9.h>

namespace Dex
{
	class D_EXPORT_D3D9 RenderAdapterD3D9
	{
	public:
		RenderAdapterD3D9( UINT id, IDirect3D9* d3d9 );

		const StringVector& GetDisplayMode( void );
		const String& GetName( void );

	private:
		UINT					m_nId;
		String					m_Name;

		StringVector			m_DisplayMode;

		// DirectX Setting
		IDirect3D9*				m_pD3D9;
		D3DADAPTER_IDENTIFIER9	m_AdapterIdentifier;
	};
}