#include <string.h>

#include "create_move.h"

void __fastcall create_move::create_move_detour( void* edx, void* ecx, int sequence_number, float input_sample_frametime, bool active )
{
	helper.call_original< void >( edx, ecx, sequence_number, input_sample_frametime, active );

	math::vec3 view_angles{ 12, 12, 12 };

	interfaces::engine->set_view_angles( view_angles );
}

void create_move::init( )
{
	helper.create( virtual_func::get( interfaces::client, 22 ), create_move_detour, _( "create_move" ) );
}

void create_move::unload( )
{
	helper.disable( );
}
