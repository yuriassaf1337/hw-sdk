#include "console.h"
#include "../../dependencies/mocking_bird/mocking_bird.h"

bool console::init( )
{
#ifdef CONSOLE_ENABLED

	MOCKING_TRY;

	MOCK AllocConsole( );

	AttachConsole( ATTACH_PARENT_PROCESS );

	if ( freopen_s( reinterpret_cast< _iobuf** >( stdout ), x( "CONOUT$" ), x( "w" ), stdout ) != 0 )
		return false;

	if ( !SetConsoleTitleA( x( "[console] hotwheels-v3" ) ) )
		return false;

	HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE );
	MOCK handle;

	DWORD mode = 0;
	GetConsoleMode( handle, &mode );

	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	return SetConsoleMode( handle, mode );

	MOCKING_CATCH( return false );
#endif
	return true;
}

void console::unload( )
{
#ifdef CONSOLE_ENABLED

	fclose( static_cast< _iobuf* >( stdout ) );

	FreeConsole( );

	if ( const auto console_window = GetConsoleWindow( ); console_window )
		PostMessageW( console_window, WM_CLOSE, 0U, 0L );
#endif
}
