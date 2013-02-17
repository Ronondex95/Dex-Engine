#include <DexStartUpSetting.h>

namespace Dex
{
	enum
	{
		ID_M_PANELSTYLE = 1000,
		ID_M_TEXT_B1,
		ID_M_CHOICE_RENDERSYSTEM_B1,
		ID_M_CHOICE_MODELIST_B2,
		ID_M_CHOICE_TYPEFORMAT_B2,
		ID_M_CHOICE_DRIVER_B3,
		ID_M_CHOICE_FULLSCREAN_B3
	};

	BEGIN_EVENT_TABLE( StartUpSetting, wxDialog )
		EVT_BUTTON( wxID_OK, StartUpSetting::ClickGO )
		EVT_CHOICE( ID_M_CHOICE_RENDERSYSTEM_B1, StartUpSetting::RenderSystemList )
		EVT_CHOICE( ID_M_CHOICE_TYPEFORMAT_B2, StartUpSetting::ModeList )
		EVT_CHOICE( ID_M_CHOICE_DRIVER_B3, StartUpSetting::DriverList )
	END_EVENT_TABLE()

	StartUpSetting::StartUpSetting( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style )
		: wxDialog( parent, id, title, pos, size, style )
	{
		m_pCore = Core::GetCore();

		this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
		wxBoxSizer* m_Sizer_Global;
		m_Sizer_Global = new wxBoxSizer( wxVERTICAL );
	
		m_PanelStyle = new wxPanel( this, ID_M_PANELSTYLE, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
		wxBoxSizer* m_Sizer_Work;
		m_Sizer_Work = new wxBoxSizer( wxVERTICAL );
		
		// Box 1
		wxBoxSizer* m_B1;
		m_B1 = new wxBoxSizer( wxHORIZONTAL );
	
		m_Text1_B1 = new wxStaticText( m_PanelStyle, ID_M_TEXT_B1, wxT("Система визуализации:"), wxDefaultPosition, wxDefaultSize, 0 );
		m_Text1_B1->Wrap( -1 );
		m_B1->Add( m_Text1_B1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
		wxArrayString m_RenderSystem_Array;
		const StringVector& systems = m_pCore->AvailableRenderSystem();
		for ( size_t i = 0; i < systems.size(); ++i )
		{
			m_RenderSystem_Array.Add( systems.at( i ) );
		}
		int m_RenderSystem_Size = sizeof( m_RenderSystem_Array ) / sizeof( wxString );
		m_RenderSystem_B1 = new wxChoice( m_PanelStyle, ID_M_CHOICE_RENDERSYSTEM_B1, wxDefaultPosition, wxSize( 300,-1 ), m_RenderSystem_Array, m_RenderSystem_Size );
		m_RenderSystem_B1->SetSelection( 0 );
		_RenderSystemList();
		m_B1->Add( m_RenderSystem_B1, 1, wxALL, 5 );
	
		m_Sizer_Work->Add( m_B1, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 15 );
		
		// Box 2
		wxBoxSizer* m_B2;
		m_B2 = new wxBoxSizer( wxHORIZONTAL );
	
		m_Text1_B2 = new wxStaticText( m_PanelStyle, ID_M_TEXT_B1, wxT("Разрешенние:"), wxDefaultPosition, wxDefaultSize, 0 );
		m_Text1_B2->Wrap( -1 );
		m_B2->Add( m_Text1_B2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
		wxString m_TypeFormat_Array[] = { wxT("4:3"), wxT("16:9"), wxT("16:10") };
		int m_TypeFormat_Size = sizeof( m_TypeFormat_Array ) / sizeof( wxString );
		m_TypeFormat_B2 = new wxChoice( m_PanelStyle, ID_M_CHOICE_TYPEFORMAT_B2, wxDefaultPosition, wxSize( 60,-1 ), m_TypeFormat_Size, m_TypeFormat_Array, 0 );
		m_TypeFormat_B2->SetSelection( 1 );
		m_B2->Add( m_TypeFormat_B2, 0, wxALL, 5 );
		
		m_ModeList_B2 = new wxChoice( m_PanelStyle, ID_M_CHOICE_MODELIST_B2, wxDefaultPosition, wxSize( 300,-1 ) );
		m_B2->Add( m_ModeList_B2, 1, wxALL, 5 );
	
		m_Sizer_Work->Add( m_B2, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 15 );

		// Box 3
		wxBoxSizer* m_B3;
		m_B3 = new wxBoxSizer( wxHORIZONTAL );
		
		m_Text1_B3 = new wxStaticText( m_PanelStyle, ID_M_TEXT_B1, wxT("Render Driver:"), wxDefaultPosition, wxDefaultSize, 0 );
		m_Text1_B3->Wrap( -1 );
		m_B3->Add( m_Text1_B3, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

		wxArrayString m_Driver_Array;
		const StringVector& Config = Core::GetRenderSystem()->GetAvailableAdpter();
		for ( size_t i = 0; i < Config.size(); ++i )
		{
			m_Driver_Array.Add( Config.at( i ) );
		}
		int m_Driver_Size = sizeof( m_Driver_Array ) / sizeof( wxString );
		m_Driver_B3 = new wxChoice( m_PanelStyle, ID_M_CHOICE_DRIVER_B3, wxDefaultPosition, wxSize( 300,-1 ), m_Driver_Array, m_Driver_Size );
		m_Driver_B3->SetSelection( 0 );
		Core::GetRenderSystem()->SetActiveAdapter( 0 );
		m_B3->Add( m_Driver_B3, 1, wxALL, 5 );
	
		m_Sizer_Work->Add( m_B3, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 15 );

		// Box 4
		wxBoxSizer* m_B4;
		m_B4 = new wxBoxSizer( wxHORIZONTAL );
	
		m_Text1_B4 = new wxStaticText( m_PanelStyle, ID_M_TEXT_B1, wxT("Полноэкранный режим:"), wxDefaultPosition, wxDefaultSize, 0 );
		m_Text1_B4->Wrap( -1 );
		m_B4->Add( m_Text1_B4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
		wxString m_FullScrean_Array[] = { wxT("Да"), wxT("Нет") };
		int m_FullScrean_Size = sizeof( m_FullScrean_Array ) / sizeof( wxString );
		m_FullScrean_B4 = new wxChoice( m_PanelStyle, ID_M_CHOICE_FULLSCREAN_B3, wxDefaultPosition, wxSize( 300,-1 ), m_FullScrean_Size, m_FullScrean_Array, 0 );
		m_FullScrean_B4->SetSelection( 0 );
		m_B4->Add( m_FullScrean_B4, 1, wxALL, 5 );
	
		m_Sizer_Work->Add( m_B4, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 15 );
	
	
		m_Sizer_Work->Add( 0, 0, 1, wxEXPAND, 5 );
	
		wxBoxSizer* m_BStart;
		m_BStart = new wxBoxSizer( wxVERTICAL );
	
		m_BuutonGo = new wxButton( m_PanelStyle, wxID_OK, wxT("Играть!"), wxDefaultPosition, wxSize( -1,50 ), 0 );
		m_BStart->Add( m_BuutonGo, 1, wxEXPAND, 5 );
	
		m_Sizer_Work->Add( m_BStart, 0, wxEXPAND|wxALL, 5 );
	
		m_PanelStyle->SetSizer( m_Sizer_Work );
		m_PanelStyle->Layout();
		m_Sizer_Work->Fit( m_PanelStyle );
		m_Sizer_Global->Add( m_PanelStyle, 1, wxEXPAND, 5 );
	
		this->SetSizer( m_Sizer_Global );
		this->Layout();
	
		this->Centre( wxBOTH );

		_ModeList();
		m_TypeFormat_B2->SetSelection( 1 );
		m_ModeList_B2->SetSelection( 1 );
		m_FullScrean_B4->SetSelection( 1 );
	}

	StartUpSetting::~StartUpSetting()
	{
	}

	void StartUpSetting::ClickGO( wxCommandEvent& event )
	{
		PairameterList win;
		win["window_handle"] = StringConverter::toString( (int)GetParent()->GetHWND() );

		if ( m_FullScrean_B4->GetStringSelection() == "Да" )
		{
			win["full_screan_mode"] = "on";
		}
		else if ( m_FullScrean_B4->GetStringSelection() == "Нет" )
		{
			win["full_screan_mode"] = "off";
		}
		win["display_mode"] = m_ModeList_B2->GetStringSelection();
		win["window_name"] = "General-Window";

		IRenderWindow* window = Core::GetRenderSystem()->CreateRenderWindow( win );


		int w, h, b;
		StringConverter::TakeDownDisplyaMode( win["display_mode"], w, h, b );

		GetParent()->SetSize( w, h );
		GetParent()->Center( wxBOTH );
		GetParent()->Show();

		Destroy();
	}

	void StartUpSetting::RenderSystemList( wxCommandEvent& WXUNUSED(event) )
	{
		_RenderSystemList();
		_ModeList();
	}

	void StartUpSetting::_RenderSystemList( void )
	{
		StringStream system;
		system << m_RenderSystem_B1->GetStringSelection();

		m_pCore->ChangeRenderSystem( system.str() );
	}

	void StartUpSetting::DriverList( wxCommandEvent& WXUNUSED(event) )
	{
		Core::GetRenderSystem()->SetActiveAdapter( m_Driver_B3->GetSelection() );
		_ModeList();
	}

	void StartUpSetting::ModeList( wxCommandEvent& WXUNUSED(event) )
	{
		_ModeList();
	}

	void StartUpSetting::_ModeList( void )
	{
		if ( !Core::GetRenderSystem() )
			return;

		int a, b = 0;
		m_ModeList_B2->Clear();

		if ( m_TypeFormat_B2->GetSelection() == 0 )
		{
			a = 4;
			b = 3;
		}
		else if ( m_TypeFormat_B2->GetSelection() == 1 )
		{
			a = 16;
			b = 9;
		}
		else if ( m_TypeFormat_B2->GetSelection() == 2 )
		{
			a = 16;
			b = 10;
		}

		const StringVector& Config = Core::GetRenderSystem()->GetAvailableDisplayMode();
		for ( size_t i = 0; i < Config.size(); ++i )
		{
			String buffer, mode = Config.at( i );
			int Width, Height;

			String::size_type x_pos = mode.find_first_of( "x", 0 );

			buffer = mode.substr( 0, x_pos );
			Width = atoi( buffer.c_str() );

			buffer = mode.substr( x_pos + 1, mode.length() );
			Height = atoi( buffer.c_str() );

			float display = (float) Width / Height;
			float format = (float) a / b;

			if ( display == format )
			{
				m_ModeList_B2->Append( Config.at( i ) );
			}
		}

		m_ModeList_B2->SetSelection( 0 );
		m_TypeFormat_B2->SetSelection( 0 );
	}
}