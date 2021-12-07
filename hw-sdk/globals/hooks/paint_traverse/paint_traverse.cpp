#include "paint_traverse.h"
#include "../../../hacks/logging/logging.h"
#include "../../ctx/ctx.h"

void __fastcall hooks::paint_traverse::paint_traverse_detour( sdk::i_panel* self, void* edx, unsigned int panel, bool force_repaint,
                                                              bool allow_force )
{
	const auto panel_hash = HASH( g_interfaces.panel->panel_name( panel ) );

	// static bool already_logged = false;

	// if ( !already_logged ) {
	//	g_interfaces.engine->execute_client_cmd( _( "clear" ) );
	//	g_log.print( _( " injection success." ), _( "[hotwheels.vip]" ) );

	//	already_logged = true;
	//}

	g_ctx.view_matrix = g_interfaces.engine->world_to_screen_matrix( );

	return hooks::paint_traverse_hook.call_original< void >( self, edx, panel, force_repaint, allow_force );
}
