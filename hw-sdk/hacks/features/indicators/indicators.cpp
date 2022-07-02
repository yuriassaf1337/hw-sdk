#include "indicators.h"
#include "../../../globals/ctx/ctx.h"
#include "../../menu/config/config.h"

void indicators::impl::reset_data( )
{
	m_velocity_info.last_vel       = 0;
	m_velocity_info.tick_prev      = 0;
	m_velocity_info.take_off       = 0;
	m_velocity_info.take_off_time  = 0.f;
	m_velocity_info.last_on_ground = false;
}

void indicators::impl::render( )
{
	if ( !g_interfaces.engine->is_fully_connected( ) || !g_ctx.local ) {
		reset_data( );
		return;
	}

	if ( g_config.find< bool >( HASH( "m_velocity_indicator" ) ) )
		g_indicators.velocity( );

	if ( g_config.find< bool >( HASH( "m_stamina_indicator" ) ) )
		g_indicators.stamina( );
}

void indicators::impl::velocity( )
{
	// TODO: FIX THIS RETARD SHITS ( SRY :) )
	int floored_velocity = static_cast< int >( std::roundf( g_ctx.local->velocity( ).length_2d( ) ) );

	if ( m_velocity_info.last_on_ground && !( g_ctx.local->flags( ) & sdk::flags::ONGROUND ) ) {
		m_velocity_info.take_off      = floored_velocity;
		m_velocity_info.take_off_time = g_interfaces.globals->current_time + 2.f;
	}

	float alpha = g_config.find< bool >( HASH( "m_velocity_indicator_fade" ) ) ? floored_velocity >= 310.f ? 310.f : floored_velocity / 310.f : 1.f;

	color _color = floored_velocity == m_velocity_info.last_vel  ? color( 255, 199, 89, alpha * 255 )
	               : floored_velocity < m_velocity_info.last_vel ? color( 255, 119, 119, alpha * 255 )
	                                                             : color( 30, 255, 109, alpha * 255 );
	bool should_draw_pre =
		( !( g_ctx.local->flags( ) & sdk::flags::ONGROUND ) || ( m_velocity_info.take_off_time > g_interfaces.globals->current_time ) ) &&
		g_config.find< bool >( HASH( "m_velocity_indicator_show_pre" ) );

	char buf[ 512 ];
	snprintf( buf, sizeof( buf ), should_draw_pre ? _( "%i (%i)" ) : _( "%i" ), floored_velocity, m_velocity_info.take_off );

	g_render.render_text( g_ctx.screen_size.x / 2, g_ctx.screen_size.y / 2, font_alignment::AL_HORIZONTAL_CENTER, font_flags::FLAG_DROPSHADOW, buf,
	                      g_fonts[ HASH( "indicator_verdana_font" ) ], _color );

	if ( m_velocity_info.tick_prev + 5 < g_interfaces.globals->tick_count ) {
		m_velocity_info.last_vel  = floored_velocity;
		m_velocity_info.tick_prev = g_interfaces.globals->tick_count;
	}

	m_velocity_info.last_on_ground = g_ctx.local->flags( ) & sdk::flags::ONGROUND;
}

void indicators::impl::stamina( ) { }

void indicators::impl::keybinds( ) { }
