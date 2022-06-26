#include "movement.h"
#include "../../../utils/keybinds/keybinds.h"
#include "../../menu/config/config.h"
#include "../../prediction/prediction.h"

void movement::impl::pre_prediction::think( )
{
	if ( !g_ctx.local->is_alive( ) || !g_interfaces.engine->connected_safe( ) )
		return;

	if ( !g_ctx.cmd->buttons.has( sdk::IN_BULLRUSH ) && g_config.find< bool >( HASH( "m_fastduck" ) ) )
		g_ctx.cmd->buttons.add( sdk::IN_BULLRUSH );

	g_movement.bhop( );
}

void movement::impl::post_prediction::think( )
{
	if ( !g_ctx.local->is_alive( ) || !g_interfaces.engine->connected_safe( ) )
		return;

	g_movement.edge_jump( );

	g_movement.jump_bug( );

	g_movement.mini_jump( );
}

void movement::impl::movement_fix( sdk::c_user_cmd* command, math::vec3 old_view_angle )
{
	command->view_angles = command->view_angles.normalize( );

	static auto cl_forwardspeed = g_convars[ _( "cl_forwardspeed" ) ];
	static auto cl_sidespeed    = g_convars[ _( "cl_sidespeed" ) ];

	float max_forward_speed = cl_forwardspeed->get_float( );
	float max_side_speed    = cl_sidespeed->get_float( );

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
}

void movement::impl::edge_jump( )
{
	if ( !g_config.find< bool >( HASH( "m_ej" ) ) || !g_input.key_state< input::KEY_DOWN >( g_config.find< std::uint8_t >( HASH( "m_ej_key" ) ) ) ) {
		g_movement.longjump.start_timer = false;
		g_movement.longjump.time_stamp  = 0;

		return;
	}

	if ( g_prediction.backup_vars.flags.has( sdk::flags::ONGROUND ) &&
	     !( g_ctx.local->flags( ).has( sdk::flags::ONGROUND ) && !g_ctx.cmd->buttons.has( sdk::buttons::IN_JUMP ) ) ) {
		g_ctx.cmd->buttons.add( sdk::buttons::IN_JUMP );

		g_movement.longjump.start_timer = true;
		g_movement.longjump.time_stamp  = g_interfaces.globals->tick_count;
	}

	if ( g_config.find< bool >( HASH( "m_lj" ) ) ) {
		if ( g_movement.longjump.start_timer ) {
			if ( g_movement.longjump.time_stamp + 2 > g_interfaces.globals->tick_count ) {
				// did lj = true
				g_ctx.cmd->buttons.add( sdk::buttons::IN_DUCK );
			} else {
				// did lj = false
				g_movement.longjump.start_timer = false;
			}
		}

		if ( g_ctx.cmd->buttons.has( sdk::buttons::IN_DUCK ) && !g_ctx.cmd->buttons.has( sdk::buttons::IN_JUMP ) &&
		     g_prediction.backup_vars.flags.has( sdk::flags::ONGROUND ) )
			g_ctx.cmd->buttons.remove( sdk::buttons::IN_DUCK );
	}
}

void movement::impl::jump_bug( )
{
	if ( !g_config.find< bool >( HASH( "m_jb" ) ) )
		return;

	if ( !g_input.key_state< input::KEY_DOWN >( g_config.find< std::uint8_t >( HASH( "m_jb_key" ) ) ) )
		return;

	[[unlikely]] if ( g_ctx.local->move_type( ).has_any_of(
						  { sdk::move_type::MOVE_NOCLIP, sdk::move_type::MOVE_LADDER, sdk::move_type::MOVE_FLY } ) ) return;

	[[unlikely]] if ( !( g_ctx.cmd->buttons.has( sdk::buttons::IN_JUMP ) ) )
	{
		static bool ducked = false;

		if ( g_ctx.local->flags( ).has( sdk::flags::ONGROUND ) && !g_prediction.backup_vars.flags.has( sdk::flags::ONGROUND ) && !ducked ) {
			g_ctx.cmd->buttons.add( sdk::buttons::IN_DUCK );

			ducked = true;
		} else
			ducked = false;

		// if player onground and somehow ducked is still true, reset

		if ( g_prediction.backup_vars.flags.has( sdk::flags::ONGROUND ) && ducked )
			ducked = false;
	}
	else // perform normal jb.
	{
		if ( g_ctx.local->flags( ).has( sdk::flags::ONGROUND ) ) {
			if ( !g_prediction.backup_vars.flags.has( sdk::flags::ONGROUND ) )
				g_ctx.cmd->buttons.add( sdk::buttons::IN_DUCK );

			g_ctx.cmd->buttons.remove( sdk::buttons::IN_JUMP );
		}

		// secret sauce
		if ( !g_ctx.local->flags( ).has( sdk::flags::ONGROUND ) && g_prediction.backup_vars.flags.has( sdk::flags::ONGROUND ) )
			g_ctx.cmd->buttons.remove( sdk::buttons::IN_DUCK );
	}
}

void movement::impl::mini_jump( )
{
	if ( !g_config.find< bool >( HASH( "m_mj" ) ) )
		return;

	if ( !g_input.key_state< input::KEY_DOWN >( g_config.find< std::uint8_t >( HASH( "m_mj_key" ) ) ) )
		return;

	[[unlikely]] if ( g_ctx.local->move_type( ).has_any_of(
						  { sdk::move_type::MOVE_NOCLIP, sdk::move_type::MOVE_LADDER, sdk::move_type::MOVE_FLY } ) ) return;

	if ( g_prediction.backup_vars.flags.has( sdk::flags::ONGROUND ) && !g_ctx.local->flags( ).has( sdk::flags::ONGROUND ) ) {
		g_ctx.cmd->buttons.add( sdk::buttons::IN_DUCK | sdk::buttons::IN_JUMP );
	}
}

void movement::impl::bhop( )
{
	if ( !g_config.find< bool >( HASH( "m_bh" ) ) )
		return;

	if ( g_config.find< bool >( HASH( "m_jb" ) ) && g_input.key_state< input::KEY_DOWN >( g_config.find< std::uint8_t >( HASH( "m_jb_key" ) ) ) )
		return;

	// will return if player is noclip/ladder/fly mode
	[[unlikely]] if ( g_ctx.local->move_type( ).has_any_of(
						  { sdk::move_type::MOVE_NOCLIP, sdk::move_type::MOVE_LADDER, sdk::move_type::MOVE_FLY } ) ) return;

	// remove jump flag if player in air
	if ( !g_ctx.local->flags( ).has( sdk::flags::ONGROUND ) )
		g_ctx.cmd->buttons.remove( sdk::buttons::IN_JUMP );
}
