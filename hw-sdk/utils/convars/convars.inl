#include "convars.h"

template< class T >
T convars::impl::get_name( std::uint32_t hash )
{
	const auto value = convar_map.find( hash );

	if ( !value._Ptr ) {
		console::print< console::log_level::FATAL >( _( "g_convars.get_pointer to hash: {} failed." ), hash );
		return nullptr;
	}

	return value._Ptr->_Myval.second.cvar_name;
}