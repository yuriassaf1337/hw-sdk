#include <string.h>

#include "present.h"

HRESULT __stdcall present_hook::present_detour( IDirect3DDevice9* device, const RECT* source, const RECT* dest, HWND dest_window,
                                                const RGNDATA* dirty )
{
	return helper.call_original< HRESULT >( device, source, dest, dest_window, dirty );
}

void present_hook::init( )
{
	helper.create( virtual_func::get( interfaces::device, 17 ), present_detour, _( "present_detour" ) );
}

void present_hook::unload( )
{
	helper.disable( );
}
