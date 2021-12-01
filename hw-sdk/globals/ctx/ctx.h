#pragma once
#include "../../game/sdk/classes/c_base_combat_weapon.h"
#include "../../game/sdk/classes/c_cs_player.h"
#include "../../game/sdk/classes/c_usercmd.h"
#include "../../game/sdk/enums/buttons.h"
#include "../../game/sdk/enums/move_type.h"

namespace ctx
{
	struct impl {
		sdk::c_cs_player* local           = nullptr;
		sdk::c_user_cmd* cmd              = nullptr;
		sdk::c_base_combat_weapon* weapon = nullptr;

		struct {
			sdk::c_user_cmd* cmd    = nullptr;
			sdk::c_cs_player* local = nullptr;
		} backup;

		math::vec2< int > screen_size = { };

		bool running_post_think = false;
	};
} // namespace ctx

inline ctx::impl g_ctx;
