#include "globals/includes/includes.h"

// info; all sdk stuff must be placed in sdk:: namespace.

unsigned long cheat_init( void* args )
{
	while ( !GetModuleHandleA( "serverbrowser.dll" ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 30 ) );

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
