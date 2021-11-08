#include <string.h>

#include "present.h"

//[note] comented just for now.

HRESULT __stdcall present_hook::present_detour( const RECT* source, const RECT* dest, HWND dest_window, const RGNDATA* dirty )
{
	return 0;
	// return helper.call_original<HRESULT>(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

void present_hook::init( )
{
	// helper.create(virtual_func::get(interfaces::device, 17), present_detour, _("present_detour"));
}

void present_hook::unload( ) { }
