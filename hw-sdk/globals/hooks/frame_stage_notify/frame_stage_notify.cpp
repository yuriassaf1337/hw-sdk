#include "frame_stage_notify.h"

void __fastcall hooks::frame_stage_notify::frame_stage_notify_detour( void* self, void* ecx, sdk::frame_stage stage )
{
	hooks::frame_stage_notify_hook.call_original< void >( self, ecx, stage );

	switch ( stage ) {
		using enum sdk::frame_stage;
	case NET_UPDATE_END:
		g_entity_list.update( );
		g_lagcomp.update( );
		g_visuals.update( );
		break;
	}
}
