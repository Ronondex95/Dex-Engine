#pragma once

#include <DexPreCompletion.h>

namespace Dex
{
	class D_EXPORT StringConverter
	{
	public:
		static void trim( String& string, bool left = true, bool right = true );

		// toString
		static String toString( const char* value );
		static String toString_on_off( bool value );
		static String toString_true_false( bool value );
		static String toString_1_0( bool value );
		static String toString( int value );
		static String toString( unsigned long value );
		static String toString( size_t value );

		// Parse
		static bool Parse_bool( String value, bool default_value = false );
		static int Parse_int( String value, int default_value = 0 );
		static unsigned int Parse_unsigned_int( String value, unsigned int default_value = 0 );
		static size_t Parse_size_t( String value, size_t default_value = 0 );

		static void TakeDownDisplyaMode( const String& mode, int& Width, int& Height, int& bit );
	};
}