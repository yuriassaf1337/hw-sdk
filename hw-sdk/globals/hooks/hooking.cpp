#include "hooking.h"

#include "../../dependencies/mocking_bird/mocking_bird.h"
#include "../ctx/ctx.h"
#include "cl_move/cl_move.h"
#include "create_move/create_move.h"
#include "emit_sound/emit_sound.h"
#include "end_scene/end_scene.h"
#include "item_post_frame/item_post_frame.h"
#include "wndproc/wndproc.h"

bool hooks::init( )
{
	MOCKING_TRY;

	if ( MH_Initialize( ) != MH_OK )
		return false;

	// alloc backup mem
	if ( !g_ctx.backup.cmd )
		g_ctx.backup.cmd = reinterpret_cast< sdk::c_user_cmd* >( std::malloc( sizeof( sdk::c_user_cmd ) ) );
	if ( !g_ctx.backup.local )
		g_ctx.backup.local = reinterpret_cast< sdk::c_cs_player* >( std::malloc( 0x3870U ) );

	hooks::wndproc::init( );
	hooks::end_scene::init( );
	hooks::create_move::init( );
	hooks::cl_move::init( );
	hooks::item_post_frame::init( );
	hooks::emit_sound::init( );

	MOCKING_CATCH( return false );

	return true;
}

void hooks::unload( )
{
	hooks::wndproc::unload( );
	hooks::end_scene::unload( );
	hooks::create_move::unload( );
	hooks::cl_move::unload( );
	hooks::item_post_frame::unload( );
	hooks::emit_sound::unload( );

	// this is so useless lol
	if ( MH_Uninitialize( ) != MH_OK )
		console::print< console::log_level::FATAL >( _( "MH_Uninitialize was not MH_OK" ) );
}
