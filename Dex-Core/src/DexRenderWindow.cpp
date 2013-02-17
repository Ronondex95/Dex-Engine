#include <DexRenderWindow.h>

namespace Dex
{
	bool IRenderWindow::IsFullScrean( void )
	{
		return m_FullScrean;
	}

	bool IRenderWindow::IsActive( void )
	{
		return m_Active;
	}

	const String& IRenderWindow::GetName( void )
	{
		return m_Name;
	}
}