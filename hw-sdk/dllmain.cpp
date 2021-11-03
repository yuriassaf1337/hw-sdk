#include "globals/includes/includes.h"

// info:
//		all sdk stuff must be placed in sdk namespace.
//		enums used in interfaces and other stuff is in sdk::enums.

// initial todo's:
//		add lazy importer.

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved )
{
	switch ( ul_reason_for_call ) {
	case DLL_PROCESS_ATTACH:

		// return hotwheels.cheat_init( hotwheels.init );
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
};
