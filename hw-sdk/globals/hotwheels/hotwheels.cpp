#include "hotwheels.h"
#include "../csgo.h"

DWORD WINAPI hotwheels::init( void* module_handle )
{
	handle = static_cast< HMODULE >( module_handle );
	window = LI_FN( FindWindowA )( x( "Valve001" ), nullptr );

	return 0;
}

DWORD WINAPI hotwheels::unload( DWORD exit_code )
{
	LI_FN( FreeLibraryAndExitThread )( handle, exit_code );

	return exit_code;
}
