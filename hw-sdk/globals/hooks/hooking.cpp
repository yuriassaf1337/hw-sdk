#include "hooking.h"

#include "present/present.h"
#include "wndproc/wndproc.h"

bool hooks::init( )
{
	if ( MH_Initialize( ) != MH_OK )
		return false;

	wndproc_hook::init( );
	present_hook::init( );

	return true;
}

void hooks::unload( )
{
	wndproc_hook::unload( );
	present_hook::unload( );

	MH_Uninitialize( );
}
