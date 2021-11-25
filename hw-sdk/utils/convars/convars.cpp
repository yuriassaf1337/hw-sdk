#include "convars.h"

sdk::con_var* convars::impl::get_pointer( std::uint32_t hash )
{
	const auto value = convar_map.find( hash );

	if ( !value._Ptr ) {
		console::print< console::log_level::FATAL >( _( "g_convars.get_pointer to hash: {} failed." ), hash );
		return nullptr;
	}

	return value._Ptr->_Myval.second.cvar;
}

void convars::impl::init( )
{
#define EMPLACE_CVAR( str ) convar_map.emplace( HASH( str ), convars::convar_t( HASH( str ), _( str ) ) )

	EMPLACE_CVAR( "sv_autobunnyhopping" );

#undef EMPLACE_CVAR
}
