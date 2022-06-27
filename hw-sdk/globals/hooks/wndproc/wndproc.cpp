#include "wndproc.h"
#include "../../../hacks/menu/menu.h"
#include "../../../utils/modules/modules.h"

HRESULT WINAPI hooks::wndproc::wndproc_detour( HWND window, UINT message, WPARAM parameter, LPARAM long_parameter )
{
	g_input.think( message, parameter, long_parameter );

		g_input.add_keybind( VK_INSERT, [ & ]( bool pressed ) {
		if ( pressed )
			g_menu.menu_open = !g_menu.menu_open;
	} );


	static auto lazy_callwndproc = LI_FN( CallWindowProcA ).get( );

	return lazy_callwndproc( hooks::wndproc_hook, window, message, parameter, long_parameter );
}
