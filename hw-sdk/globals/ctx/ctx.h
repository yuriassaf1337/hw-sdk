#pragma once
#include "../../game/sdk/classes/c_base_combat_weapon.h"
#include "../../game/sdk/classes/c_cs_player.h"
#include "../../game/sdk/classes/c_usercmd.h"

namespace ctx
{
	struct impl {
		sdk::c_cs_player* local           = nullptr;
		sdk::c_user_cmd* cmd              = nullptr;
		sdk::c_base_combat_weapon* weapon = nullptr;
	};
} // namespace ctx

inline ctx::impl g_ctx;
