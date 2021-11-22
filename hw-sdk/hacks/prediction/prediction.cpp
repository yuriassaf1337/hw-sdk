#include "prediction.h"
#include "../../globals/intefaces/interfaces.h"

void prediction::impl::post_think( ) { }

void prediction::impl::update( ) { }

void prediction::impl::start( ) { }

void prediction::impl::end( ) { }

void prediction::impl::reset( )
{
	g_interfaces.prediction->restore_entity_to_predicted_frame( g_interfaces.prediction->predicted_commands( ) - 1 );
	g_interfaces.prediction->previous_start_frame( ) = -1;
	g_interfaces.prediction->predicted_commands( )   = 0;
}
