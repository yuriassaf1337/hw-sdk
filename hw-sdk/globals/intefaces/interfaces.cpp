#include <string.h>

#include "../../utils/modules/modules.h"
#include "interfaces.h"

bool interfaces::init( )
{
	MOCKING_TRY
	device = **reinterpret_cast< IDirect3DDevice9*** >( g_shaderapidx9_dll.pattern_scan( _( "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) ) + 0x1 );
	if ( !device )
		return false;

	MOCKING_CATCH( return false );

	return true;
}

void interfaces::unload( ) { }
