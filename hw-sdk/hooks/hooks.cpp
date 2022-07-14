#include "hooks.h"
#include "../dependencies/imgui/imgui_impl_win32.h"

bool hooks::impl::init( )
{
	MOCKING_TRY;

	if ( const auto status = MH_Initialize( ); status != MH_OK ) {
		console::print< console::log_level::FATAL >( _( "hooks::impl::init( ) failed to initialize [ status: {} ]" ), MH_StatusToString( status ) );
		return false;
	}

	if ( hooks::wnd_proc = reinterpret_cast< WNDPROC >( LI_FN( SetWindowLongA )( FindWindowA( _( "Valve001" ), nullptr ), GWL_WNDPROC,
	                                                                             reinterpret_cast< LONG_PTR >( hooks::detours::wnd_proc ) ) );
	     !hooks::wnd_proc ) {
		console::print< console::log_level::SUCCESS >( _( "Failed find game window" ) );
		return false;
	}

	MOCK hooks::ret_add::init( );

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

	LI_FN( SetWindowLongA )( hotwheels::window, GWL_WNDPROC, reinterpret_cast< LONG_PTR >( hooks::wnd_proc ) );

	g_imgui.destroy( );

	MOCKING_CATCH( );
}

bool __fastcall hooks::detours::create_move( sdk::c_cs_player* ecx, void*, float input_sample_time, sdk::c_user_cmd* cmd )
{
	static auto og = hooks::create_move.get_original< hooks::create_move_fn >( );

	if ( !cmd || !cmd->command_number )
		return og( ecx, input_sample_time, cmd );

	g_ctx.cmd = cmd;

	auto net_channel = g_interfaces.client_state->net_channel;

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

	if ( net_channel ) {
		if ( !hooks::send_net_msg.is_hooked( ) )
			hooks::send_net_msg.create( virtual_func::get( net_channel, 40 ), &hooks::detours::send_net_msg );
	}

	return false;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler( HWND window, UINT message, WPARAM wideParam, LPARAM longParam );
HRESULT WINAPI hooks::detours::wnd_proc( HWND window, UINT message, WPARAM parameter, LPARAM long_parameter )
{
	g_input.think( message, parameter, long_parameter );

	if ( g_input.key_state( input::key_state_t::KEY_RELEASED, VK_INSERT ) )
		g_menu.menu_open = !g_menu.menu_open;

	static auto lazy_callwndproc = LI_FN( CallWindowProcA ).get( );

	if ( g_menu.menu_initialised && g_menu.menu_open && ImGui_ImplWin32_WndProcHandler( window, message, parameter, long_parameter ) )
		return 1L;

	return lazy_callwndproc( hooks::wnd_proc, window, message, parameter, long_parameter );
}

bool __stdcall hooks::detours::ret_add( LPCSTR )
{
	return true;
}

bool __fastcall hooks::detours::send_net_msg( void* ecx, void* edx, sdk::i_net_msg* net_message, bool reliable, bool voice )
{
	static auto og = hooks::send_net_msg.get_original< decltype( &hooks::detours::send_net_msg ) >( );

	// CRC check bypass
	if ( net_message->get_type( ) == 14 )
		return false;

	// fix for fakelag voice lag
	if ( net_message->get_group( ) == sdk::net_channel_type::VOICE )
		voice = true;

	return og( ecx, edx, net_message, reliable, voice );
}
