#include <DexRenderAdapterD3D9.h>
#include <DexCore.h>

namespace Dex
{
	RenderAdapterD3D9::RenderAdapterD3D9( UINT id, IDirect3D9* d3d9 )
	{
		m_nId = id;
		m_pD3D9 = d3d9;

		StringStream Description;

		m_pD3D9->GetAdapterIdentifier( m_nId, 0, &m_AdapterIdentifier );

		Description << m_AdapterIdentifier.Description;
		m_Name = Description.str();

		// Adapter Format
		const D3DFORMAT AdapterFormatArray[] = {
			/*D3DFMT_A2R10G10B10, // 32-битный пиксельный формат, когда 10 битов резервируются для каждого цвета и 2 бита резервируются для альфа смешивания (прозрачный тексель)*/
			D3DFMT_X8R8G8B8,	// 32-битный RGB пиксельный формат, когда 8 бит резервируется для каждого цвета
			/*D3DFMT_X1R5G5B5,	// 16-битный пиксельный формат, когда 5 бит резервируется для каждого цвета*/
            D3DFMT_R5G6B5		// 16-битный RGB пиксельный формат
		};
		const int nAdapterFormatCount = sizeof ( AdapterFormatArray ) / sizeof ( D3DFORMAT );

		for ( int nAdapterFormat = 0; nAdapterFormat < nAdapterFormatCount; nAdapterFormat++ )
		{
			const int nAdapterModeCount = m_pD3D9->GetAdapterModeCount( m_nId, AdapterFormatArray[nAdapterFormat] );

			for ( int nMode = 0; nMode < nAdapterModeCount; nMode++ )
			{
				D3DDISPLAYMODE DisplayMode;
				StringStream mode;

				m_pD3D9->EnumAdapterModes( m_nId, AdapterFormatArray[nAdapterFormat], nMode, &DisplayMode );

				// Min
				if ( DisplayMode.Width < 800 || DisplayMode.Height < 600 )
					continue;

				// Max
				if ( DisplayMode.Width > UINT_MAX || DisplayMode.Height > UINT_MAX )
					continue;

				if ( DisplayMode.Format == D3DFMT_X8R8G8B8 )
				{
					mode << DisplayMode.Width << "x" << DisplayMode.Height << "-32 bit";
					m_DisplayMode.push_back( mode.str() );
				}
				else if ( DisplayMode.Format == D3DFMT_R5G6B5 )
				{
					mode << DisplayMode.Width << "x" << DisplayMode.Height << "-16 bit";
					m_DisplayMode.push_back( mode.str() );
				}
			}
		}

		Core::GetLog()->DrawLine( "RenderAdapterD3D9: Обноружено устройство " + m_Name );
	}

	const StringVector& RenderAdapterD3D9::GetDisplayMode( void )
	{
		return m_DisplayMode;
	}

	const String& RenderAdapterD3D9::GetName( void )
	{
		return m_Name;
	}
}