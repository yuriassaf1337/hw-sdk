#include <string.h>

#include "../create_move/create_move.h"
#include "present.h"

HRESULT __stdcall hooks::present::present_detour( IDirect3DDevice9* device, const RECT* source, const RECT* dest, HWND dest_window,
                                                  const RGNDATA* dirty )
{
	if ( hooks::can_shoot )
		g_render.render_text( 200, 200, font_alignment::AL_DEFAULT, font_flags::FLAG_DROPSHADOW, _( "SHOOT!" ),
		                      fonts::find( _( "indicator_verdana_font" ) ), color( 255, 50, 150, 50 ) );

	g_menu.draw( );

	return hooks::present_hook.call_original< HRESULT >( device, source, dest, dest_window, dirty );
}
