#include <DexMashBufferD3D9.h>

namespace Dex
{
	MashBufferD3D9::MashBufferD3D9( const ArrayVertexList& vertex, const ArrayIndexList& index, IDirect3DDevice9* device )
	{
		m_pDevice9 = device;
		m_nIndex = index.size();
		m_nVertex = vertex.size();
		m_pMesh = NULL;

		D3DVERTEXELEMENT9 VERTEX_DECL[] =
		{
			{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION, 0},
			{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_NORMAL,   0},
			{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD, 0},
			D3DDECL_END()
		};

		D3DXCreateMesh( index.size() / 3, vertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT, VERTEX_DECL, m_pDevice9, &m_pMesh );

		VERTEX* pVertex;
		m_pMesh->LockVertexBuffer( 0, ( void** )&pVertex );
		memcpy( pVertex, vertex.data(), vertex.size() * sizeof( VERTEX ) );
		m_pMesh->UnlockVertexBuffer();

		DWORD* pIndex;
		m_pMesh->LockIndexBuffer( 0, ( void** )&pIndex );
		memcpy( pIndex, index.data(), index.size() * sizeof( DWORD ) );
		m_pMesh->UnlockIndexBuffer();

		Material* pMaterial = new Material();
		InitMaterial( pMaterial );
		m_Material.push_back( pMaterial );

		ZeroMemory( &m_Matirial, sizeof( D3DMATERIAL9 ) );
		m_Matirial.Diffuse.r = m_Matirial.Ambient.r = 1.0f;
		m_Matirial.Diffuse.g = m_Matirial.Ambient.g = 0.0f;
		m_Matirial.Diffuse.b = m_Matirial.Ambient.b = 1.0f;
		m_Matirial.Diffuse.a = m_Matirial.Ambient.a = 1.0f;
	}

	MashBufferD3D9::~MashBufferD3D9( void )
	{
	}

	void MashBufferD3D9::Draw( void )
	{
		m_pDevice9->SetMaterial( &m_Matirial );

		m_pMesh->DrawSubset( 0 );
	}

	void MashBufferD3D9::InitMaterial( Material* pMaterial )
	{
		ZeroMemory( pMaterial, sizeof( Material ) );

		pMaterial->Name = "Defaut";
		pMaterial->Ambient = D3DXVECTOR3( 0.2f, 0.2f, 0.2f );
		pMaterial->Diffuse = D3DXVECTOR3( 0.8f, 0.8f, 0.8f );
		pMaterial->Specular = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
		pMaterial->nShininess = 0;
		pMaterial->fAlpha = 1.0f;
		pMaterial->bSpecular = false;
		pMaterial->pTexture = NULL;
	}
}