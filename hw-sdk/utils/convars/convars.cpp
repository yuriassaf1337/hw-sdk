#include "convars.h"

void convars::impl::init( )
{
	constexpr auto emplace_cvar = []( const char* convar_name ) {
		convar_map.emplace( fnv::hash( convar_name ), convars::convar_t( fnv::hash( convar_name ), _( convar_name ) ) );
	};

	emplace_cvar( "sv_autobunnyhopping 1" );
}
