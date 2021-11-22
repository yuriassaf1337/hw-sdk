#pragma once
#include <iostream>

#include "../../../utils/netvar/netvar.h"
#include "../../../globals/includes/includes.h"

#include "i_client_entity.h"

namespace sdk
{
	struct c_base_entity : public i_client_entity
	{
	public:
		NETVAR(team_number, std::int32_t, "CBaseEntity", "m_iTeamNum");
	};
} // namespace sdk
