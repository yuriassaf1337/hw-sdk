#pragma once
#include "../../globals/includes/includes.h"
#include "../../globals/macros/macros.h"

template< console::log_level level, typename... VA >
void console::format_log( std::string_view str, VA&&... args )
{
	auto formatter = ::console::format( str, std::forward< VA >( args )... );
	console::print< level >( formatter );
};

template< typename... VA >
inline std::string console::format( std::string_view fmt, VA&&... args )
{
	return fmt::vformat( fmt, fmt::make_format_args( std::forward< VA >( args )... ) );
};

template< console::log_level lev >
void console::print( std::string_view print, std::string_view prefix )
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