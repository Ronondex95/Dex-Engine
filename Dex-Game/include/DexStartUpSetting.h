#pragma once

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <Dex.h>

namespace Dex
{
	class StartUpSetting : public wxDialog 
	{
	public:		
		StartUpSetting( wxWindow* parent = NULL, wxWindowID id = wxID_ANY, const wxString& title = wxT("Настройки графики"),
			const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,600 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~StartUpSetting();

	protected:
		void ClickGO( wxCommandEvent& event );

		void RenderSystemList( wxCommandEvent& WXUNUSED(event) );
		void ModeList( wxCommandEvent& WXUNUSED(event) );
		void DriverList( wxCommandEvent& WXUNUSED(event) );
		
	private:
		void _RenderSystemList( void );
		void _ModeList( void );

	private:
		Core*			m_pCore;
		IRenderSystem*	m_pRender;

		wxPanel*		m_PanelStyle;
		// Box 1
		wxStaticText*	m_Text1_B1;
		wxChoice*		m_RenderSystem_B1;
		// Box 2
		wxStaticText*	m_Text1_B2;
		wxChoice*		m_TypeFormat_B2;
		wxChoice*		m_ModeList_B2;
		// Box 3
		wxStaticText*	m_Text1_B3;
		wxChoice*		m_Driver_B3;
		// Box 4
		wxStaticText*	m_Text1_B4;
		wxChoice*		m_FullScrean_B4;

		wxButton*		m_BuutonGo;

		DECLARE_EVENT_TABLE()
	};
}