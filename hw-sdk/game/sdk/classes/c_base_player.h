#pragma once

#include "../../../globals/includes/includes.h"

#include "../enums/player_flags.h"
#include "c_base_combat_character.h"
#include "c_handle.h"

struct c_base_view_model;

namespace sdk
{
	struct c_base_player : public c_base_combat_character {
	public:
		NETVAR( health, std::int32_t, "CBasePlayer", "m_iHealth" );
		NETVAR( life_state, std::int32_t, "CBasePlayer", "m_lifeState" );
		NETVAR( flags, bit_flag_t< std::int32_t >, "CBasePlayer", "m_fFlags" );
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
		NETVAR( fall_velocity, float, "CBasePlayer", "m_flFallVelocity" );

		// TODO @ liga, im not sure but i think these 3 can be grabbed by prediction datamap
		// so in future we can add datamap shit for netvars
		OFFSET( c_user_cmd*&, current_command, 0xCD2 );
		OFFSET( int_flag&, button_forced, 0xCD1 );
		OFFSET( int_flag&, button_disabled, 0xCD0 );

		[[nodiscard]] int_flag& move_type( )
		{
			static std::uintptr_t offset = netvar::get_table( _( "CBaseEntity" ), _( "m_nRenderMode" ) ) + 0x1;
			return *reinterpret_cast< int_flag* >( reinterpret_cast< std::uintptr_t >( this ) + offset );
		}

		void pre_think( )
		{
			return virtual_func::call< void >( this, 318 );
		}

		void post_think( )
		{
			return virtual_func::call< void >( this, 319 );
		}

		void select_item( const char* item, int sub_type )
		{
			return virtual_func::call< void, const char*, int >( this, 330, item, sub_type );
		}

		static void set_prediction_random_seed( c_user_cmd* command )
		{
			static float* random_seed = *g_client_dll.pattern_scan( _( "A3 ? ? ? ? 66 0F 6E 86 " ) ).add( 0x1 ).as< float** >( );
			*random_seed              = command ? command->random_seed : -1;
		}

		static void set_prediction_player( c_base_entity* entity )
		{
			static c_base_entity** predicted_player =
				*g_client_dll.pattern_scan( _( "89 35 ? ? ? ? F3 0F 10 48" ) ).add( 0x2 ).as< c_base_entity*** >( );
			*predicted_player = entity;
		}

		int determine_simulation_ticks( )
		{
			static auto determine_simulation_ticks_address = g_server_dll.pattern_scan( _( "56 8B F1 33 D2 57 33 FF" ) ).as< std::uintptr_t* >( );
			using determine_simulation_ticks_type          = int( __thiscall* )( c_base_player* );

			return reinterpret_cast< determine_simulation_ticks_type >( determine_simulation_ticks_address )( this );
		}

		void adjust_player_timebase( int simulation_ticks )
		{
			static auto adjust_player_timebase_address =
				g_server_dll.pattern_scan( _( "55 8B EC 51 53 56 8B 75 ? 8B D9 85 F6" ) ).as< std::uintptr_t* >( );
			using adjust_player_timebase_type = void( __thiscall* )( c_base_player*, int );

			reinterpret_cast< adjust_player_timebase_type >( adjust_player_timebase_address )( this, simulation_ticks );
		}

		math::vec3 eye_position( )
		{
			return vector_origin( ) + view_offset( );
		}
	};
} // namespace sdk
