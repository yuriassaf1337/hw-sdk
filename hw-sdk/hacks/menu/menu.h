#pragma once

#include <d3d9.h>

#include "config/config.h"

struct ImFont;

namespace menu
{
	struct impl {
		ImFont* menu_font     = nullptr;
		bool menu_open        = true;
		bool menu_initialised = false;
		int menu_tab          = 0;
		HWND window           = nullptr;

		bool init_input( );
		void draw( );
	};
}; // namespace menu

inline menu::impl g_menu;
