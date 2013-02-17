#include <DexRenderWindowD3D9.h>
#include <DexStringConverter.h>
#include <DexCore.h>

namespace Dex
{
	RenderWindowD3D9::RenderWindowD3D9( UINT adapter, D3DDEVTYPE type, IDirect3D9* d3d9 )
	{
		m_nAdapter = adapter;
		m_DeviceType = type;
		m_pD3D9 = d3d9;

		ZeroMemory( &m_d3d_pp, sizeof( D3DPRESENT_PARAMETERS ) );
		m_pDevice9 = 0;
	}

	RenderWindowD3D9::~RenderWindowD3D9( void )
	{
		D_RELEASE( m_pDevice9 );
	}

	bool RenderWindowD3D9::Create( const PairameterList& config )
	{
		PairameterList::const_iterator it;

		it = config.find("window_name");
		if ( it != config.end() )
		{
			m_Name = it->second;
		}

		it = config.find("window_handle");
		if ( it != config.end() )
		{
			HWND h_Wnd = (HWND)StringConverter::Parse_size_t( it->second );
			m_d3d_pp.hDeviceWindow = h_Wnd;
		}
		else
		{
			Core::GetLog()->DrawLine("RenderWindowD3D9:Init \"window_handle\" не указан", MT_ERROR );
			return false;
		}

		m_d3d_pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_d3d_pp.EnableAutoDepthStencil = TRUE;
		m_d3d_pp.BackBufferFormat = D3DFMT_UNKNOWN;
		m_d3d_pp.BackBufferHeight = 0;
		m_d3d_pp.BackBufferWidth = 0;

		it = config.find("display_mode");
		if ( it != config.end() )
		{
			StringConverter::TakeDownDisplyaMode( it->second, m_nWidth, m_nHeight, m_nBit );
		}
		else
		{
			Core::GetLog()->DrawLine("RenderWindowD3D9:Init \"display_mode\" не указано", MT_WARNING );

			m_nWidth = 800;
			m_nHeight = 600;
			m_nBit = 32;
		}

		if ( m_nBit == 32 )
		{
			m_d3d_pp.BackBufferFormat = D3DFMT_X8R8G8B8;

			if ( FAILED( m_pD3D9->CheckDeviceFormat( m_nAdapter, m_DeviceType,
				D3DFMT_X8R8G8B8, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24S8 ) ) )
			{
				if ( FAILED( m_pD3D9->CheckDeviceFormat( m_nAdapter, m_DeviceType,
					D3DFMT_X8R8G8B8, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D32 ) ) )
				{
					m_d3d_pp.AutoDepthStencilFormat = D3DFMT_D16;
				}
				else
				{
					m_d3d_pp.AutoDepthStencilFormat = D3DFMT_D32;
				}
			}
			else
			{
				if ( SUCCEEDED( m_pD3D9->CheckDepthStencilMatch( m_nAdapter, m_DeviceType,
					D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, D3DFMT_D24S8 ) ) )
				{
					m_d3d_pp.AutoDepthStencilFormat = D3DFMT_D24S8;
				}
				else
				{
					m_d3d_pp.AutoDepthStencilFormat = D3DFMT_D24X8;
				}
			}
		}
		else if ( m_nBit == 16 )
		{
			m_d3d_pp.BackBufferFormat = D3DFMT_R5G6B5;
			m_d3d_pp.AutoDepthStencilFormat = D3DFMT_D16;
		}

		m_d3d_pp.BackBufferHeight = m_nHeight;
		m_d3d_pp.BackBufferWidth = m_nWidth;

		it = config.find( "full_screan_mode" );
		if ( it != config.end() )
		{
			if ( it->second == "on" )
			{
				m_FullScrean = true;
				m_d3d_pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
			}
			else if ( it->second == "off" )
			{
				m_FullScrean = false;
			}
			else
			{
				Core::GetLog()->DrawLine("RenderWindowD3D9:Init \"full_screan_mode\" значение не опознано \"on\" или \"off\"", MT_WARNING );
				m_FullScrean = false;
			}
		}

		m_VSync = false;

		m_d3d_pp.Windowed = !m_FullScrean;
		m_d3d_pp.BackBufferCount =  m_VSync ? 2 : 1;

		if ( !CreateDevice() )
		{
			return false;
		}

		m_pDevice9->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
		m_pDevice9->SetRenderState( D3DRS_ZENABLE, TRUE );

		D3DXMatrixPerspectiveFovLH( &m_ProjectionMatrix, D3DX_PI / 4, (FLOAT)m_nWidth / m_nHeight, 1.0f, 10000.0f );
		m_pDevice9->SetTransform( D3DTS_PROJECTION, &m_ProjectionMatrix );

		return true;
	}

	bool RenderWindowD3D9::IsLostControl( void )
	{
		HRESULT result = m_pDevice9->TestCooperativeLevel();

		String error = DXGetErrorDescription( result );
		if ( result != S_OK )
			Core::GetLog()->DrawLine("RenderWindowD3D9:IsLostControl Ошибка - " + error );

		if ( result == D3DERR_DEVICELOST )
		{
			return true;
		}
		else if ( result == D3DERR_DEVICENOTRESET )
		{
			// deinitresurse
			m_pDevice9->Reset( &m_d3d_pp );
			// initresurse

			return false;
		}

		return false;
	}

