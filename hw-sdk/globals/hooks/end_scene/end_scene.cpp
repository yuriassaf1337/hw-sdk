#include <string.h>

#include "../create_move/create_move.h"
#include "end_scene.h"

LONG __stdcall hooks::end_scene::end_scene_detour( IDirect3DDevice9* device )
{
	static auto static_return = _ReturnAddress( );

	if ( static_return != _ReturnAddress( ) )
		return hooks::end_scene_hook.call_original< LONG >( device );

	g_render.setup_state( );

	if ( hooks::can_shoot )
		g_render.render_text( 200, 200, font_alignment::AL_DEFAULT, font_flags::FLAG_DROPSHADOW, _( "SHOOT!" ),
		                      g_fonts[ _( "indicator_verdana_font" ) ], color( 255, 50, 150, 50 ) );

	// g_render.render_vertical_gradient( 20, 20, 100, 100, color( 255, 255, 0, 0 ), color( 255, 255, 255, 0 ), true );
	g_render.render_gradient< gradient_type_t::HORIZONTAL >( 20, 20, 100, 100, color( 0, 255, 0, 255 ), color( 255, 0, 0, 255 ) );

	g_render.finish_state( );

	g_menu.draw( );

	return hooks::end_scene_hook.call_original< LONG >( device );
}
