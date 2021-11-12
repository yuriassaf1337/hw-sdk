#include "hooking.h"

#include "../../dependencies/mocking_bird/mocking_bird.h"
#include "create_move/create_move.h"
#include "present/present.h"
#include "wndproc/wndproc.h"

bool hooks::init( )
{
	MOCKING_TRY;

	if ( MH_Initialize( ) != MH_OK )
		return false;

	hooks::wndproc::init( );
	hooks::present::init( );
	hooks::create_move::init( );

	MOCKING_CATCH( return false );

	return true;
}

void hooks::unload( )
{
	hooks::wndproc::unload( );
	hooks::present::unload( );
	hooks::create_move::unload( );

	MH_Uninitialize( );
}
