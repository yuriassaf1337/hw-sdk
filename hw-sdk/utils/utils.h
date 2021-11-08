#pragma once

#include "../dependencies/lazy_importer/lazy_importer.h"
#include "helpers/primitive_definitions/primitives.h"
#include "modules/address/address.h"

#include <Windows.h>
#include <cstdint>
#include <thread>

namespace utils
{
	void sleep( std::uint32_t time );
	BOOL cheat_create_thread( DWORD WINAPI function( void* ), void* param );
} // namespace utils
