#pragma once

#include <DexPreCompletion.h>

namespace Dex
{
	enum MessageTypes
	{
		MT_NORMAL,
		MT_WARNING,
		MT_ERROR
	};

	class D_EXPORT Log
	{
	public:
		Log( const String& logname );
		~Log( void );

		void DrawLine( const String& Text, const MessageTypes Log_type = MT_NORMAL );

	private:
		OFStream	m_Log;
	};
}