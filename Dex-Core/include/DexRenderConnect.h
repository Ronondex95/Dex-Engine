#pragma once

#include <DexPreCompletion.h>
#include <DexMath.h>

namespace Dex
{
	class D_EXPORT IRenderConnect
	{
	public:
		virtual void SetMatrixIdentity( void ) = 0;
		virtual void SetViewMatrix( const Point3& position, const Point3& target, const Point3& up ) = 0;
		virtual void SetWorldMatrix( const Point3& position, const Point3& rotation, const Point3& scale ) = 0;

		virtual IVertexBuffer* CreateVertexBuffer( void ) = 0;
		virtual void SetVertexBuffer( IVertexBuffer* vertex ) = 0;

		virtual bool LoadMash( const String& file, IVertexBuffer** ppVertexBuffer ) = 0;
		virtual bool AddLight( const Point3& position, const Point4& color ) = 0;
		virtual bool LoadOBJ( const String& file ) = 0;

		virtual bool IsLostControl( void ) = 0;
		virtual bool PreRender( void ) = 0;
		virtual void Render( int nMashId ) = 0;
		virtual void PostRender( void ) = 0;
		virtual void Clear( void ) = 0;
		virtual void Present( void ) = 0;
	};
}