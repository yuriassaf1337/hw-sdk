#pragma once
#include <iostream>

#include "../../../utils/netvar/netvar.h"
#include "../../../globals/includes/includes.h"

#include "../enums/teams.h"
#include "i_client_entity.h"

namespace sdk
{
	struct c_base_entity : public i_client_entity
	{
	public:
		NETVAR(team_number, sdk::enums::teams, "CBaseEntity", "m_iTeamNum");
	};
} // namespace sdk