	bool RenderWindowD3D9::CreateDevice( void )
	{
		HRESULT result;

		result = m_pD3D9->CreateDevice( m_nAdapter, m_DeviceType, m_d3d_pp.hDeviceWindow,
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_d3d_pp, &m_pDevice9 );

		if ( SUCCEEDED( result ) )
		{
			return true;
		}

		result = m_pD3D9->CreateDevice( m_nAdapter, m_DeviceType, m_d3d_pp.hDeviceWindow,
			D3DCREATE_MIXED_VERTEXPROCESSING, &m_d3d_pp, &m_pDevice9 );

		if ( SUCCEEDED( result ) )
		{
			return true;
		}

		result = m_pD3D9->CreateDevice( m_nAdapter, m_DeviceType, m_d3d_pp.hDeviceWindow,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_d3d_pp, &m_pDevice9 );


		if ( FAILED( result ) )
		{
			String error = DXGetErrorDescription( result );
			Core::GetLog()->DrawLine("RenderWindowD3D9:CreateDevice Ошибка - " + error );

			return false;
		}

		return true;
	}

	void RenderWindowD3D9::SetMatrixIdentity( void )
	{
		D3DXMatrixIdentity( &m_WorldMatrix );
		D3DXMatrixIdentity( &m_ViewMatrix );
		m_LightCount = 0;
	}

	void RenderWindowD3D9::SetViewMatrix( const Point3& position, const Point3& target, const Point3& up )
	{
		D3DXVECTOR3 Eye( position.x, position.y, position.z );
		D3DXVECTOR3 LookAt( target.x, target.y, target.z );
		D3DXVECTOR3 Up( up.x, up.y, up.z );

		D3DXMatrixLookAtLH( &m_ViewMatrix, &Eye, &LookAt, &Up );

		m_pDevice9->SetTransform( D3DTS_VIEW, &m_ViewMatrix );
	}

	IVertexBuffer* RenderWindowD3D9::CreateVertexBuffer( void )
	{
		return new VertexBufferD3D9( m_pDevice9 );
	}

	void RenderWindowD3D9::SetVertexBuffer( IVertexBuffer* vertex )
	{
		m_VertexBuffer = vertex;
	}

	void RenderWindowD3D9::SetWorldMatrix( const Point3& position, const Point3& rotation, const Point3& scale )
	{
		D3DXMATRIX buffer;

		// Rotation X
		D3DXMatrixIdentity( &buffer );
		D3DXMatrixRotationX( &buffer, D3DXToRadian( rotation.x ) );
		D3DXMatrixMultiply( &m_WorldMatrix, &buffer, &m_WorldMatrix );

		// Rotation Y
		D3DXMatrixIdentity( &buffer );
		D3DXMatrixRotationY( &buffer, D3DXToRadian( rotation.y ) );
		D3DXMatrixMultiply( &m_WorldMatrix, &buffer, &m_WorldMatrix );

		// Rotation Z
		D3DXMatrixIdentity( &buffer );
		D3DXMatrixRotationZ( &buffer, D3DXToRadian( rotation.z ) );
		D3DXMatrixMultiply( &m_WorldMatrix, &buffer, &m_WorldMatrix );

		// Scaling
		D3DXMatrixIdentity( &buffer );
		D3DXMatrixScaling( &buffer, scale.x, scale.y, scale.z );
		D3DXMatrixMultiply( &m_WorldMatrix, &buffer, &m_WorldMatrix );

		// Translation
		D3DXMatrixIdentity( &buffer );
		D3DXMatrixTranslation( &buffer, position.x, position.y, position.z );
		D3DXMatrixMultiply( &m_WorldMatrix, &buffer, &m_WorldMatrix );

		m_pDevice9->SetTransform( D3DTS_WORLD, &m_WorldMatrix );
	}

	bool RenderWindowD3D9::LoadMash( const String& file, IVertexBuffer** ppVertexBuffer )
	{

		/*MashBufferD3D9* mash = new MashBufferD3D9( m_pDevice9 );

		if ( mash->LoadOBJ( file ) )
		{
			m_MashBuffer.push_back( mash );

			return true;
		}

		delete mash;*/

		return false;
	}

	bool RenderWindowD3D9::AddLight( const Point3& position, const Point4& color )
	{
		D3DLIGHT9 light;
		ZeroMemory( &light, sizeof( D3DLIGHT9 ) );

		light.Type = D3DLIGHT_DIRECTIONAL;

		light.Position.x = position.x;
		light.Position.z = position.z;
		light.Position.y = position.y;

		light.Diffuse.r = color.x;
		light.Diffuse.g = color.y;
		light.Diffuse.b = color.z;
		light.Diffuse.a = color.w;

		light.Direction = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );

		light.Range = 1000.0f;

		m_pDevice9->SetLight( m_LightCount, &light );
		m_pDevice9->LightEnable( m_LightCount, TRUE );

		m_LightCount++;

