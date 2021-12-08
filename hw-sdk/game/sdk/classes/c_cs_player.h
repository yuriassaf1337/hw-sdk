#pragma once
#include <iostream>

#include "../../../globals/includes/includes.h"

#include "../../../utils/convars/convars.h"

#include "c_base_player.h"

namespace sdk
{
	struct c_cs_player : public c_base_player {
	public:
		NETVAR( has_defuser, bool, "CCSPlayer", "m_bHasDefuser" );
		NETVAR( gun_game_immunity, bool, "CCSPlayer", "m_bGunGameImmunity" );
		NETVAR( shots_fired, std::int32_t, "CCSPlayer", "m_iShotsFired" );
		NETVAR( eye_angles, math::vec3, "CCSPlayer", "m_angEyeAngles[0]" );
		NETVAR( armor_value, int, "CCSPlayer", "m_ArmorValue" );
		NETVAR( has_heavy_armor, bool, "CCSPlayer", "m_bHasHeavyArmor" );
		NETVAR( has_helmet, bool, "CCSPlayer", "m_bHasHelmet" );
		NETVAR( is_scoped, bool, "CCSPlayer", "m_bIsScoped" );
		NETVAR( lower_body_yaw_target, float, "CCSPlayer", "m_flLowerBodyYawTarget" );
		NETVAR( flash_max_alpha, float, "CCSPlayer", "m_flFlashMaxAlpha" );
		NETVAR( account, std::int32_t, "CCSPlayer", "m_iAccount" );
		NETVAR( flash_duration, float, "CCSPlayer", "m_flFlashDuration" );

		bool is_enemy( sdk::teams team )
		{
			static auto mp_teammates_are_enemies = g_convars[ _( "mp_teammates_are_enemies" ) ];

			if ( mp_teammates_are_enemies->get_bool( ) )
				return true;

			if ( this->team_number( ) == team )
				return false;

			return true;
		}

		bool is_alive( )
		{
			return ( this->life_state( ) == sdk::life_state::LIFE_ALIVE && this->health( ) > 0 ) && !gun_game_immunity( );
		}
	};
} // namespace sdk
