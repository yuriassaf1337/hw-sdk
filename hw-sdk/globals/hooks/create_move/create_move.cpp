#include <string.h>

#include "create_move.h"

void __fastcall create_move::create_move_detour( void* edx, void* ecx, int sequence_number, float input_sample_frametime, bool active )
{
	helper.call_original<void>(edx, ecx, sequence_number, input_sample_frametime, active);
}

void create_move::init( )
{
	helper.create( virtual_func::get( interfaces::device, 17 ), create_move_detour, _( "create_move" ) );
}

void create_move::unload( )
{
	helper.disable( );
}
