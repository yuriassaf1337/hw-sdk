#pragma once

#include <d3d9.h>

#include "config/config.h"

namespace menu
{
	struct impl {
		bool menu_open              = true;
		bool menu_initialised     = false;
		HWND window          = nullptr;

		bool init_input( );
		void init( IDirect3DDevice9* device );
		void draw( );
	};
}; // namespace menu

inline menu::impl g_menu;
