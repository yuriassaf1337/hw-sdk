#pragma once

#include "../../../globals/includes/includes.h"
#include "c_base_entity.h"

namespace sdk
{
	struct c_base_combat_weapon : public c_base_entity {
	public:
		NETVAR(clip_mag, std::int32_t, "CBaseCombatWeapon", "m_iClip1");
	};
} // namespace sdk
