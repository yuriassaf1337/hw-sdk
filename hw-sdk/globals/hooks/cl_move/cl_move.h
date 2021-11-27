#pragma once

#include <d3dx9.h>
#include <iostream>

#include "../../../hacks/gui/gui.h"
#include "../../../utils/renderer/renderer.h"
#include "../../../utils/vfunc/vfunc.h"
#include "../../intefaces/interfaces.h"
#include "../hooking.h"

namespace hooks
{
	inline auto adjust = 0;

	CREATE_HOOK_HELPER( cl_move_hook, void( __cdecl )( float, bool ) );
	struct cl_move {
		static void __cdecl cl_move_detour( float accumulated_extra_samples, bool final_tick );

		static void init( )
		{
			cl_move_hook.create( g_engine_dll.pattern_scan( _( "55 8B EC 81 EC ? ? ? ? 53 56 8A F9" ) ).as< void* >( ), cl_move_detour,
			                     _( "cl_move_detour" ) );
		}
		static void unload( )
		{
			cl_move_hook.disable( );
		}
	};
} // namespace hooks
