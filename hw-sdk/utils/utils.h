#pragma once

#include <Windows.h>
#include <cstdint>
#include <iostream>
#include <thread>

class interface_node
{
public:
	void* ( *get )( );
	const char* name;
	interface_node* next;
};

namespace utils
{
	void sleep( std::uint32_t time );

	BOOL cheat_create_thread( DWORD WINAPI function( void* ), void* param );
} // namespace utils
