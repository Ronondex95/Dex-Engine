#pragma once

#include <DexPreCompletion.h>

namespace Dex
{
	class D_EXPORT IRenderSystem
	{
	public:
		const String& GetName( void );
		void SetActiveAdapter( UINT adapter );

	public:
		virtual const StringVector& GetAvailableDisplayMode( void ) = 0;
		virtual const StringVector& GetAvailableAdpter( void ) = 0;

		virtual IRenderConnect* GetConnect( const String& name ) = 0;

		virtual IRenderWindow* CreateRenderWindow( const PairameterList& config ) = 0;

	protected:
		String					m_Name;

		// Driver - Adapter
		UINT					m_ActiveAdapter;
		StringVector			m_AdapterList;
	};
}