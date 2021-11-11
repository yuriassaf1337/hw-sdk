#include <string.h>

#include "../../utils/modules/modules.h"
#include "interfaces.h"

bool interfaces::init( )
{
	MOCKING_TRY
	device = **reinterpret_cast< IDirect3DDevice9*** >( g_shaderapidx9_dll.pattern_scan( _( "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) ) + 0x1 );

	engine = g_engine_dll.find_interface< sdk::iv_engine_client* >( _( "VEngineClient014" ) );

	MOCKING_CATCH( return false );

	return true;
}

void interfaces::unload( ) { }
