#include "hooking.h"

#include "present/present.h"
#include "wndproc/wndproc.h"

void hooks::init( )
{
	MH_Initialize( );

	wndproc_hook::init( );
	present_hook::init( );
}

void hooks::unload( )
{
	wndproc_hook::unload( );
	present_hook::unload( );

	MH_Uninitialize( );
}
