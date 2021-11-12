#include <string.h>

#include "../../utils/modules/modules.h"
#include "interfaces.h"

bool sdk::interfaces::init( )
{
	MOCKING_TRY

	device = **g_shaderapidx9_dll.pattern_scan( _( "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) ).add( 0x1 ).as< IDirect3DDevice9*** >( );

	engine = g_engine_dll.find_interface< sdk::iv_engine_client* >( VENGINE_CLIENT_INTERFACE_VERSION );

	client = g_client_dll.find_interface< sdk::i_client_dll* >( VCLIENT_INTERFACE_VERSION );

	MOCKING_CATCH( return false );

	console::print< console::log_level::SUCCESS >( _( "initialized interfaces" ) );

	return true;
}
