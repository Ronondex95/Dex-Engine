#pragma once

#include <DexPreCompletionD3D9.h>
#include <DexBufferStructureD3D9.h>

namespace Dex
{
	class D_EXPORT_D3D9 MashBufferD3D9
	{
	public:
		MashBufferD3D9( const ArrayVertexList& vertex, const ArrayIndexList& index, IDirect3DDevice9* device );
		~MashBufferD3D9( void );

		void Draw( void );

		void InitMaterial( Material* pMaterial );

	private:
		typedef vector< Material* >::type	m_MaterialList;

		m_MaterialList				m_Material;

		// DirectX Setting
		IDirect3DDevice9*			m_pDevice9;

		D3DMATERIAL9				m_Matirial;

		int							m_nIndex;
		int							m_nVertex;

		ID3DXMesh*					m_pMesh;
	};
}