#include "wndproc.h"

HRESULT WINAPI hooks::wndproc::wndproc_detour( HWND window, UINT message, WPARAM parameter, LPARAM long_parameter )
{
	g_input.think( window, message, parameter, long_parameter );

	static auto lazy_callwndproc = LI_FN( CallWindowProcA ).get( );

	return CallWindowProcA( hooks::wndproc_hook, window, message, parameter, long_parameter );
}