		return true;
	}

	bool RenderWindowD3D9::LoadOBJ( const String& file )
	{
		IFStream stream( file.c_str() );

		if ( stream )
		{
			vector< D3DXVECTOR3 >::type Positions;
			vector< D3DXVECTOR2 >::type TexCoords;
			vector< D3DXVECTOR3 >::type Normals;

			ArrayIndexList	m_ArrayIndex;
			ArrayVertexList	m_ArrayVertex;

			char cahr_line[256] = {0};
			char material_filename[256] = {0};

			while ( stream )
			{
				stream >> cahr_line;

				if ( std::strcmp( cahr_line, "#" ) == 0 )
				{
					// comment
				}
				else if ( std::strcmp( cahr_line, "v" ) == 0 )
				{
					float x, y, z;
					stream >> x >> y >> z;
					Positions.push_back( D3DXVECTOR3( x, y, z ) );
				}
				else if ( std::strcmp( cahr_line, "vt" ) == 0 )
				{
					float u, v;
					stream >> u >> v;
					TexCoords.push_back( D3DXVECTOR2( u, v ) );
				}
				else if ( std::strcmp( cahr_line, "vn" ) == 0 )
				{
					float x, y, z;
					stream >> x >> y >> z;
					Normals.push_back( D3DXVECTOR3( x, y, z ) );
				}
				else if ( std::strcmp( cahr_line, "f" ) == 0 )
				{
					UINT position, texcoord, normal;
					VERTEX vertex;

					for( UINT nFace = 0; nFace < 3; nFace++ )
					{
						ZeroMemory( &vertex, sizeof( VERTEX ) );

						stream >> position;
						vertex.position = Positions[ position - 1 ];

						if( '/' == stream.peek() )
						{
							stream.ignore();

							if( '/' != stream.peek() )
							{
								stream >> texcoord;
								vertex.texcoord = TexCoords[ texcoord - 1 ];
							}

							if( '/' == stream.peek() )
							{
								stream.ignore();

								stream >> normal;
								vertex.normal = Normals[ normal - 1 ];
							}
						}

						int res = -1;

						for ( size_t i = 0; i < m_ArrayVertex.size(); i++ )
						{
							if ( memcmp( &m_ArrayVertex[i], &vertex, sizeof(VERTEX) ) == 0 )
							{
								res = i;
							}
						}

						if ( res < 0 )
						{
							m_ArrayVertex.push_back( vertex );
							res = m_ArrayVertex.size() - 1;
						}
						
						m_ArrayIndex.push_back( res );
					}
				}
				/*else if ( std::strcmp( cahr_line, "mtllib" ) == 0 )
				{
					// Material library
					stream >> material_filename;
				}
				else if ( std::strcmp( cahr_line, "usemtl" ) == 0 )
				{
					// Material
					stream >> cahr_line;

					bool bFound = false;
					for( int iMaterial = 0; iMaterial < m_Materials.si(); iMaterial++ )
					{
						Material* pCurMaterial = m_Materials.GetAt( iMaterial );
						if( 0 == wcscmp( pCurMaterial->strName, strName ) )
						{
							bFound = true;
							dwCurSubset = iMaterial;
							break;
						}
					}

					if( !bFound )
					{
						pMaterial = new Material();
						if( pMaterial == NULL )
							return E_OUTOFMEMORY;

						dwCurSubset = m_Materials.GetSize();

						InitMaterial( pMaterial );
						wcscpy_s( pMaterial->strName, MAX_PATH - 1, strName );

						m_Materials.Add( pMaterial );
					}
				}
				else
				{
					// Unimplemented or unrecognized command
				}*/
			}

			stream.close();

			MashBufferD3D9* buffer = new MashBufferD3D9( m_ArrayVertex, m_ArrayIndex, m_pDevice9 );

			m_MashBuffer.push_back( buffer );

			return true;
		}

		return false;
	}

	bool RenderWindowD3D9::PreRender( void )
	{
		if ( SUCCEEDED( m_pDevice9->BeginScene() ) )
		{
			return true;
		}

		return false;
	}

	void RenderWindowD3D9::Render( PRIMATIVE_TYPE )
	{
		m_pDevice9->SetRenderState( D3DRS_LIGHTING, TRUE );
		m_pDevice9->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_XRGB( 255, 0, 0 ) );

		D3DPRIMITIVETYPE PrimitiveType = D3DPT_TRIANGLELIST;

		if ( PRIMATIVE_TYPE )
		{

			hr = m_pDevice9->DrawIndexedPrimitive( PrimitiveType, static_cast<INT>(op.vertexData->vertexStart), 0, static_cast<UINT>(op.vertexData->vertexCount), static_cast<UINT>(op.indexData->indexStart), static_cast<UINT>(primCount) );
		}

	}


	void RenderWindowD3D9::PostRender( void )
	{
		m_pDevice9->EndScene();
	}

	void RenderWindowD3D9::Clear( void )
	{
		m_pDevice9->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 28, 128 ), 1.0f, 0 );
	}

	void RenderWindowD3D9::Present( void )
	{
		m_pDevice9->Present( 0, 0, 0, 0 );
	}
}
