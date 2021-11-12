#include <string.h>

#include "present.h"

HRESULT __stdcall hooks::present::present_detour( IDirect3DDevice9* device, const RECT* source, const RECT* dest, HWND dest_window,
                                                  const RGNDATA* dirty )
{
	return hooks::present_hook.call_original< HRESULT >( device, source, dest, dest_window, dirty );
}
