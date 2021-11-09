#pragma once

#include <d3dx9.h>
#include <iostream>

#include "../../../utils/vfunc/vfunc.h"
#include "../../intefaces/interfaces.h"
#include "../hooking.h"

namespace present_hook
{
	HRESULT __stdcall present_detour( IDirect3DDevice9* device, const RECT* source, const RECT* dest, HWND dest_window, const RGNDATA* dirty );

	void init( );
	void unload( );

	inline hook_helper< HRESULT( __stdcall )( IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA* ) > helper;
} // namespace present_hook
