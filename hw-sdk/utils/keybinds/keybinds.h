#pragma once

#include "../../dependencies/lazy_importer/lazy_importer.h"
#include "../math/types/vector.h"
#include <Windows.h>
#include <deque>
#include <functional>

namespace keybinds
{
	enum key_state
	{
		NONE,
		UP,
		DOWN,
		RELEASED
	};

	constexpr static inline std::uint64_t MAX_RELEASED_TIME = 100;

	struct impl {
	private:
		struct key_info_t {
			keybinds::key_state m_state;
			std::uint64_t m_time;

			constexpr key_info_t( ) : m_state{ keybinds::key_state::NONE }, m_time{ 0 } { }

			constexpr key_info_t( keybinds::key_state state, std::uint64_t time ) : m_state{ state }, m_time{ time } { }
		};

	public:
		struct {
			math::vec2< float > pos{ };
			std::int32_t scroll_amt{ };
		} mouse;

		std::array< key_info_t, 255 > m_keys{ };

		void think( UINT msg, WPARAM w_param, LPARAM l_param );
	};
} // namespace keybinds

inline keybinds::impl g_keybind_module;

namespace input
{
	struct impl {
	public:
		template< auto state >
		bool key_state( std::uint8_t key_id )
		{
			auto& key = g_keybind_module.m_keys[ key_id ];

			std::uint64_t time = LI_FN( GetTickCount64 )( );

			if constexpr ( state == keybinds::key_state::RELEASED ) {
				if ( key.m_state == state )
					if ( time - key.m_time <= keybinds::MAX_RELEASED_TIME )
						return key.m_state = keybinds::key_state::UP;
					else
						key.m_state = keybinds::key_state::UP;

				return false;
			} else
				return key.m_state == state;
		}
	};
} // namespace input

inline input::impl g_input;
