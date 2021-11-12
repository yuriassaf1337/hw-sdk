#include "wndproc.h"

HRESULT __stdcall hooks::wndproc::wndproc_detour( HWND window, UINT message, WPARAM parameter, LPARAM long_parameter )
{
	keybinds::handle_input( message, parameter );

	static auto lazy_callwndproc = LI_FN( CallWindowProcA ).get( );

	return lazy_callwndproc( hooks::wndproc_hook, window, message, parameter, long_parameter );
}
