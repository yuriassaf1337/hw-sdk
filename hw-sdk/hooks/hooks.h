#pragma once

#include <iostream>

#include "../dependencies/minhook/include/MinHook.h"
#include "../utils/console/console.h"
#include "../utils/detour/detour.h"

namespace hooks
{
	inline detour::hook create_move;

	struct impl {
		void init( );
		void unload( );
	};
} // namespace hooks

inline hooks::impl g_hooks;
