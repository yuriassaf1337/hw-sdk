#pragma once

#include <d3dx9.h>
#include <iostream>

#include "../../../utils/vfunc/vfunc.h"
#include "../../intefaces/interfaces.h"
#include "../hooking.h"

namespace hooks
{
	CREATE_HOOK_HELPER( present_hook, HRESULT( __stdcall )( IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA* ) );
	struct present {
		static HRESULT __stdcall present_detour( IDirect3DDevice9* device, const RECT* source, const RECT* dest, HWND dest_window,
		                                         const RGNDATA* dirty );

		static void init( )
		{
			present_hook.create( virtual_func::get( g_interfaces.device, 17 ), present_detour, _( "present_detour" ) );
		}
		static void unload( )
		{
			present_hook.disable( );
		}
	};
} // namespace hooks
