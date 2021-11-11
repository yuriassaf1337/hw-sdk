#include "utils.h"

#include "../dependencies/hash/hash.h"
#include "../dependencies/lazy_importer/lazy_importer.h"
#include "../dependencies/xor/xor.h"
#include "../globals/macros/macros.h"
#include "helpers/primitive_definitions/primitives.h"

void utils::sleep( std::uint32_t time )
{
	::std::this_thread::sleep_for( ::chr::milliseconds( time ) );
}

void* utils::find_interface( const char* interface_name, const char* module_name )
{
	auto get_jmp_address = []( std::uintptr_t address ) -> std::uintptr_t {
		auto jmp_relative = *reinterpret_cast< std::uintptr_t* >( address + 0x1 );

		address += 0x5;
		address += jmp_relative;

		return address;
	};

	auto module_handle = LI_FN( GetModuleHandleA )( module_name );
	auto pointer       = reinterpret_cast< std::uintptr_t >( LI_FN( GetProcAddress )( module_handle, _( "CreateInterface" ) ) );

	while ( *reinterpret_cast< std::uint8_t* >( pointer ) != 0xE9 )
		++pointer;

	pointer = get_jmp_address( pointer );

	while ( *reinterpret_cast< std::uint16_t* >( pointer ) != 0x358B )
		++pointer;

	auto node = **reinterpret_cast< interface_node*** >( pointer + 0x2 );

	char buffer_name[ 128 ]{ };

	while ( node ) {
		std::size_t size;

		for ( size = 0; node->name[ size ] != '\0'; ++size )
			buffer_name[ size ] = node->name[ size ];

		buffer_name[ size ] = '\0';

		if ( HASH( buffer_name ) == HASH( interface_name ) )
			break;

		node = node->next;
	}

	if ( !node )
		return nullptr;

	void* node_address = node->get( );

	if ( !node_address )
		return nullptr;

	return node_address;
}

BOOL utils::cheat_create_thread( DWORD WINAPI function( void* ), void* param )
{
	HANDLE handle = LI_FN( CreateThread )( nullptr, 0, function, param, 0, nullptr );
	if ( !handle )
		return FALSE;

	LI_FN( CloseHandle )( handle );

	return TRUE;
}
