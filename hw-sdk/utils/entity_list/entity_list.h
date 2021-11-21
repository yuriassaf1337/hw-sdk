#pragma once
#include "../../game/sdk/classes/i_client_entity.h"
#include "../../globals/intefaces/interfaces.h"

#include <deque>

namespace entity_list
{
	inline std::deque< sdk::i_client_entity* > entities;

	void update( );
} // namespace entity_list
