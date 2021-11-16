#pragma once

#include "../../dependencies/lazy_importer/lazy_importer.h"
#include "../math/types/vector.h"
#include <Windows.h>
#include <deque>

namespace input
{
	struct impl {
	public:
		explicit impl( ) = default;

		enum key_state_t
		{
			key_none = -1,
			key_up,
			key_down,
		};

		std::array< key_state_t, 256U > key_states     = { key_up };
		std::array< key_state_t, 256U > old_key_states = { key_up };

		struct {
			math::vec2< int > pos;
			math::vec2< int > old_pos;
			int scroll_amt;
		} mouse;

		inline bool is_key_pressed( std::uint32_t vk )
		{
			return key_states[ vk ] == key_state_t::key_down && old_key_states[ vk ] == key_state_t::key_up;
		}

		inline bool is_key_released( std::uint32_t vk )
		{
			return key_states[ vk ] == key_state_t::key_up && old_key_states[ vk ] == key_state_t::key_down;
		}

		inline bool is_key_down( std::uint32_t vk )
		{
			return key_states[ vk ] == key_state_t::key_down;
		}

		inline bool is_key_up( std::uint32_t vk )
		{
			return key_states[ vk ] == key_state_t::key_up;
		}

		bool mouse_in_area( int x, int y, int w, int h )
		{
			return mouse.pos.x >= x && mouse.pos.y >= y && mouse.pos.x <= ( x + w ) && mouse.pos.y <= ( y + h );
		}
		inline bool mouse_in_area( const math::vec2< int > pos, const math::vec2< int > size )
		{
			return mouse_in_area( pos.x, pos.y, size.x, size.y );
		}

		void think( HWND window, UINT msg, WPARAM wparam, LPARAM lparam );
	};
} // namespace input

inline input::impl g_input;
