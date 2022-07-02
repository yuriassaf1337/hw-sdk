#include "indicators.h"
#include "../../../globals/ctx/ctx.h"
#include "../../menu/config/config.h"

void indicators::impl::reset_data( )
{

}

void indicators::impl::render( )
{
	if ( !g_ctx.local || !g_ctx.local->is_alive( ) || !g_interfaces.engine->is_fully_connected( ) ) {
		reset_data( );
		return;
	}

	if ( g_config.find< bool >( HASH( "m_velocity_indicator" ) ) )
		g_indicators.velocity( );

	if ( g_config.find< bool >( HASH( "m_stamina_indicator" ) ) )
		g_indicators.stamina( );
}

void indicators::impl::velocity( ) { }

void indicators::impl::stamina( ) { }