#pragma once

#include <iostream>

// dependencies
#include "../dependencies/minhook/include/MinHook.h"
#include "../dependencies/mocking_bird/mocking_bird.h"

// game
#include "../game/sdk/classes/c_cs_player.h"
#include "../game/sdk/include.h"

// utils
#include "../utils/console/console.h"
#include "../utils/detour/detour.h"

// globals
#include "../globals/ctx/ctx.h"
#include "../globals/interfaces/interfaces.h"

// hacks
#include "../hacks/features/aimbot/aimbot.h"
#include "../hacks/features/movement/movement.h"
#include "../hacks/prediction/prediction.h"

// imgui
#include "../hacks/menu/imgui/imgui_helper.h"

namespace hooks
{
	struct impl {
		bool init( );
		void unload( );
	};
} // namespace hooks

inline hooks::impl g_hooks;

#include "hooks.inl"
