#pragma once

#include <DexPreCompletion.h>

namespace Dex
{
	class D_EXPORT ConfigFile
	{
	public:
		ConfigFile( const String& filename );
		~ConfigFile( void );

		const ConfigList& GetConfig( void );

	private:
		IFStream		m_Stream;

		StringPair		m_ParameterBuffer;
		ConfigList		m_Config;
	};
}