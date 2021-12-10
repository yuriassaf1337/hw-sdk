#include "frame_stage_notify.h"

bool __stdcall hooks::frame_stage_notify::frame_stage_notify_detour( int stage )
{
	hooks::frame_stage_notify_hook.call_original< bool >( g_interfaces.client, stage );
}
