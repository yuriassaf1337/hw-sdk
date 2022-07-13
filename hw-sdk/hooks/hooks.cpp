#include "hooks.h"

bool hooks::impl::init( )
{
	MOCKING_TRY;

	if ( const auto status = MH_Initialize( ); status != MH_OK ) {
		console::print< console::log_level::FATAL >( _( "hooks::impl::init( ) failed to initialize [ status: {} ]" ), MH_StatusToString( status ) );
		return false;
	}

	HOOK( hooks::create_move.create( virtual_func::get( g_interfaces.client, 24 ), hooks::detours::create_move ) );

	MOCKING_CATCH( return false );

	console::print< console::log_level::SUCCESS >( _( "Initialized all hooks." ) );
	return true;
}

void hooks::impl::unload( )
{
	MOCKING_TRY;

	MH_DisableHook( MH_ALL_HOOKS );
	MH_RemoveHook( MH_ALL_HOOKS );

	MH_Uninitialize( );

	g_imgui.destroy( );

	MOCKING_CATCH( );
}

bool __fastcall hooks::detours::create_move( sdk::c_cs_player* ecx, void*, float input_sample_time, sdk::c_user_cmd* cmd )
{
	static auto og = *hooks::create_move.get_original< hooks::create_move_fn >( );

	if ( !cmd || !cmd->command_number )
		return og( ecx, input_sample_time, cmd );

	g_ctx.cmd = cmd;

	if ( og( ecx, input_sample_time, cmd ) )
		ecx->set_local_view_angles( cmd->view_angles );

	if ( !g_ctx.local )
		return false;

	g_movement.pre_prediction.think( );

	g_prediction.update( );
	g_prediction.store_backup( );

	g_prediction.start( g_ctx.local );
	g_prediction.end( g_ctx.local );

	g_aimbot.run( );
	g_movement.movement_fix( cmd, g_prediction.backup_vars.view_angles );

	g_movement.post_prediction.think( );

	return false;
}
