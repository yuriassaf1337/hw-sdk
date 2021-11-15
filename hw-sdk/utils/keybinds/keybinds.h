#pragma once

#include "../../dependencies/lazy_importer/lazy_importer.h"
#include "../math/types/vector.h"
#include <Windows.h>
#include <deque>
#include <functional>

namespace input
{
	enum key_state
	{
		NONE,
		UP,
		DOWN,
		RELEASED
	};

	struct keybind_t {
		std::size_t key;
		std::function< void( bool ) > callback;
	};

	constexpr static inline std::uint64_t MAX_RELEASED_TIME = 100;

	struct impl {
	private:
		struct key_info_t {
			input::key_state m_state;
			std::uint64_t m_time;

			constexpr key_info_t( ) : m_state{ input::key_state::NONE }, m_time{ 0 } { }

			constexpr key_info_t( input::key_state state, std::uint64_t time ) : m_state{ state }, m_time{ time } { }
		};

	public:
		struct {
			math::vec2< float > pos{ };
			std::int32_t scroll_amt{ };
		} mouse;

		std::array< key_info_t, 255 > m_keys{ };

		template< auto state >
		bool key_state( std::uint8_t key_id )
		{
			auto& key = m_keys[ key_id ];

			std::uint64_t time = LI_FN( GetTickCount64 )( );

			if constexpr ( state == key_state::RELEASED ) {
				if ( key.m_state == state )
					if ( time - key.m_time <= input::MAX_RELEASED_TIME )
						return key.m_state = key_state::UP;
					else
						key.m_state = key_state::UP;

				return false;
			} else
				return key.m_state == state;
		}

		BOOL think( UINT msg, WPARAM w_param, LPARAM l_param );
	};
} // namespace input

inline input::impl g_input;
