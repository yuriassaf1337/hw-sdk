#pragma once

#include <d3dx9.h>
#include <iostream>

#include "../hooking.h"
#include "../../../utils/vfunc/vfunc.h"
#include "../../intefaces/interfaces.h"
#include "../../../utils/keybinds/keybinds.h"

namespace wndproc_hook
{
	inline WNDPROC original;

	LONG WINAPI wndproc_detour( HWND window, UINT message, WPARAM parameter, LPARAM long_parameter );

	void init( );
	void unload( );
} // namespace present_hook
