#include "paint_traverse.h"
#include "../../../hacks/logging/logging.h"

void __stdcall hooks::paint_traverse::paint_traverse_detour( unsigned int panel, bool force_repaint, bool allow_force )
{
	const auto panel_hash = HASH( g_interfaces.panel->panel_name( panel ) );

	std::once_flag flag{ };
	std::call_once( flag, []( ) {
		g_interfaces.engine->execute_client_cmd( _( "clear" ) );
		g_log.print( _( "injection success." ), _( "[hotwheels.vip]" ) );
	} );

	return hooks::paint_traverse_hook.call_original< void >( panel, force_repaint, allow_force );
}
