#include <DexStringConverter.h>

namespace Dex
{
	void StringConverter::trim( String& string, bool left, bool right )
	{
		const String delims = " \t\r";

        if ( right )
		{
            string.erase( string.find_last_not_of( delims ) + 1 ); // trim right
		}

        if ( left )
		{
            string.erase( 0, string.find_first_not_of( delims ) ); // trim left
		}
	}

	String StringConverter::toString( const char* value )
	{
		StringStream String;
		String << value;
		return String.str();
	}

	String StringConverter::toString_on_off( bool value )
	{
		String result;
		if ( value )
		{
			result = "on";
		}
		else
		{
			result = "off";
		}
		return result;
	}

	String StringConverter::toString_true_false( bool value )
	{
		String result;
		if ( value )
		{
			result = "true";
		}
		else
		{
			result = "false";
		}
		return result;
	}

	String StringConverter::toString_1_0( bool value )
	{
		String result;
		if ( value )
		{
			result = "0";
		}
		else
		{
			result = "1";
		}
		return result;
	}

	String StringConverter::toString( int value )
	{
		StringStream String;
		String << value;
		return String.str();
	}

	String StringConverter::toString( unsigned long value )
	{
		StringStream String;
		String << value;
		return String.str();
	}

	String StringConverter::toString( size_t value )
	{
		StringStream String;
		String << value;
		return String.str();
	}

	bool StringConverter::Parse_bool( String value, bool default_value )
	{
		bool result = default_value;
		if ( value == "on" || value == "true" || value == "1" )
		{
			result = true;
		}
		else if ( value == "off" || value == "false" || value == "0" )
		{
			result = false;
		}

		return result;
	}

	int StringConverter::Parse_int( String value, int default_value )
	{
		StringStream String( value );
		int result = default_value;
        if( !( String >> result ) )
            return default_value;

		return result;
	}

	unsigned int StringConverter::Parse_unsigned_int( String value, unsigned int default_value )
	{
		StringStream String( value );
		unsigned int result = default_value;
        if( !( String >> result ) )
            return default_value;

		return result;
	}

	size_t StringConverter::Parse_size_t( String value, size_t default_value )
	{
		StringStream String( value );
		size_t result = default_value;
        if( !( String >> result ) )
            return default_value;

		return result;
	}

	void StringConverter::TakeDownDisplyaMode( const String& mode, int& Width, int& Height, int& bit )
	{
		String buffer;

		String::size_type x_pos = mode.find_first_of( "x", 0 );
		String::size_type space_pos = mode.find_first_of( "-", 0 );

		buffer = mode.substr( 0, x_pos );
		Width = atoi( buffer.c_str() );

		buffer = mode.substr( x_pos + 1, space_pos );
		Height = atoi( buffer.c_str() );

		buffer = mode.substr( space_pos + 1, mode.length() );
		bit = atoi( buffer.c_str() );
	}
}