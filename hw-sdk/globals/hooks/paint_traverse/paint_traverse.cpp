#include "paint_traverse.h"
#include "../../../hacks/features/visuals/visuals.h"
#include "../../../hacks/logging/logging.h"
#include "../../ctx/ctx.h"

void __fastcall hooks::paint_traverse::paint_traverse_detour( sdk::i_panel* self, void* edx, unsigned int panel, bool force_repaint,
                                                              bool allow_force )
{
	const auto panel_hash = HASH( g_interfaces.panel->panel_name( panel ) );

	if ( static bool already_logged = false; !already_logged ) {
		//	g_interfaces.engine->execute_client_cmd( _( "clear" ) );
		g_log.print( _( " injection success." ), _( "[hotwheels.vip]" ) );

		already_logged = true;
	}

	g_ctx.view_matrix = g_interfaces.engine->world_to_screen_matrix( );

	for ( auto& player : g_entity_list.players ) {
		visuals::esp_object& object = g_visuals.esp_objects[ player->entity_index( ) ];

		if ( !object.m_owner )
			continue;

		auto collideable = object.m_owner->get_collideable( );

		if ( !collideable )
			continue;

		object.m_box.m_mins = collideable->obb_mins( );
		object.m_box.m_maxs = collideable->obb_maxs( );

		object.m_box.m_rgfl = object.m_owner->rgfl_coordinate_frame( );
	}

	hooks::paint_traverse_hook.call_original< void >( self, edx, panel, force_repaint, allow_force );
}
