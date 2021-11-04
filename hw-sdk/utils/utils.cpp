#include "utils.h"

void utils::sleep( std::uint32_t time )
{
	::std::this_thread::sleep_for( ::chr::milliseconds( time ) );
}

BOOL utils::cheat_create_thread( DWORD WINAPI function( void* ), void* param )
{
	HANDLE handle = LI_FN( CreateThread )( nullptr, 0, function, param, 0, nullptr );
	if ( !handle )
		return FALSE;

	LI_FN( CloseHandle )( handle );

	return TRUE;
}
