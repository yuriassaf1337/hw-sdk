#include "hotwheels.h"
#include "../../dependencies/audio/kyu/loaded.h"
#include "../../dependencies/audio/peter_griffin/loaded.h"
#include "../../dependencies/audio/soilder/loaded.h"
#include "../../utils/helpers/function_enforce/function_enforce.h"
#include "../../utils/keybinds/keybinds.h"
#include "../csgo.h"
#include "../hooks/hooking.h"
#include "../interfaces/interfaces.h"
#include <sapi.h>

DWORD WINAPI hotwheels::init( void* module_handle )
{
	handle = static_cast< HMODULE >( module_handle );
	while ( !( window = LI_FN( FindWindowA )( _( "Valve001" ), nullptr ) ) )
		utils::sleep( 100 );

	ENFORCE_FAILURE( g_csgo.init( ), "Failed to init csgo" );

	ENFORCE_FAILURE( g_interfaces.init( ), "Failed to init interfaces" );

	ENFORCE_FAILURE( g_hooks.init( ), "Failed to init hooks" );

	LI_FN( PlaySoundA )( reinterpret_cast< LPCSTR >( kyu::loaded ), nullptr, SND_MEMORY | SND_ASYNC );

	g_input.add_keybind( VK_DELETE, []( bool pressed ) -> void {
		HANDLE thread = LI_FN( CreateThread )( nullptr, 0, reinterpret_cast< LPTHREAD_START_ROUTINE >( unload ), nullptr, 0, nullptr );

		if ( thread )
			LI_FN( CloseHandle )( thread );
	} );

	return 0;
}

DWORD WINAPI hotwheels::unload( DWORD exit_code )
{
	MOCKING_TRY

	g_hooks.unload( );

	g_csgo.unload( );

	LI_FN( FreeLibraryAndExitThread )( handle, exit_code );

	MOCKING_CATCH( return 1 );

	return exit_code;
}
