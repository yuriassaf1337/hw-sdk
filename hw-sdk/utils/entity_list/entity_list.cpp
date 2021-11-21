#include "entity_list.h"

void entity_list::update( )
{
	entities.clear( );

	for ( int i = 0; i < g_interfaces.entity_list->get_highest_entity_index( ); i++ ) {
		auto entity = g_interfaces.entity_list->get_client_entity( i );

		if ( !entity )
			continue;

		auto client_class = entity->get_client_class( );

		if ( client_class->class_id == sdk::enums::class_ids::CS_PLAYER )
			entities.push_back( entity );
	}
}
