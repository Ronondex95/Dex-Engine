#include <DexGamePoint.h>

namespace Dex
{
	IMPLEMENT_APP( GameInit )

	bool GameInit::OnInit()
	{
		if ( !wxApp::OnInit() )
			return false;

		GeneralFrame* frame = new GeneralFrame( wxT("The Promised Land") );

		return true;
	}
}