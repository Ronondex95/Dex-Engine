#include <DexDynamicLibrary.h>
#include <DexCore.h>

namespace Dex
{
	DynamicLibrary::DynamicLibrary( const String& filename )
	{
		m_Work = true;
		m_FileName = filename;

		if ( filename.substr( filename.length() - 4, 4 ) != ".dll" )
		{
			m_FileName += ".dll";
		}

		m_hDll = LoadLibraryEx( m_FileName.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH );

		if ( !m_hDll )
		{
			LPVOID ErrorBuffer; 
			FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
				NULL, GetLastError(), MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), (LPTSTR) &ErrorBuffer, 0, NULL );

			String error = (char*)ErrorBuffer;
			LocalFree( ErrorBuffer );

			Core::GetLog()->DrawLine("DynamicLibrary: " + error, MT_ERROR );
			m_Work = false;
		}
	}

	DynamicLibrary::~DynamicLibrary( void )
	{
		if ( !FreeLibrary( m_hDll ) )
		{
			Core::GetLog()->DrawLine("DynamicLibrary: Невозможно выгрузить модуль", MT_ERROR );
		}
	}

	void* DynamicLibrary::GetAddress( const String& funcname )
	{
		return GetProcAddress( m_hDll, funcname.c_str() );
	}
}