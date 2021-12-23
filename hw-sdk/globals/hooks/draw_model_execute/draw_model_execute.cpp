#include "draw_model_execute.h"
#include "../../ctx/ctx.h"
#include <type_traits>

void __fastcall hooks::draw_model_execute::draw_model_execute_detour( void* ecx, void* edx, void* context, void* state, sdk::model_render_info& info,
                                                                      math::matrix_3x4* custom_bone_to_world )
{
	draw_model_execute_hook.call_original< void >( ecx, edx, context, state, info, custom_bone_to_world );
}
