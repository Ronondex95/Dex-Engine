#pragma once

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <DexStartUpSetting.h>
#include <Dex.h>
#include <DexEvent.h>

namespace Dex
{
	class GeneralFrame : public wxFrame 
	{
	public:
		
		GeneralFrame( const wxString& title ); 
		~GeneralFrame( void );

	protected:
		virtual void Update( wxUpdateUIEvent& event );
		virtual void Keys( wxKeyEvent& event );

	private:
		void Loop( void );
		void RenderLoop( bool stop );
		void CreateSimpleScene( void );

	private:
		Core*			m_pCore;
		IRenderSystem*	m_pRender;
		Camera*			m_pPlayer;

		Scene*			m_pScene;
		Group*			m_RootGroup;
		Mash*			m_pMash1;
		Light*			m_pLight1;
		Light*			m_pLight2;

		Event*			m_Event;

		DECLARE_EVENT_TABLE()
	};
}