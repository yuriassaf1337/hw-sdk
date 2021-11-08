#pragma once
#include "../../../globals/macros/macros.h"
#include "../../../utils/helpers/bit_flag.h"
#include "../../../utils/math/types/vector.h"
#include <cstdint>

namespace sdk
{
	class c_usercmd
	{
	public:
		PAD( 4 );
		int command_number;
		int tick_count;
		math::vec3 view_angles;
		math::vec3 aim_direction;
		float forward_move;
		float side_mode;
		float up_move;
		int_flag buttons;
		char impulse;
		int weapon_select;
		int weapon_subtype;
		int random_seed;
		short moused_x;
		short moused_y;
		bool has_been_predicted;
	};
} // namespace sdk
