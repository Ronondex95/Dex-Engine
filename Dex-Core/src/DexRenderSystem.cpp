#include <DexRenderSystem.h>

namespace Dex
{
	const String& IRenderSystem::GetName( void )
	{
		return m_Name;
	}

	void IRenderSystem::SetActiveAdapter( UINT adapter )
	{
		m_ActiveAdapter = adapter;
	}
}