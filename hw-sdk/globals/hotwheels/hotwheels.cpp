#include "hotwheels.h"
#include "../../utils/helpers/function_enforce/function_enforce.h"
#include "../csgo.h"


//remove later
#include "../hooks/present/present.h"
#include "../intefaces/interfaces.h"

DWORD WINAPI hotwheels::init( void* module_handle )
{
	handle = static_cast< HMODULE >( module_handle );
	window = LI_FN( FindWindowA )( _( "Valve001" ), nullptr );

	ENFORCE_FAILURE( g_csgo.init( ), "failed to init csgo" );

	interfaces::init();
	
	present_hook::init();

	return 0;
}

DWORD WINAPI hotwheels::unload( DWORD exit_code )
{
	LI_FN( FreeLibraryAndExitThread )( handle, exit_code );

	return exit_code;
}
