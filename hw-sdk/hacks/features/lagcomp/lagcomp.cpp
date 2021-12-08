#include "lagcomp.h"

#include "../../../game/sdk/enums/flow.h"

#include "../../../utils/convars/convars.h"
#include "../../../utils/entity_list/entity_list.h"

bool lagcomp::impl::is_valid( record heap_record )
{
	float correct = 0.f;

	static auto sv_maxunlag = g_convars[ _( "sv_maxunlag" ) ]->get_float( );

	correct += g_interfaces.engine->get_net_channel_info( )->get_latency( sdk::flow::FLOW_OUTGOING );
	correct += lerp_time( );

	correct = std::clamp( correct, 0.f, sv_maxunlag );

	float delta_correct = fabs( correct - ( g_interfaces.globals->current_time - heap_record.simulation_time ) );

	if ( delta_correct > .2f )
		return false;

	return true;
}

float lagcomp::impl::lerp_time( )
{
	static auto update_rate  = g_convars[ _( "sv_maxupdaterate" ) ]->get_int( );
	static auto interp_ratio = std::clamp( g_convars[ _( "cl_interp_ratio" ) ]->get_float( ), 1.f, FLT_MAX );

	static auto interp = g_convars[ _( "cl_interp" ) ]->get_float( );

	static auto min_interp_ratio = g_convars[ _( "sv_client_min_interp_ratio" ) ]->get_float( );
	static auto max_interp_ratio = g_convars[ _( "sv_client_max_interp_ratio" ) ]->get_float( );

	interp_ratio = std::clamp( interp_ratio, min_interp_ratio, max_interp_ratio );

	return std::max( interp, interp_ratio / update_rate );
}

void lagcomp::impl::update( )
{
	static auto sv_maxunlag = g_convars[ _( "sv_maxunlag" ) ]->get_float( );
	auto sv_maxunlag_ticks  = static_cast< int >( sv_maxunlag / g_interfaces.globals->interval_per_tick );

	for ( auto& player : g_entity_list.players ) {
		if ( player->gun_game_immunity( ) )
			continue;

		auto& current_heap_iterator = heap_iterator[ player->entity_index( ) ];

		if ( !heap_records[ player->entity_index( ) ] )
			heap_records[ player->entity_index( ) ] = new record[ sv_maxunlag_ticks ];

		auto& current_record = heap_records[ player->entity_index( ) ][ current_heap_iterator ];

		current_record.origin          = player->get_abs_angles( );
		current_record.simulation_time = player->simulation_time( );
		current_record.valid           = is_valid( current_record );

		current_heap_iterator++;

		if ( current_heap_iterator >= sv_maxunlag_ticks )
			current_heap_iterator = 0;
	}
}

void lagcomp::impl::backtrack_player( record heap_record ) { }
