#include <string.h>

#include "../../../hacks/prediction/prediction.h"
#include "../../../utils/convars/convars.h"
#include "../../../utils/entity_list/entity_list.h"
#include "../../../utils/keybinds/keybinds.h"
#include "create_move.h"

void __stdcall create_move_function( int sequence_number, float input_sample_frametime, bool active, bool& send_packet )
{
	hooks::create_move_hook.call_original< void >( g_interfaces.client, nullptr, sequence_number, input_sample_frametime, active );

	auto command  = g_interfaces.input->get_user_cmd( 0, sequence_number );
	auto verified = g_interfaces.input->get_verified_cmd( sequence_number );

	entity_list::update( );

	if ( !entity_list::local_player || !command || !verified )
		return;

	g_prediction.update( );
	g_prediction.start( entity_list::local_player, command );
	{
	}
	g_prediction.end( entity_list::local_player, command );

	if ( g_input.key_state< input::key_state_t::KEY_DOWN >( VK_END ) )
		send_packet = false;

	g_convars[ _( "sv_autobunnyhopping" ) ]->set_value( true );

	verified->command  = *command;
	verified->checksum = command->checksum( );
}

__declspec( naked ) void __fastcall hooks::create_move::create_move_detour( sdk::i_client_dll* _this, void* edx, int sequence_number,
                                                                            float input_sample_frametime, bool active )
{
	__asm
	{
		push ebp
		mov  ebp, esp
		push ebx
		push esp
		push dword ptr[active]
		push dword ptr[input_sample_frametime]
		push dword ptr[sequence_number]
		call create_move_function
		pop  ebx
		pop  ebp
		retn 0Ch
	}
}
