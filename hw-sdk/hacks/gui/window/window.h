#pragma once
#include "../includes/includes.h"
#include <stack>

namespace gui
{
	struct window {
		// todo on position, calculate middle of screen to spawn menu in(menu width / 2 - screen width / 2)
		math::vec2< int > position = { 250, 250 };
		math::vec2< int > size     = { 537, 621 };

		// cursors / focus
		std::stack< math::vec2< int > > cursor_pos_stack;
		std::size_t focused_id;

		// tabs
		std::vector< std::pair< std::string_view, std::string_view > > tabs;
		int active_tab = 0;

		// util(couldnt think of a better name lol)
		struct {
			bool open     = false;
			bool dragging = false;
		} util;
	};
} // namespace gui

inline gui::window g_window;
