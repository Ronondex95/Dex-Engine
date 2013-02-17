#pragma once

#include <DexPreCompletion.h>

namespace Dex
{
	class D_EXPORT IRenderWindow
	{
	public:
		bool IsFullScrean( void );
		bool IsActive( void );
		const String& GetName( void );

	protected:
		String				m_Name;

		bool				m_FullScrean;
		bool				m_VSync;
		bool				m_Active;

		// Display Mode
		int					m_nWidth;
		int					m_nHeight;
		int					m_nBit;
	};
}