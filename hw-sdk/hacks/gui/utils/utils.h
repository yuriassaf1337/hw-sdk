#pragma once
#include "../../../utils/console/console.h"
#include "../gui.h"

// sory for naespace spam

math::vec2< int > last_cursor_position{ };

namespace gui::easing
{
	template< typename T = float >
	constexpr inline T in_cubic( T x )
	{
		return x * x * x;
	}

	template< typename T = float >
	constexpr inline T in_quint( T x )
	{
		T t2 = x * x;
		return x * t2 * t2;
	}

	template< typename T = float >
	constexpr inline T out_quint( T x )
	{
		const T t2 = ( --x ) * x;
		return 1.f + x * t2 * t2;
	}
} // namespace gui::easing

namespace gui::helpers
{
	const std::size_t hash( const std::string_view& name )
	{
		return std::hash< std::string_view >( )( name );
	};

	std::vector< std::string > split_string( std::string str, const std::string& delimiter )
	{
		std::vector< std::string > output;

		size_t pos = 0;
		while ( ( pos = str.find( delimiter ) ) != std::string::npos ) {
			std::string token = str.substr( 0, pos );
			output.push_back( token );
			str.erase( 0, pos + delimiter.length( ) );
		}

		output.push_back( str );

		return output;
	}

	// cursors
	void push_cursor( const math::vec2< int >& to_pos )
	{
		g_gui.cursor_pos_stack.push( to_pos );
	}

	math::vec2< int > pop_cursor( )
	{
		// return empty vector if we dont have cursor pos
		if ( g_gui.cursor_pos_stack.empty( ) ) {
			console::print< console::log_level::WARNING >( _( "{} returned 0 - g_gui.cursor_pos_stack was empty." ), __func__ );
			return { };
		}

		math::vec2< int > top{ g_gui.cursor_pos_stack.top( ) };
		g_gui.cursor_pos_stack.pop( );
		last_cursor_position = top;
		return top;
	}
	math::vec2< int > last_cursor_pos( )
	{
		return last_cursor_position;
	}
} // namespace gui::helpers
