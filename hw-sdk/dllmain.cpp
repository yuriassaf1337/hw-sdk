#include "globals/includes/includes.h"
#include "utils/console/console.h"

// info; all sdk stuff must be placed in sdk:: namespace.

unsigned long WINAPI cheat_init( void* args )
{
	while ( !GetModuleHandle( x( "serverbrowser.dll" ) ) )
		utils::sleep( 30 );

	console::init( );

	return 0;
};

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved )
{
	switch ( ul_reason_for_call ) {
	case DLL_PROCESS_ATTACH:

		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
};
