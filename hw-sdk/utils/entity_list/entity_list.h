#pragma once
#include "../../game/sdk/classes/c_base_player.h"
#include "../../game/sdk/classes/c_cs_player.h"
#include "../../game/sdk/classes/i_client_entity.h"
#include "../../globals/interfaces/interfaces.h"

#include <deque>

namespace entity_list
{
	struct impl {
		std::deque< sdk::c_cs_player* > players;

		void update( );
	};
} // namespace entity_list

inline entity_list::impl g_entity_list;
