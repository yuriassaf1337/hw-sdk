#include "hotwheels.h"
#include "../../utils/helpers/function_enforce/function_enforce.h"
#include "../csgo.h"

#include "../../utils/keybinds/keybinds.h"
#include "../hooks/hooking.h"
#include "../intefaces/interfaces.h"

DWORD WINAPI hotwheels::init( void* module_handle )
{
	handle = static_cast< HMODULE >( module_handle );
	while ( !( window = LI_FN( FindWindowA )( _( "Valve001" ), nullptr ) ) )
		utils::sleep( 100 );

	ENFORCE_FAILURE( g_csgo.init( ), "Failed to init csgo" );

	ENFORCE_FAILURE( g_interfaces.init( ), "Failed to init interfaces" );

	ENFORCE_FAILURE( hooks::init( ), "Failed to init hooks" );

	while ( !g_input.is_key_pressed( VK_INSERT ) ) {
		utils::sleep( 10 );
	}

	LI_FN( CreateThread )( nullptr, 0, reinterpret_cast< LPTHREAD_START_ROUTINE >( unload ), nullptr, 0, nullptr );

	return 0;
}

DWORD WINAPI hotwheels::unload( DWORD exit_code )
{
	hooks::unload( );

	console::unload( );

	LI_FN( FreeLibraryAndExitThread )( handle, exit_code );

	return exit_code;
}
