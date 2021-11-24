#pragma once
#include "../../game/sdk/classes/c_base_player.h"
#include "../../game/sdk/classes/c_cs_player.h"
#include "../../game/sdk/classes/i_client_entity.h"
#include "../../globals/intefaces/interfaces.h"

#include <deque>

namespace entity_list
{
	inline std::deque< sdk::i_client_entity* > entities;
	inline sdk::c_cs_player* local_player;

	void update( );
} // namespace entity_list
