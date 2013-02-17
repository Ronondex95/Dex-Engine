#include <DexConfigFile.h>
#include <DexCore.h>
#include <DexStringConverter.h>

namespace Dex
{
	ConfigFile::ConfigFile( const String& filename )
	{
		m_Stream.open( filename.c_str(), std::ios::in );

		if ( m_Stream )
		{
			char cahr_line[256];
			String line, parametor, value;

			while ( m_Stream )
			{
				m_Stream.getline( cahr_line, 256 );
				line = StringConverter::toString( cahr_line );

				// Пропуск пустых и "#" закоментированых строк
				if ( line.length() > 0 && line.at( 0 ) != '#' )
				{
					String::size_type separator_pos = line.find_first_of( "=", 0 );
					if ( separator_pos != String::npos )
					{
						// parametor
						parametor = line.substr( 0, separator_pos );

						// value
						value = line.substr( separator_pos + 1, line.length() );

						// trim
						StringConverter::trim( parametor );
						StringConverter::trim( value );

						m_ParameterBuffer.first = parametor;
						m_ParameterBuffer.second = value;

						m_Config.push_back( m_ParameterBuffer );
					}
				}
			}
		}
		else
		{
			Core::GetLog()->DrawLine( "ConfigFile: Файл \"" + filename + "\" не найден!", MT_ERROR );
		}
	}

	ConfigFile::~ConfigFile( void )
	{
		m_Stream.close();
	}

	const ConfigList& ConfigFile::GetConfig( void )
	{
		return m_Config;
	}
}