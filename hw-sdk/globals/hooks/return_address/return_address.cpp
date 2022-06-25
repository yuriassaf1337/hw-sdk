#include "return_address.h"

// prevents red trust as said by liga(fake)
bool __stdcall hooks::return_address::return_address_detour( LPCSTR )
{
	return true;
}
