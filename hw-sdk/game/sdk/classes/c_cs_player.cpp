#include "c_cs_player.h"

const bool sdk::c_cs_player::is_enemy( sdk::c_cs_player* player )
{
	static auto mp_teammates_are_enemies = g_convars[ _( "mp_teammates_are_enemies" ) ];

	if ( mp_teammates_are_enemies->get_bool( ) )
		return true;

	if ( this->team_number( ) == player->team_number( ) )
		return false;

	return true;
}

bool sdk::c_cs_player::is_alive( )
{
	return ( this->life_state( ) == sdk::life_state::LIFE_ALIVE && this->health( ) > 0 );
}

const std::string& sdk::c_cs_player::name( )
{
	if ( sdk::player_info_t info{ }; g_interfaces.engine->get_player_info( this->entity_index( ), &info ) )
		return std::string( info.name ).substr( 0, 24 );
	return { };
}
