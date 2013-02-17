#include <DexCore.h>
#include <DexRenderSystemD3D9.h>

namespace Dex
{
	RenderSystemD3D9* pRenderSystem;

	extern "C"
	{
		void D_EXPORT_D3D9 Start_DexDynamicLibrary( void )
		{
			pRenderSystem = new RenderSystemD3D9();

			Core::GetCore()->AddRenderSystem( pRenderSystem );
		}

		void D_EXPORT_D3D9 Stop_DexDynamicLibrary( void )
		{
			Core::GetCore()->RemoveRenderSystem( pRenderSystem );

			//delete pRenderSystem;
		}
	}
}