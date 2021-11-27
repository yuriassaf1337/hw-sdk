#include "prediction.h"

#include "../../globals/hooks/cl_move/cl_move.h"
#include "../../globals/intefaces/interfaces.h"

void prediction::impl::pre_think( sdk::c_base_player* player )
{
	static auto pre_think_signature = g_client_dll.pattern_scan( _( "55 8B EC 83 E4 ? 51 56 8B F1 8B 06" ) ).as< std::uintptr_t >( );

	using pre_think_type = void( __thiscall* )( sdk::c_base_player* );

	reinterpret_cast< pre_think_type >( pre_think_signature )( player );
}

void prediction::impl::post_think( sdk::c_base_player* player )
{
	static auto post_think_signature =
		g_client_dll.pattern_scan( _( "56 8B 35 ? ? ? ? 57 8B F9 8B CE 8B 06 FF 90 ? ? ? ? 8B 07" ) ).as< std::uintptr_t >( );

	using post_think_type = void( __thiscall* )( sdk::c_base_player* );

	reinterpret_cast< post_think_type >( post_think_signature )( player );
}

void prediction::impl::update( ) { }

void prediction::impl::start( sdk::c_base_player* player, sdk::c_user_cmd* command )
{
	player->current_command( ) = command;
	player->set_prediction_random_seed( command );
	player->set_prediction_player( player );

	backup_vars.tick_base    = get_tick_base( player, command );
	backup_vars.current_time = g_interfaces.globals->current_time;
	backup_vars.frame_time   = g_interfaces.globals->frame_time;

	g_interfaces.globals->current_time = player->tick_base( ) * g_interfaces.globals->interval_per_tick;
	g_interfaces.globals->frame_time   = g_interfaces.prediction->engine_paused ? 0 : g_interfaces.globals->interval_per_tick;

	g_interfaces.game_movement->start_track_prediction_errors( player );

	g_interfaces.prediction->set_local_view_angles( command->view_angles );

	pre_think( player );

	g_interfaces.move_helper->set_host( player );

	g_interfaces.prediction->setup_move( player, command, g_interfaces.move_helper, &backup_vars.move_data );

	g_interfaces.game_movement->process_movement( player, &backup_vars.move_data );

	g_interfaces.prediction->finish_move( player, command, &backup_vars.move_data );

	g_interfaces.move_helper->process_impacts( );

	post_think( player );

	player->tick_base( ) = backup_vars.tick_base;

	if ( hooks::adjust != 0 ) {
		if ( hooks::adjust < 0 ) {
			player->tick_base( )--;
			hooks::adjust++;
		} else {
			player->tick_base( )++;
			hooks::adjust--;
		}
	}
}

void prediction::impl::end( sdk::c_base_player* player, sdk::c_user_cmd* command )
{
	g_interfaces.game_movement->finish_track_prediction_errors( player );

	g_interfaces.move_helper->set_host( nullptr );

	g_interfaces.globals->current_time = backup_vars.current_time;
	g_interfaces.globals->frame_time   = backup_vars.frame_time;

	player->current_command( ) = nullptr;
	player->set_prediction_random_seed( nullptr );
	player->set_prediction_player( nullptr );

	g_interfaces.game_movement->reset( );
}

void prediction::impl::reset( )
{
	g_interfaces.prediction->restore_entity_to_predicted_frame( g_interfaces.prediction->predicted_commands( ) - 1 );
	g_interfaces.prediction->previous_start_frame( ) = -1;
	g_interfaces.prediction->predicted_commands( )   = 0;
}

int prediction::impl::get_tick_base( sdk::c_base_player* player, sdk::c_user_cmd* command )
{
	static int tick = 0;

	if ( command ) {
		static sdk::c_user_cmd* last_command{ };

		if ( !last_command || last_command->has_been_predicted )
			tick = player->tick_base( );
		else
			tick++;

		last_command = command;
	}

	return tick;
}
