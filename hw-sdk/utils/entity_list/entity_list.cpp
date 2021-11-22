#include "entity_list.h"
#include "../../game/sdk/classes/c_base_entity.h"

void entity_list::update( )
{
	entities.clear( );

	for ( int i = 0; i < g_interfaces.entity_list->get_highest_entity_index( ); i++ ) {
		auto entity = g_interfaces.entity_list->get_client_entity( i );

		if ( !entity )
			continue;

		auto base_entity = entity->as< sdk::c_base_entity* >( );

		if ( !base_entity )
			continue;

		if ( base_entity->is_player( ) ) {
			auto player = reinterpret_cast< sdk::c_cs_player* >( entity );

			if ( !player )
				continue;

			if ( player->is_dormant( ) )
				continue;

			if ( player->health( ) < 1 )
				continue;

			auto active_weapon_handle = player->active_weapon( );

			if ( active_weapon_handle ) {
				auto active_weapon =
					g_interfaces.entity_list->get_client_entity_from_handle( active_weapon_handle )->as< sdk::c_base_combat_weapon* >( );

				if ( active_weapon ) {
					auto mag_ammo = active_weapon->clip_mag( );
					auto aaaaaaaa = 1;
				}
			}

			entities.push_back( entity );
		}
	}
}
