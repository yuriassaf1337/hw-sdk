#pragma once

#include <d3dx9.h>
#include <iostream>

#include "../../../game/sdk/classes/c_base_entity.h"
#include "../../../game/sdk/classes/c_usercmd.h"
#include "../../../utils/vfunc/vfunc.h"
#include "../../intefaces/interfaces.h"
#include "../hooking.h"

namespace hooks
{
	CREATE_HOOK_HELPER( create_move_hook, bool( __fastcall )( void*, float, bool ) );

	struct create_move {
		static bool __fastcall create_move_detour( sdk::c_base_entity* edx, void*, float input_sample_frametime, sdk::c_user_cmd* active );

		static void init( )
		{
			hooks::create_move_hook.create( virtual_func::get( g_interfaces.client, 22 ), create_move_detour, _( "create_move_detour" ) );
		}

		static void unload( )
		{
			hooks::create_move_hook.disable( );
		}
	};
} // namespace hooks
