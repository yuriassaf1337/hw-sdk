#include "hotwheels.h"
#include "../../utils/helpers/function_enforce/function_enforce.h"
#include "../csgo.h"

DWORD WINAPI hotwheels::init( void* module_handle )
{
	handle = static_cast< HMODULE >( module_handle );
	window = LI_FN( FindWindowA )( x( "Valve001" ), nullptr );

	ENFORCE_FAILURE( g_csgo.init( ), "failed to init csgo" );

	return 0;
}

DWORD WINAPI hotwheels::unload( DWORD exit_code )
{
	LI_FN( FreeLibraryAndExitThread )( handle, exit_code );

	return exit_code;
}
