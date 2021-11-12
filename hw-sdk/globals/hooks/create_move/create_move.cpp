#include <string.h>

#include "create_move.h"

bool __fastcall hooks::create_move::create_move_detour( sdk::c_base_entity* edx, void*, float input_sample_frametime, sdk::c_user_cmd* active )
{
	hooks::create_move_hook.call_original< bool >( edx, input_sample_frametime, active );

	return false;
}
