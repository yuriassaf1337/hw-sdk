#pragma once
#include "../hooking.h"
#include <iostream>

#include "../../../game/sdk/classes/c_base_entity.h"
#include "../../../game/sdk/classes/c_usercmd.h"
#include "../../../utils/vfunc/vfunc.h"
#include "../../interfaces/interfaces.h"
#include "../hooking.h"
namespace hooks
{
	CREATE_HOOK_HELPER( frame_stage_notify_hook, bool( __fastcall* )( void*, int ) );

	struct frame_stage_notify {
		static bool __stdcall frame_stage_notify_detour( int stage );

		static void init( )
		{
			hooks::frame_stage_notify_hook.create( virtual_func::get( g_interfaces.client, 37 ), frame_stage_notify_detour,
			                                       _( "frame_stage_notify_detour" ) );
		}

		static void unload( )
		{
			hooks::frame_stage_notify_hook.disable( );
		}
	};
} // namespace hooks
