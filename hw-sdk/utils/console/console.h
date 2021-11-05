#pragma once

// deps
#include "../../dependencies/tinyformat.h"
#include "../../globals/macros/macros.h"

#include "log_level/log_level.h"

#include <Windows.h>
#include <consoleapi.h>
#include <consoleapi2.h>
#include <consoleapi3.h>
#include <stdio.h>
#include <windef.h>

namespace console
{
	bool init( );

	void unload( );

	template< console::log_level lev >
	void print( std::string_view print, std::string_view prefix = _( ">> " ) )
	{
#ifdef CONSOLE_ENABLED

		const char* type{ };
		switch ( lev ) {
		case console::log_level::NORMAL:
			type = _( " " );
			break;
		case console::log_level::WARNING:
			type = _( " # warning -> " );
			break;
		case console::log_level::FATAL:
			type = _( " # fatal -> " );
			break;
		}
		// have to do this otherwise we get a dangling pointer -> (ss.str().c_str())
		std::stringstream ss{ };
		ss << prefix << type << print;
		const std::string temp_str = std::string{ ss.str( ) };

		tfm::printf( temp_str.c_str( ) );
#endif
	}
} // namespace console
