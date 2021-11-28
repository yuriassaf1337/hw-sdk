#include "entity_list.h"
#include "../../game/sdk/classes/c_base_entity.h"
#include "../../globals/ctx/ctx.h"

void entity_list::impl::update( )
{
	players.clear( );

	g_ctx.local  = nullptr;
	g_ctx.weapon = nullptr;

	auto local_player_entity = g_interfaces.entity_list->get_client_entity( g_interfaces.engine->get_local_player( ) );

	if ( !local_player_entity )
		return;

	g_ctx.local = local_player_entity->as< sdk::c_cs_player* >( );

	if ( auto local_weapon_handle = g_ctx.local->active_weapon( ) ) {
		auto local_weapon_entity = g_interfaces.entity_list->get_client_entity_from_handle( local_weapon_handle );

		if ( local_weapon_entity )
			g_ctx.weapon = local_weapon_entity->as< sdk::c_base_combat_weapon* >( );
	}

	for ( int i = 0; i < g_interfaces.entity_list->get_highest_entity_index( ); i++ ) {
		auto entity = g_interfaces.entity_list->get_client_entity( i )->as< sdk::c_cs_player* >( );

		if ( !entity )
			continue;

		if ( entity->is_player( ) ) {
			if ( entity->is_dormant( ) )
				continue;

			if ( entity->health( ) < 1 )
				continue;

			players.push_back( entity );
		}
	}
}
