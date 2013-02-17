#pragma once

#include <DexPreCompletionD3D9.h>
#include <DexRenderWindow.h>
#include <DexRenderConnect.h>
#include <DexMashBufferD3D9.h>
#include <DexBufferStructureD3D9.h>
#include <DexVertexBuffer.h>
#include <DexVertexBufferD3D9.h>

namespace Dex
{
	class D_EXPORT_D3D9 RenderWindowD3D9 : public IRenderWindow, public IRenderConnect
	{
	public:
		RenderWindowD3D9( UINT adapter, D3DDEVTYPE type, IDirect3D9* d3d9 );
		~RenderWindowD3D9( void );

		bool Create( const PairameterList& config );

	public:
		// connect
		void SetMatrixIdentity( void );
		void SetViewMatrix( const Point3& position, const Point3& target, const Point3& up );
		void SetWorldMatrix( const Point3& position, const Point3& rotation, const Point3& scale );

		IVertexBuffer* CreateVertexBuffer( void );
		void SetVertexBuffer( IVertexBuffer* vertex );

		bool LoadMash( const String& file, IVertexBuffer** ppVertexBuffer );
		bool AddLight( const Point3& position, const Point4& color );
		bool LoadOBJ( const String& file );

		bool IsLostControl( void );
		bool PreRender( void );
		void Render( int nMashId );
		void PostRender( void );
		void Clear( void );
		void Present( void );

	private:
		bool CreateDevice( void );

	private:
		typedef vector< MashBufferD3D9* >::type			m_MashBufferList;

		int							m_LightCount;
		m_MashBufferList			m_MashBuffer;

		IVertexBuffer*				m_VertexBuffer;

		HWND						m_hWnd;

		D3DXMATRIX					m_WorldMatrix;
		D3DXMATRIX					m_ViewMatrix;
		D3DXMATRIX					m_ProjectionMatrix;

		// DirectX Setting
		IDirect3D9*					m_pD3D9;
		IDirect3DDevice9*			m_pDevice9;

		UINT						m_nAdapter;
		D3DDEVTYPE					m_DeviceType;

		D3DPRESENT_PARAMETERS		m_d3d_pp;
	};
}