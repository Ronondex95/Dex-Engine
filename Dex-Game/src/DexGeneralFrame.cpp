#include <DexGeneralFrame.h>

namespace Dex
{
	enum
	{
		FRAMES = 1000
	};

	BEGIN_EVENT_TABLE( GeneralFrame, wxFrame )
		EVT_UPDATE_UI( FRAMES, GeneralFrame::Update )
		EVT_KEY_UP( GeneralFrame::Keys )
	END_EVENT_TABLE()

	GeneralFrame::GeneralFrame( const wxString& title )
		: wxFrame( NULL, FRAMES, title )
	{
		SetSizeHints( wxDefaultSize, wxDefaultSize );
		Center( wxBOTH );

		m_Event = new Event();

		m_pCore = new Core();
		m_pRender = 0;

		StartUpSetting* start = new StartUpSetting( this );
		start->ShowModal();

		m_pRender = Core::GetRenderSystem();

		CreateSimpleScene();
	}

	GeneralFrame::~GeneralFrame( void )
	{
		delete m_pCore;
	}

	void GeneralFrame::CreateSimpleScene( void )
	{
		m_pScene = m_pCore->CreateScene("Scene-Simple", "General-Window");
		m_RootGroup = m_pScene->GetRootGroup();

		m_pPlayer = m_pScene->CreateCamera("Camera-Player");
		m_pPlayer->MoveTo( Point3( 0.0f, 5.0f, 0.2f ) );

		m_RootGroup->

		m_pMash1 = m_pScene->CreateDMashFromFile("cup.obj", "test");

		m_pLight1 = m_pScene->CreateLight("light_1", Point4( 1.0f, 0.0f, 0.0f, 1.0f ) );
		m_pLight1->MoveTo( Point3( 5.0f, 0.0f, 0.0f ) );

		m_pLight2 = m_pScene->CreateLight("light_2", Point4( 0.0f, 0.0f, 1.0f, 1.0f ) );
		m_pLight2->MoveTo( Point3( -5.0f, 0.0f, 0.0f ) );
	}

	void GeneralFrame::Update( wxUpdateUIEvent& event )
	{
		if ( m_pRender )
		{
			m_pCore->RenderOneFrame();

			static float orbit;
			orbit+=1.0;

			//m_pMash1->MoveZ( 0.03f );
			m_pMash1->RotationX( orbit );
		}
	}

	void GeneralFrame::Keys( wxKeyEvent& event )
	{
		static float orbit;

		if ( event.GetKeyCode() == WXK_ESCAPE )
		{
			Close();
		}
		else if ( event.GetKeyCode() == 87 ) // W
		{
			m_pPlayer->Move( Point3( 0.0f, 0.0f, 1.0f ) );
		}
		else if ( event.GetKeyCode() == 83 ) // S
		{
			m_pPlayer->Move( Point3( 0.0f, 0.0f, -1.0f ) );
		}
		else if ( event.GetKeyCode() == 65 ) // A
		{
			m_pPlayer->Move( Point3( 1.0f, 0.0f, 0.0f ) );
		}
		else if ( event.GetKeyCode() == 68 ) // D
		{
			m_pPlayer->Move( Point3( -1.0f, 0.0f, 0.0f ) );
		}
	}
}