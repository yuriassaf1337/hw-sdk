#include "keybinds.h"
#include "../../dependencies/lazy_importer/lazy_importer.h"
#include "../../globals/hooks/wndproc/wndproc.h"

BOOL input::impl::think( UINT msg, WPARAM w_param, LPARAM l_param )
{
	std::uint8_t key_id        = 0;
	input::key_state key_state = key_state::UP;

	mouse.scroll_amt = 0;

	switch ( msg ) {
	case WM_KEYDOWN:
		key_id    = w_param;
		key_state = key_state::DOWN;
		break;
	case WM_KEYUP:
		key_id    = w_param;
		key_state = key_state::UP;
		break;
	case WM_LBUTTONDOWN:
		key_id    = VK_LBUTTON;
		key_state = key_state::DOWN;
		break;
	case WM_LBUTTONUP:
		key_id    = VK_LBUTTON;
		key_state = key_state::UP;
		break;
	case WM_LBUTTONDBLCLK:
		key_id    = VK_LBUTTON;
		key_state = key_state::DOWN;
		break;
	case WM_RBUTTONDOWN:
		key_id    = VK_RBUTTON;
		key_state = key_state::DOWN;
		break;
	case WM_RBUTTONUP:
		key_id    = VK_RBUTTON;
		key_state = key_state::UP;
		break;
	case WM_RBUTTONDBLCLK:
		key_id    = VK_RBUTTON;
		key_state = key_state::DOWN;
		break;
	case WM_MBUTTONDOWN:
		key_id    = VK_MBUTTON;
		key_state = key_state::DOWN;
		break;
	case WM_MBUTTONUP:
		key_id    = VK_MBUTTON;
		key_state = key_state::UP;
		break;
	case WM_MBUTTONDBLCLK:
		key_id    = VK_MBUTTON;
		key_state = key_state::DOWN;
		break;
	case WM_XBUTTONDOWN:
		key_id    = GET_XBUTTON_WPARAM( w_param ) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2;
		key_state = key_state::DOWN;
		break;
	case WM_XBUTTONUP:
		key_id    = GET_XBUTTON_WPARAM( w_param ) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2;
		key_state = key_state::UP;
		break;
	case WM_XBUTTONDBLCLK:
		key_id    = GET_XBUTTON_WPARAM( w_param ) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2;
		key_state = key_state::DOWN;
		break;
	case WM_MOUSEMOVE:
		mouse.pos = math::vec2< float >( ( int )( short )LOWORD( l_param ), ( int )( short )HIWORD( l_param ) );
		break;
	case WM_MOUSEWHEEL:
		mouse.scroll_amt = -( GET_WHEEL_DELTA_WPARAM( w_param ) / ( WHEEL_DELTA / 4 ) );
		break;
	case WM_KILLFOCUS:
	case WM_SETFOCUS:
		for ( auto& key : m_keys )
			key.m_state = key_state::UP;
		break;
	default:
		break;
	}

	std::uint64_t time = LI_FN( GetTickCount64 )( );

	if ( key_id ) {
		if ( key_state == key_state::UP && m_keys[ key_id ].m_state == key_state::DOWN )
			m_keys[ key_id ] = { key_state::RELEASED, time };
		else
			m_keys[ key_id ] = { key_state, time };
	}

	return LI_FN( CallWindowProcA )( hooks::wndproc_hook, hotwheels::window, msg, w_param, l_param );
}
