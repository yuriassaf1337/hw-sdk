#include <string.h>

#include "../../../dependencies/imgui/imgui.h"
#include "../../../dependencies/imgui/dx9/imgui_impl_dx9.h"
#include "../../../dependencies/imgui/imgui_impl_win32.h"
#include "../../../hacks/features/lagcomp/lagcomp.h"
#include "../../../hacks/features/visuals/visuals.h"
#include "../../../hacks/logging/logging.h"
#include "../../../hacks/menu/menu.h"
#include "../../../utils/convars/convars.h"
#include "../../../utils/entity_list/entity_list.h"
#include "../../ctx/ctx.h"
#include "../create_move/create_move.h"
#include "end_scene.h"

LONG __stdcall hooks::end_scene::end_scene_detour( IDirect3DDevice9* device )
{
	static auto static_return = _ReturnAddress( );

	if ( static_return != _ReturnAddress( ) )
		return hooks::end_scene_hook.call_original< LONG >( device );

	if ( device ) {
		D3DVIEWPORT9 vp;
		device->GetViewport( &vp );

		g_ctx.screen_size.x = vp.Width;
		g_ctx.screen_size.y = vp.Height;
	}

		g_render.setup_state( );

			g_visuals.render( );

				g_log.think( );

	if ( !g_menu.menu_initialised )
		g_menu.init( device );

	ImGui_ImplDX9_NewFrame( );
	ImGui_ImplWin32_NewFrame( );
	ImGui::NewFrame( );

	g_menu.draw( );

	ImGui::EndFrame( );
	ImGui::Render( );
	ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );

	g_render.finish_state( );

	return hooks::end_scene_hook.call_original< LONG >( device );
}
