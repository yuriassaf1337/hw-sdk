#include "lagcomp.h"
#include "../../../utils/convars/convars.h"
#include "../../../utils/entity_list/entity_list.h"

bool lagcomp::impl::is_valid( )
{
	return true;
}

void lagcomp::impl::update( )
{
	static auto sv_maxunlag = g_convars[ _( "sv_maxunlag" ) ];
	auto sv_maxunlag_ticks  = static_cast< int >( sv_maxunlag->get_float( ) / g_interfaces.globals->interval_per_tick );

	for ( auto& player : g_entity_list.players ) {
		auto& current_heap_iterator = heap_iterator[ player->entity_index( ) ];

		if ( !heap_records[ player->entity_index( ) ] )
			heap_records[ player->entity_index( ) ] = new record[ sv_maxunlag_ticks ];

		auto& current_record = heap_records[ player->entity_index( ) ][ current_heap_iterator ];

		current_record.origin          = player->get_abs_angles( );
		current_record.simulation_time = player->simulation_time( );
		current_record.valid           = is_valid( );

		current_heap_iterator++;

		if ( current_heap_iterator >= sv_maxunlag_ticks )
			current_heap_iterator = 0;
	}
}
