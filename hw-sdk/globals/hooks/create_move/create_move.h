#pragma once

#include <d3dx9.h>
#include <iostream>

#include "../../../utils/vfunc/vfunc.h"
#include "../../intefaces/interfaces.h"
#include "../hooking.h"

namespace create_move
{
	void __fastcall create_move_detour( void* edx, void* ecx, int sequence_number, float input_sample_frametime, bool active );

	void init( );
	void unload( );

	inline hook_helper< void( __fastcall )( void*, void*, int, float, bool ) > helper;
} // namespace create_move
