#include <string.h>

#include "../../../globals/ctx/ctx.h"
#include "../../../utils/entity_list/entity_list.h"
#include "../../../utils/keybinds/keybinds.h"
#include "cl_move.h"

static int charged = 0;

void __cdecl hooks::cl_move::cl_move_detour( float accumulated_extra_samples, bool final_tick )
{
	auto can_charge = []( ) -> bool {
		bool sure = false;

		if ( g_ctx.local )
			sure = true;

		return sure;
	};

	auto charge = []( ) -> void {
		adjust--;
		charged++;
	};

	auto release = [ accumulated_extra_samples, final_tick ]( ) -> void {
		for ( int i = 0; i < charged; i++ ) {
			adjust++;
			hooks::cl_move_hook.call_original< void >( accumulated_extra_samples, final_tick );
		}

		charged = 0;
	};

	if ( charged < 16 && can_charge( ) ) {
		charge( );
		return;
	}

	hooks::cl_move_hook.call_original< void >( accumulated_extra_samples, final_tick );

	if ( g_input.key_state< input::KEY_DOWN >( VK_HOME ) && charged == 16 )
		release( );
}
