#include <string.h>

#include "create_move.h"

bool __fastcall hooks::create_move::create_move_detour( sdk::i_client_dll* _this, void* edx, int sequence_number, float input_sample_frametime, bool active )
{
	hooks::create_move_hook.call_original< bool >( _this, edx, input_sample_frametime, active );

	return false;
}
