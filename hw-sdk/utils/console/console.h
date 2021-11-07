#pragma once

// deps
#include "log_level/log_level.h"

#include <Windows.h>
#include <consoleapi.h>
#include <consoleapi2.h>
#include <consoleapi3.h>
#include <stdio.h>
#include <utility>
#include <windef.h>
#include <xstring>

namespace console
{
	bool init( );

	void unload( );

	template< console::log_level lev >
	void print( std::string_view print, std::string_view prefix = ">> " );

	template< typename... VA >
	inline std::string format( std::string_view fmt, VA&&... args );

	template< console::log_level level, typename... VA >
	void format_log( std::string_view str, VA&&... args );
} // namespace console

#include "console.inl"
