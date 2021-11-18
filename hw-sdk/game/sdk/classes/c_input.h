#pragma once

#include "../../../globals/macros/macros.h"
#include "../../../utils/math/types/vector.h"
#include "../../../utils/vfunc/vfunc.h"
#include "c_usercmd.h"
#include "c_verified_cmd.h"

#include <iostream>

constexpr std::size_t multiplayer_backup = 150;

namespace sdk
{
	class c_input
	{
	public:
		PAD( 0xC );
		bool trackir_available;
		bool mouse_initiated;
		bool mouse_active;
		bool JoystickAdvancedInit;
		PAD( 0x2C );
		void* Keys;
		PAD( 0x6C );
		bool CameraInterceptingMouse;
		bool CameraInThirdPerson;
		bool CameraMovingWithMouse;
		math::vec3 m_vecCameraOffset;
		bool CameraDistanceMove;
		int CameraOldX;
		int CameraOldY;
		int CameraX;
		int CameraY;
		bool CameraIsOrthographic;
		math::vec3 PreviousViewAngles;
		math::vec3 PreviousViewAnglesTilt;
		float LastForwardMove;
		int ClearInputState;
		PAD( 0x8 );
		sdk::c_user_cmd* m_pCommands;
		sdk::c_verified_cmd* m_pVerifiedCommands;

		inline sdk::c_user_cmd* get_user_cmd( int sequence_number );
		inline sdk::c_user_cmd* get_user_cmd( int slot, int sequence_number );
		inline sdk::c_verified_cmd* get_verified_cmd( int sequence_number );
	};
} // namespace sdk

sdk::c_user_cmd* sdk::c_input::get_user_cmd( int sequence_number ){
	return reinterpret_cast< sdk::c_user_cmd*( __thiscall* )( void*, int, int ) >( virtual_func::get(this, 8) )(this, 0, sequence_number);
}

sdk::c_user_cmd* sdk::c_input::get_user_cmd( int slot, int sequence_number )
{
	return reinterpret_cast< sdk::c_user_cmd*( __thiscall* )( void*, int, int ) >( virtual_func::get(this, 8) )(this, slot, sequence_number);
}

sdk::c_verified_cmd* sdk::c_input::get_verified_cmd( int sequence_number ) 
{
	auto verified_commands = *reinterpret_cast<sdk::c_verified_cmd**>(reinterpret_cast<std::uint32_t>(this) + 0xF8);

	return &verified_commands[sequence_number % multiplayer_backup];
}
