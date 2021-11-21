#include "gui.h"
#include "window/window.h"

void gui::impl::draw( )
{
	if ( g_window.begin_window( _( "hotwheels" ) ) ) {
		g_window.end_window( );
	}
}
