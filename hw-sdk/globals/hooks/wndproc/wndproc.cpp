#include "wndproc.h"

HRESULT __stdcall wndproc_hook::wndproc_detour( HWND window, UINT message, WPARAM parameter, LPARAM long_parameter )
{
	keybinds::handle_input( message, parameter );

	static auto lazy_callwndproc = LI_FN( CallWindowProcA ).get( );

	return lazy_callwndproc( original, window, message, parameter, long_parameter );
}

void wndproc_hook::init( )
{
	original =
		reinterpret_cast< WNDPROC >( LI_FN( SetWindowLongA )( hotwheels::window, GWL_WNDPROC, reinterpret_cast< LONG_PTR >( wndproc_detour ) ) );
}

void wndproc_hook::unload( )
{
	LI_FN( SetWindowLongA )( hotwheels::window, GWL_WNDPROC, reinterpret_cast< LONG_PTR >( original ) );
}
