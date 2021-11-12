#include "hooking.h"

#include "create_move/create_move.h"
#include "present/present.h"
#include "wndproc/wndproc.h"

bool hooks::init( )
{
	if ( MH_Initialize( ) != MH_OK )
		return false;

	wndproc_hook::init( );
	present_hook::init( );
	create_move::init( );

	return true;
}

void hooks::unload( )
{
	wndproc_hook::unload( );
	present_hook::unload( );
	create_move::unload( );

	MH_Uninitialize( );
}
