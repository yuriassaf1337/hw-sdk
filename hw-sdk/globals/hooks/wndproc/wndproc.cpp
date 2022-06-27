#include "wndproc.h"
#include "../../../dependencies/imgui/imgui.h"
#include "../../../hacks/menu/menu.h"
#include "../../../utils/modules/modules.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler( HWND window, UINT message, WPARAM wideParam, LPARAM longParam );
HRESULT WINAPI hooks::wndproc::wndproc_detour( HWND window, UINT message, WPARAM parameter, LPARAM long_parameter )
{
	g_input.think( message, parameter, long_parameter );

	g_input.add_keybind( VK_INSERT, [ & ]( bool pressed ) {
		if ( pressed )
			g_menu.menu_open = !g_menu.menu_open;
	} );

	static auto lazy_callwndproc = LI_FN( CallWindowProcA ).get( );

	if ( g_menu.menu_initialised && g_menu.menu_open && ImGui_ImplWin32_WndProcHandler( window, message, parameter, long_parameter ) )
		return 1L;

	return lazy_callwndproc( hooks::wndproc_hook, window, message, parameter, long_parameter );
}
