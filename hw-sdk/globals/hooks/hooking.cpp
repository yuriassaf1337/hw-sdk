#include "hooking.h"

#include "../../dependencies/mocking_bird/mocking_bird.h"
#include "cl_move/cl_move.h"
#include "create_move/create_move.h"
#include "end_scene/end_scene.h"
#include "wndproc/wndproc.h"

bool hooks::init( )
{
	MOCKING_TRY;

	if ( MH_Initialize( ) != MH_OK )
		return false;

	hooks::wndproc::init( );
	hooks::end_scene::init( );
	hooks::create_move::init( );
	hooks::cl_move::init( );

	MOCKING_CATCH( return false );

	return true;
}

void hooks::unload( )
{
	hooks::wndproc::unload( );
	hooks::end_scene::unload( );
	hooks::create_move::unload( );
	hooks::cl_move::unload( );

	MH_Uninitialize( );
}
