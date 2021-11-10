#pragma once
#include "../../../globals/hotwheels/hotwheels.h"
#include <string_view>

namespace function_enforce
{
	template< bool uninject, typename... args >
	inline bool enforcer( bool what, std::string_view id, std::string_view msg, args&&... arg )
	{
		if ( !what ) {
			console::print< console::log_level::FATAL >( _( "Enforce failed - [ id = {} -> msg = {} ]" ), id, msg );

#ifdef _DEBUG
			MessageBox( hotwheels::window, console::format( _( "Enforce failed - [ id = {} -> msg = {} ]" ), id, msg ).c_str( ),
			            _( "exit failure - function enforcer" ), MB_OK );
#endif

			if constexpr ( abort )
				hotwheels::unload( EXIT_FAILURE );
		}

		return what;
	}
}; // namespace function_enforce

// sends warning only if explicit function fails, aka if something doesnt initialize proper, it will unload
#define ENFORCE_WARNING( exp, msg, ... ) function_enforce::enforcer< false >( exp, _( #exp ), _( msg ), __VA_ARGS__ )
#define ENFORCE_FAILURE( exp, msg, ... ) function_enforce::enforcer< true >( exp, _( #exp ), _( msg ), __VA_ARGS__ )
