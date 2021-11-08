#pragma once

#include <d3dx9.h>
#include <iostream>

#include "../../intefaces/interfaces.h"
#include "../../../utils/vfunc/vfunc.h"
#include "../../../utils/hooking/hooking.h"

namespace present_hook
{
	hook_helper<HRESULT(__stdcall)(const RECT*, const RECT*, HWND, const RGNDATA*)> helper;

	void init();
	void unload();

	HRESULT __stdcall present_detour( const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion );
}
