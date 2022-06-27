#pragma once

#include "config/config.h"

namespace menu
{
	struct impl {
		bool menu_open = true;

		void draw( );
	};
}; // namespace menu

inline menu::impl g_menu;
