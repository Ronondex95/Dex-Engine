#pragma once

#include <DexPreCompletionD3D9.h>

namespace Dex
{
	#define D3DFVF_VERTEX ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 )
	struct VERTEX
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DXVECTOR2 texcoord;
	};
	typedef vector< VERTEX >::type		ArrayVertexList;
	typedef vector< DWORD >::type		ArrayIndexList;

	struct Material
	{
		String   Name;

		D3DXVECTOR3 Ambient;
		D3DXVECTOR3 Diffuse;
		D3DXVECTOR3 Specular;

		int nShininess;
		float fAlpha;

		bool bSpecular;

		String   Texture;
		IDirect3DTexture9* pTexture;
		D3DXHANDLE hTechnique;
	};
}