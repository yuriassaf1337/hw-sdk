#include <string.h>

#include "../../../hacks/features/lagcomp/lagcomp.h"
#include "../../../hacks/logging/logging.h"
#include "../../../utils/convars/convars.h"
#include "../../../utils/entity_list/entity_list.h"
#include "../../ctx/ctx.h"
#include "../create_move/create_move.h"
#include "end_scene.h"

LONG __stdcall hooks::end_scene::end_scene_detour( IDirect3DDevice9* device )
{
	static auto static_return = _ReturnAddress( );

	if ( static_return != _ReturnAddress( ) )
		return hooks::end_scene_hook.call_original< LONG >( device );

	if ( device ) {
		D3DVIEWPORT9 vp;
		device->GetViewport( &vp );

		g_ctx.screen_size.x = vp.Width;
		g_ctx.screen_size.y = vp.Height;
	}

	g_render.setup_state( );

	if ( hooks::can_shoot )
		g_render.render_text( 200, 200, font_alignment::AL_DEFAULT, font_flags::FLAG_DROPSHADOW, _( "SHOOT!" ),
		                      g_fonts[ HASH( "indicator_verdana_font" ) ], color( 255, 50, 150, 50 ) );

	static auto sv_maxunlag = g_convars[ _( "sv_maxunlag" ) ];
	auto sv_maxunlag_ticks  = static_cast< int >( sv_maxunlag->get_float( ) / g_interfaces.globals->interval_per_tick );

	for ( auto& player : g_entity_list.players ) {
		auto heap_record = g_lagcomp.heap_records[ player->entity_index( ) ];

		if ( !heap_record )
			continue;

		for ( auto heap_iterator = 0; heap_iterator < sv_maxunlag_ticks; heap_iterator++ ) {
			auto current_record = heap_record[ heap_iterator ];

			math::vec3 screen_position;

			if ( current_record.valid )
				g_render.render_rectangle< int >( utils::world_to_screen( current_record.origin ), math::vec2( 10, 10 ),
				                                  color( 255, 255, 255, 255 ) );
		}
	}

	g_log.think( );

	g_menu.draw( );

	g_render.finish_state( );

	return hooks::end_scene_hook.call_original< LONG >( device );
}
