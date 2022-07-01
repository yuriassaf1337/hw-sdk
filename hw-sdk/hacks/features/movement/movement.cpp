#include "movement.h"
#include "../../../utils/keybinds/keybinds.h"
#include "../../menu/config/config.h"
#include "../../prediction/prediction.h"

void movement::impl::pre_prediction::think( )
{
	if ( !g_ctx.local->is_alive( ) || !g_interfaces.engine->is_fully_connected( ) )
		return;

	if ( !g_ctx.cmd->buttons.has( sdk::IN_BULLRUSH ) && g_config.find< bool >( HASH( "m_fast_duck" ) ) )
		g_ctx.cmd->buttons.add( sdk::IN_BULLRUSH );

	g_movement.bhop( );
}

void movement::impl::post_prediction::think( )
{
	if ( !g_ctx.local->is_alive( ) || !g_interfaces.engine->is_fully_connected( ) )
		return;

	g_movement.edge_jump( );

	g_movement.jump_bug( );

	g_movement.mini_jump( );

	g_movement.auto_align( );
}

void movement::impl::movement_fix( sdk::c_user_cmd* cmd, math::vec3 old_view_angle )
{
	cmd->view_angles = cmd->view_angles.normalize( );
}

void movement::impl::edge_jump( )
{
	if ( !g_config.find< bool >( HASH( "m_ej" ) ) || !g_input.key_state< input::KEY_DOWN >( g_config.find< std::uint8_t >( HASH( "m_ej_key" ) ) ) ) {
		g_movement.longjump.start_timer = false;
		g_movement.longjump.time_stamp  = 0;

		return;
	}

	if ( g_prediction.backup_vars.flags.has( sdk::flags::ONGROUND ) && !g_ctx.local->flags( ).has( sdk::flags::ONGROUND ) ) {

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
	}

	if ( g_ctx.cmd->buttons.has( sdk::buttons::IN_DUCK ) && !g_ctx.cmd->buttons.has( sdk::buttons::IN_JUMP ) &&
	     g_prediction.backup_vars.flags.has( sdk::flags::ONGROUND ) )
		g_ctx.cmd->buttons.remove( sdk::buttons::IN_DUCK );
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

void movement::impl::rotate_movement( math::vec3& angle )
{
	if ( angle.is_zero( ) )
		angle = g_interfaces.engine->get_view_angles( );

	math::vec3 vec_move( g_ctx.cmd->forward_move, g_ctx.cmd->side_move, g_ctx.cmd->up_move );

	math::vec3 ang_move{ };
	math::vector_angles( vec_move, ang_move );

	const float speed = vec_move.length_2d( );

	const float rotation = math::deg2rad( g_ctx.cmd->view_angles.y - angle.y + ang_move.y );

	g_ctx.cmd->forward_move = std::cosf( rotation ) * speed;
	g_ctx.cmd->side_move    = std::sinf( rotation ) * speed;
}

const bool movement::impl::alignable( const math::vec3 origin )
{
	const math::vec2 remainder1( 1.f - ( origin.x - std::floor( origin.x ) ), 1.f - ( origin.y - std::floor( origin.y ) ) );
	const math::vec2 remainder2( ( origin.x - std::floor( origin.x ) ), ( origin.y - std::floor( origin.y ) ) );

	return ( ( remainder1.x >= movement::distance_to_stop && remainder1.x <= movement::distance_till_adjust ) ||
	         ( remainder1.y >= movement::distance_to_stop && remainder1.y <= movement::distance_till_adjust ) ) ||
	       ( ( remainder2.x >= movement::distance_to_stop && remainder2.x <= movement::distance_till_adjust ) ||
	         ( remainder2.y >= movement::distance_to_stop && remainder2.y <= movement::distance_till_adjust ) );
}

void movement::impl::auto_align( )
{
	// credits patoke
	if ( !g_config.find< bool >( HASH( "m_auto_align" ) ) )
		return;

	// will return if player is noclip/ladder/fly mode
	[[unlikely]] if ( g_ctx.local->move_type( ).has_any_of(
						  { sdk::move_type::MOVE_NOCLIP, sdk::move_type::MOVE_LADDER, sdk::move_type::MOVE_FLY } ) ) return;

	// user not moving
	if ( static_cast< int >( g_ctx.cmd->side_move ) == 0 && static_cast< int >( g_ctx.cmd->forward_move ) == 0 )
		return;

	if ( g_ctx.local->flags( ).has( sdk::flags::ONGROUND ) )
		return;

	struct {
		const math::vec3 origin    = g_ctx.local->get_abs_origin( );
		const math::vec3 velocity  = g_ctx.local->velocity( );
		const float trace_additive = movement::distance_till_adjust + ( 32.f / 2.f );
		int wall_hit               = 0;
	} m_info;

	if ( !g_movement.alignable( m_info.origin ) )
		return;

	const math::vec2< float > ray_differences[ 4 ] = { math::vec2( m_info.trace_additive, 0.f ), math::vec2( 0.f, m_info.trace_additive ),
		                                               math::vec2( -m_info.trace_additive, 0.f ), math::vec2( 0.f, -m_info.trace_additive ) };
	for ( int i = 1; i <= 4; i++ ) {
		sdk::c_game_trace trace{ };
		sdk::c_trace_filter filter;
		filter.skip = g_ctx.local;

		// we don't to rotate this using our viewangles, it's just gonna make our life harder (ref: https://imgur.com/a/rNSMv9j)
		math::vec3 to = m_info.origin + math::vec3( ray_differences[ i - 1 ].x, ray_differences[ i - 1 ].y, 0 );
		sdk::ray_t ray{ };

		ray.init( m_info.origin, to );
		g_interfaces.engine_trace->trace_ray( ray, sdk::masks::MASK_ALL, &filter, &trace );

		// did we hit something and it wasn't a player?
		if ( trace.did_hit( ) && !trace.entity->is_player( ) )
			m_info.wall_hit = i;
	}

	if ( const int is_wall_parallel = m_info.wall_hit == 1 || m_info.wall_hit == 2 ? 1 : -1; m_info.wall_hit != 0 ) {
		math::vec3 velocity_angle = math::calculate_angle( m_info.origin, m_info.origin + m_info.velocity );

		float v_angle_y = velocity_angle.y;

		float base_yaw = math::normalize_yaw( v_angle_y );

		const float direction =
			velocity_angle.y == 0.f ? -1 * is_wall_parallel : std::round( math::normalize_yaw( velocity_angle.y ) / ( 180.f * is_wall_parallel ) );

		// best strafe angle to align the player
		const float angle_diff =
			math::rad2deg( atan( ( g_ctx.cmd->buttons.has( sdk::buttons::IN_DUCK ) ? 4.6775f : 4.5500f ) / m_info.velocity.length_2d( ) ) ) *
			( 2.f * M_PI );

		float final_yaw = base_yaw + direction * angle_diff;

		math::vec3 angle = { g_ctx.cmd->view_angles.x, math::normalize_yaw( final_yaw ), 0.0f };

		g_movement.rotate_movement( angle );
	}
}
