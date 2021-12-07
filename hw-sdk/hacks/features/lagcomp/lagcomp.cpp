#include "lagcomp.h"
#include "../../../utils/convars/convars.h"
#include "../../../utils/entity_list/entity_list.h"

void lagcomp::impl::update( )
{
	static auto sv_maxunlag = g_convars[ _( "sv_maxunlag" ) ];
	auto sv_maxunlag_ticks  = static_cast< int >( sv_maxunlag->get_float( ) / g_interfaces.globals->interval_per_tick );

	for ( auto& player : g_entity_list.players ) {
		if ( !player->entity_index( ) )
			continue;

		auto& current_heap_record   = heap_records[ player->entity_index( ) ];
		auto& current_heap_iterator = heap_iterator[ player->entity_index( ) ];

		if ( !current_heap_iterator )
			current_heap_record = reinterpret_cast< record* >( malloc( sv_maxunlag_ticks * sizeof record ) );

		auto current_record = current_heap_record[ current_heap_iterator * sizeof record ];

		current_record.valid = false;

		current_heap_iterator++;

		if ( current_heap_iterator >= sv_maxunlag_ticks )
			current_heap_iterator = 0;
	}
}
