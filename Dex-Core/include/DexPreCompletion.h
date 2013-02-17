#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

#include <algorithm>

#include <assert.h>

#include <vector>
#include <map>

#include <Windows.h>

#pragma warning ( disable : 4251 )

namespace Dex
{
	// D_EXPORT
	#if defined ( DEXENGINE_EXPORTS )
	#	define D_EXPORT __declspec( dllexport )
	#else
	#	define D_EXPORT __declspec( dllimport )
	#endif

	// String
	typedef std::string String;
	typedef std::stringstream StringStream;
	typedef std::ofstream OFStream;
	typedef std::ifstream IFStream;

	// Container
	template< typename T >
	struct vector
	{
		typedef typename std::vector< T > type;
		typedef typename std::vector< T >::iterator iterator;
	};

	template< typename T1, typename T2 >
	struct map
	{
		typedef typename std::map< T1, T2 > type;
		typedef typename std::map< T1, T2 >::iterator iterator;
	};

	template< typename T1, typename T2 >
	struct pair
	{
		typedef typename std::pair< T1, T2 > type;
	};

	// Common
	typedef map< String, String >::type PairameterList;
	typedef vector< String >::type StringVector;
	typedef struct _ConfigOption
	{
		String Default_Value;
		StringVector Possible_Values;

	} ConfigOption;
	typedef map< String, ConfigOption >::type ConfigOptionList;

	typedef pair< String, String >::type StringPair;
	typedef vector< StringPair >::type ConfigList;

	// Classes
	class Core;
	class IRenderConnect;
	class IVertexBuffer;
	class Object;
	class Scene;
	class Group;
	class Camera;
	class Mash;
	class Log;
	class Light;
	class IRenderSystem;
	class ConfigFile;
	class StringConverter;
	class DynamicLibrary;
	class IRenderWindow;

	typedef vector< Group* >::type	GroupList;
}