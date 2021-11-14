#pragma once
#include "../includes/includes.h"

namespace gui
{
	class window
	{
	public:
		gui::window( ) = default;
		gui::window( std::string_view window_name, math::vec2< int >& window_position, math::vec2< int >& window_size,
		             std::deque< std::string_view > window_tabs, int& window_selected_tab ){

		};

		void think( );

	private:
		std::vector< gui::window > m_windows;
	};
} // namespace gui

inline gui::window g_window;
