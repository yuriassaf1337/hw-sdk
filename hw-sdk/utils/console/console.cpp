#include "console.h"

bool console::init( )
{
	if ( !AllocConsole( ) )
		return false;

	AttachConsole( ATTACH_PARENT_PROCESS );

	if ( freopen_s( reinterpret_cast< _iobuf** >( stdout ), x( "CONOUT$" ), x( "w" ), stdout ) != 0 )
		return false;

	if ( !SetConsoleTitleA( x( "[console] hotwheels-v3" ) ) )
		return false;

	return true;
}

void console::unload( )
{
	fclose( static_cast< _iobuf* >( stdout ) );

	FreeConsole( );

	if ( const auto console_window = GetConsoleWindow( ); console_window )
		PostMessageW( console_window, WM_CLOSE, 0U, 0L );
}
