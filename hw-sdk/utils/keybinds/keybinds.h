#pragma once

#include "../../dependencies/lazy_importer/lazy_importer.h"
#include "../math/types/vector.h"
#include <Windows.h>
#include <deque>

namespace input
{
	enum key_state_t
	{
		KEY_NONE,
		KEY_UP,
		KEY_DOWN,
		KEY_RELEASED
	};

	constexpr static inline std::uint64_t MAX_RELEASED_TIME = 100;

	struct impl {
	private:
		struct key_info_t {
			input::key_state_t state;
			std::uint64_t time;

			constexpr key_info_t( ) : state{ input::key_state_t::KEY_NONE }, time{ 0 } { }

			constexpr key_info_t( input::key_state_t state, std::uint64_t time ) : state{ state }, time{ time } { }
		};

	public:
		std::array< key_info_t, 255U > key_states = { };

		struct {
			math::vec2< int > pos;
			int scroll_amt;
		} mouse;

		void think( UINT msg, WPARAM wparam, LPARAM lparam );

		template< auto state >
		bool key_state( std::uint8_t key_id )
		{
			auto& key = key_states[ key_id ];

			std::uint64_t time = LI_FN( GetTickCount64 )( );

			if constexpr ( state == key_state_t::KEY_RELEASED ) {
				if ( key.state == state )
					if ( time - key.time <= input::MAX_RELEASED_TIME )
						return key.state = key_state_t::KEY_UP;
					else
						key.state = key_state_t::KEY_UP;

				return false;
			} else
				return key.state == state;
		}
	};
} // namespace input

inline input::impl g_input;
