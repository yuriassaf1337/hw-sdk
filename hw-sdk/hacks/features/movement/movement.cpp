#include "movement.h"
#include "../../../utils/keybinds/keybinds.h"
#include "../../prediction/prediction.h"

void movement::impl::pre_prediction::think( )
{
	if ( !g_ctx.local->is_alive( ) || !g_interfaces.engine->connected_safe( ) )
		return;

	if ( !g_ctx.cmd->buttons.has( sdk::IN_BULLRUSH ) )
		g_ctx.cmd->buttons.add( sdk::IN_BULLRUSH );

	g_movement.bhop( );

	// g_movement.mini_hop( );
}

void movement::impl::post_prediction::think( )
{
	if ( !g_ctx.local->is_alive( ) || !g_interfaces.engine->connected_safe( ) )
		return;
}

void movement::impl::movement_fix( sdk::c_user_cmd* command, math::vec3 old_view_angle )
{
	command->view_angles = command->view_angles.normalize( );

	static auto cl_forwardspeed = g_convars[ _( "cl_forwardspeed" ) ];
	static auto cl_sidespeed    = g_convars[ _( "cl_sidespeed" ) ];
	static auto cl_upspeed      = g_convars[ _( "cl_upspeed" ) ];

	float max_forward_speed = cl_forwardspeed->get_float( );
	float max_side_speed    = cl_sidespeed->get_float( );
	float max_up_speed      = cl_upspeed->get_float( );

	math::vec3 forward{ }, right{ }, up{ };
	math::angle_vectors( old_view_angle, &forward, &right, &up );

	forward.z = right.z = up.x = up.y = 0.f;

	forward.normalize_in_place( );
	right.normalize_in_place( );
	up.normalize_in_place( );

	math::vec3 old_forward{ }, old_right{ }, old_up{ };
	math::angle_vectors( command->view_angles, &old_forward, &old_right, &old_up );

	old_forward.z = old_right.z = old_up.x = old_up.y = 0.f;

	old_forward.normalize_in_place( );
	old_right.normalize_in_place( );
	old_up.normalize_in_place( );

	float pitch_forward = forward.x * command->forward_move;
	float yaw_forward   = forward.y * command->forward_move;
	float pitch_side    = right.x * command->side_move;
	float yaw_side      = right.y * command->side_move;
	float roll_up       = up.z * command->up_move;

	float x =
		old_forward.x * pitch_side + old_forward.y * yaw_side + old_forward.x * pitch_forward + old_forward.y * yaw_forward + old_forward.z * roll_up;
	float y = old_right.x * pitch_side + old_right.y * yaw_side + old_right.x * pitch_forward + old_right.y * yaw_forward + old_right.z * roll_up;
	float z = old_up.x * yaw_side + old_up.y * pitch_side + old_up.x * yaw_forward + old_up.y * pitch_forward + old_up.z * roll_up;

	command->forward_move = std::clamp( x, -max_forward_speed, max_forward_speed );
	command->side_move    = std::clamp( y, -max_side_speed, max_side_speed );
	command->up_move      = std::clamp( z, -max_up_speed, max_up_speed );
}

void movement::impl::jump_bug( )
{
	static bool jump_bugged = false;

	bool is_on_ground = !( g_prediction.backup_vars.flags.has( sdk::ONGROUND ) ) && g_ctx.local->flags( ).has( sdk::ONGROUND );

	if ( !g_input.key_state< input::KEY_DOWN >( VK_SPACE ) ) {
		if ( is_on_ground && !jump_bugged ) {
			g_ctx.cmd->buttons.add( sdk::IN_DUCK );
			jump_bugged = true;
		} else {
			jump_bugged = false;
		}

		if ( g_prediction.backup_vars.flags.has( sdk::ONGROUND ) && jump_bugged )
			jump_bugged = false;
	} else {
		int pre_flags = g_ctx.local->flags( );

		g_prediction.start( g_ctx.local );
		g_prediction.end( g_ctx.local );

		if ( g_prediction.backup_vars.flags.has( sdk::ONGROUND ) || !( g_ctx.local->flags( ).has( sdk::ONGROUND ) ) )
			jump_bugged = false;
		else {
			g_ctx.cmd->buttons.add( sdk::IN_DUCK );
			g_ctx.cmd->buttons.remove( sdk::IN_JUMP );
			jump_bugged = true;
		}
	}
}

void movement::impl::mini_hop( )
{
	static bool did_duck = false;
	bool stay_in_duck    = true;

	[[unlikely]] if ( g_ctx.local->move_type( ).has_any_of(
						  { sdk::move_type::MOVE_NOCLIP, sdk::move_type::MOVE_LADDER, sdk::move_type::MOVE_FLY } ) ) return;

	if ( g_prediction.backup_vars.flags.has( sdk::ONGROUND ) && g_ctx.cmd->buttons.has( sdk::IN_JUMP ) ) {
		if ( !did_duck ) {
			did_duck = true;
			g_ctx.cmd->buttons.add( sdk::IN_DUCK );
		} else {
			did_duck = false;

			if ( stay_in_duck )
				g_ctx.cmd->buttons.add( sdk::IN_DUCK );

			g_ctx.cmd->buttons.remove( sdk::IN_JUMP );
		}
	}
}

void movement::impl::bhop( )
{
	// will return if player is noclip/ladder/fly mode
	[[unlikely]] if ( g_ctx.local->move_type( ).has_any_of(
						  { sdk::move_type::MOVE_NOCLIP, sdk::move_type::MOVE_LADDER, sdk::move_type::MOVE_FLY } ) ) return;

	// remove jump flag if player in air
	if ( !g_ctx.local->flags( ).has( sdk::flags::ONGROUND ) )
		g_ctx.cmd->buttons.remove( sdk::buttons::IN_JUMP );
}
