#include "keybinds.h"
#include "../../dependencies/lazy_importer/lazy_importer.h"
#include "../../globals/hooks/wndproc/wndproc.h"

void input::impl::think( HWND window, UINT msg, WPARAM wparam, LPARAM lparam )
{
	old_key_states = key_states;
	mouse.old_pos  = mouse.pos;

	std::uint32_t key       = 0u;
	impl::key_state_t state = key_none;

	switch ( msg ) {
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		if ( wparam < 256u ) {
			key   = wparam;
			state = key_down;
		}
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		if ( wparam < 256u ) {
			key   = wparam;
			state = key_up;
		}
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
		key   = VK_LBUTTON;
		state = msg == WM_LBUTTONUP ? key_up : key_down;
		break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		key   = VK_RBUTTON;
		state = msg == WM_RBUTTONUP ? key_up : key_down;
		break;
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
		key   = VK_MBUTTON;
		state = msg == WM_MBUTTONUP ? key_up : key_down;
		break;
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
		key   = ( GET_XBUTTON_WPARAM( wparam ) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2 );
		state = msg == WM_XBUTTONUP ? key_up : key_down;
		break;
	case WM_MOUSEWHEEL:
	case WM_MOUSEHWHEEL:
		mouse.scroll_amt = GET_WHEEL_DELTA_WPARAM( wparam ) / WHEEL_DELTA;
		break;
	case WM_CHAR:
		break;
	default:
		if ( msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST ) {
			mouse.pos = math::vec2< int >( ( int )( LOWORD( lparam ) ), ( int )( HIWORD( lparam ) ) );
		}
		break;
	}

	if ( state == key_none )
		return;

	key_states[ key ] = state;
}
