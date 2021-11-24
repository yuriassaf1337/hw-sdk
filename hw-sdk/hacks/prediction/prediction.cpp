#include "prediction.h"

#include "../../globals/intefaces/interfaces.h"

void prediction::impl::post_think( ) { }

void prediction::impl::update( ) { }

void prediction::impl::start( sdk::c_base_player* entity, sdk::c_user_cmd* command )
{
	entity->current_command( ) = command;
	entity->set_prediction_random_seed( command );
	entity->set_prediction_player( entity );

	g_interfaces.globals->current_time = entity->tick_base( ) * g_interfaces.globals->interval_per_tick;
	g_interfaces.globals->frame_time   = g_interfaces.prediction->engine_paused ? 0 : g_interfaces.globals->interval_per_tick;

	g_interfaces.game_movement->start_track_prediction_errors( entity );
}

void prediction::impl::end( sdk::c_base_player* entity, sdk::c_user_cmd* command )
{
	g_interfaces.game_movement->finish_track_prediction_errors( entity );

	entity->current_command( ) = nullptr;
	entity->set_prediction_random_seed( nullptr );
	entity->set_prediction_player( nullptr );
}

void prediction::impl::reset( )
{
	g_interfaces.prediction->restore_entity_to_predicted_frame( g_interfaces.prediction->predicted_commands( ) - 1 );
	g_interfaces.prediction->previous_start_frame( ) = -1;
	g_interfaces.prediction->predicted_commands( )   = 0;
}
