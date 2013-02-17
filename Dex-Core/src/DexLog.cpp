#include <DexLog.h>

namespace Dex
{
	Log::Log( const String& logname )
	{
		m_Log.open( logname.c_str() );

		m_Log << "<html>" << std::endl;
		m_Log << "<head>" << std::endl;
		m_Log << "<title>Work log</title>" << std::endl;
		m_Log << "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">" << std::endl;
		m_Log << "</head>" << std::endl;
		m_Log << "<body>" << std::endl;
		m_Log << "<div class=\"header\"><b>Dex Engine - Work log</b></div>" << std::endl;
	}

	Log::~Log( void )
	{
		m_Log << "</body>" << std::endl;
		m_Log << "</html>" << std::endl;

		m_Log.close();
	}

	void Log::DrawLine( const String& Text, const MessageTypes Log_type )
	{
		if ( m_Log )
		{
			String Warning;

			if ( Log_type == MT_NORMAL )
			{
				Warning = "normal";
			}
			else if ( Log_type == MT_WARNING )
			{
				Warning = "warning";
			}
			else if ( Log_type == MT_ERROR )
			{
				Warning = "error";
			}

			m_Log << "<div class=" + Warning + ">" + Text + "</div>" << std::endl;

			m_Log.flush();
		}
	}
}