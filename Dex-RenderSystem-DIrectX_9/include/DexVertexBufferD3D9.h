#pragma once

#include <DexPreCompletionD3D9.h>
#include <DexBufferStructureD3D9.h>
#include <DexVertexBuffer.h>

namespace Dex
{
	class D_EXPORT VertexBufferD3D9 : public IVertexBuffer
	{
	public:
		VertexBufferD3D9( IDirect3DDevice9* device )
		{
			m_pDevice9 = device;
			m_nVertex = 0;
		}

		void CreateBuffer( const VertexType& type )
		{
			if ( type == VT_PNT )
			{
				m_pDevice9->CreateVertexBuffer( m_nVertex * sizeof( VERTEX ), 0, D3DFVF_VERTEX, D3DPOOL_DEFAULT, &m_VertexBuffer, NULL );
			}
		}

	private:
		// DirectX Setting
		IDirect3DDevice9*			m_pDevice9;
		IDirect3DVertexBuffer9*		m_VertexBuffer;
	};
}