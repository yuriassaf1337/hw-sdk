#include "gui.h"
#include "groupbox/groupbox.h"
#include "window/window.h"

void gui::impl::draw( )
{
	// invoke all tabs
	g_tabs.invoke_tabs( { _( "Aimbot" ), _( "Visuals" ), _( "Misc" ), _( "Skins" ), _( "Demos" ), _( "Config" ) } );

	// begin main window
	if ( g_window.invoke_window( _( "hotwheels" ) ) ) {
		g_groupbox.invoke_groupbox( _( "Test" ), { 100, 70 } );
		g_window.end_window( );
	}
}
