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
	constexpr auto emplace_cvar = []( const char* convar_name ) {
		convar_map.emplace( fnv::hash( convar_name ), convars::convar_t( fnv::hash( convar_name ), _( convar_name ) ) );
	};

	emplace_cvar( "sv_autobunnyhopping" );
}
