#include "indicators.h"
#include "../../../globals/ctx/ctx.h"
#include "../../menu/config/config.h"

void indicators::impl::think( )
{
	if ( !g_ctx.local->is_alive( ) || !g_interfaces.engine->connected_safe( ) )
		return;

	if ( g_config.find< bool >( HASH( "m_velocity_indicator" ) ) )
		g_indicators.velocity( ); /* brazil brain */

	if ( g_config.find< bool >( HASH( "m_stamina_indicator" ) ) )
		g_indicators.stamina( );
}

void indicators::impl::velocity( ) { }

void indicators::impl::stamina( ) { }