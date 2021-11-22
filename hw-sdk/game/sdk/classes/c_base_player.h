#pragma once

#include "../../../globals/includes/includes.h"

#include "c_base_combat_character.h"
#include "c_handle.h"

struct c_base_view_model;

namespace sdk
{
	struct c_base_player : public c_base_combat_character {
	public:
		NETVAR( health, std::int32_t, "CBasePlayer", "m_iHealth" );
		NETVAR( life_state, std::int32_t, "CBasePlayer", "m_lifeState" );
		NETVAR( flags, std::int32_t, "CBasePlayer", "m_fFlags" );
		NETVAR( tick_base, std::int32_t, "CBasePlayer", "m_nTickBase" );
		NETVAR( view_offset, math::vec3, "CBasePlayer", "m_vecViewOffset[0]" );
		NETVAR( view_punch_angle, math::vec3, "CBasePlayer", "m_viewPunchAngle" );
		NETVAR( aim_punch_angle, math::vec3, "CBasePlayer", "m_aimPunchAngle" );
		NETVAR( view_model, std::uintptr_t, "CBasePlayer", "m_hViewModel[0]" );
		NETVAR( velocity, math::vec3, "CBasePlayer", "m_vecVelocity[0]" );
		NETVAR( max_speed, float, "CBasePlayer", "m_flMaxspeed" );
		NETVAR( observer_target, std::uintptr_t, "CBasePlayer", "m_hObserverTarget" );
		NETVAR( duck_speed, float, "CBasePlayer", "m_flDuckSpeed" );
		NETVAR( duck_amount, float, "CBasePlayer", "m_flDuckAmount" );
		NETVAR( last_place_name, char, "CBasePlayer", "m_szLastPlaceName" );
	};
} // namespace sdk
