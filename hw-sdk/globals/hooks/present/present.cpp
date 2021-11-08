#include <string.h>

#include "present.h"

HRESULT __stdcall present_hook::present_detour( const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion ) 
{
	return helper.call_original<HRESULT>(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

void present_hook::init( )
{
	helper.create(virtual_func::get(interfaces::device, 17), present_detour, _("present_detour"));
}

void present_hook::unload( ) { }
