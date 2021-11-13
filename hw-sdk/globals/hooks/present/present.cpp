#include <string.h>

#include "present.h"

HRESULT __stdcall hooks::present::present_detour( IDirect3DDevice9* device, const RECT* source, const RECT* dest, HWND dest_window,
                                                  const RGNDATA* dirty )
{
	render::render_line( 10, 20, 30, 40, color( 255, 0, 0, 255 ) );
	render::render_rectangle( 10 * 2, 20 * 2, 30 * 2, 40 * 2, color( 0, 255, 0, 255 ) );
	render::render_filled_rectangle( 10 * 8, 20 * 8, 30 * 3, 40 * 3, color( 0, 0, 255, 255 ) );

	return hooks::present_hook.call_original< HRESULT >( device, source, dest, dest_window, dirty );
}
