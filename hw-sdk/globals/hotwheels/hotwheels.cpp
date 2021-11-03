#include "hotwheels.h"

DWORD WINAPI hotwheels::init( void* module_handle )
{
	handle = static_cast< HMODULE >( module_handle );
	window = LI_FN( FindWindowA )( x( "Valve001" ), nullptr );

	return 0;
}
