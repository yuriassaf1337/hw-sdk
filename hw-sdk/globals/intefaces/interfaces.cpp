#include <string.h>

#include "../../utils/modules/modules.h"
#include "interfaces.h"

bool interfaces::init( )
{
	MOCKING_TRY

	device = **g_shaderapidx9_dll.pattern_scan( _( "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) ).add( 0x1 ).as< IDirect3DDevice9*** >( );

	engine = g_engine_dll.find_interface< sdk::iv_engine_client* >( _( "VEngineClient014" ) );

	client = g_client_dll.find_interface< sdk::chl_client* >( _("VClient018"));

	MOCKING_CATCH( return false );

	return true;
}

void interfaces::unload( ) { }
