#include "../includes/includes.h"

#ifndef HOTWHEELS_H
#	define HOTWHEELS_H

// cheat initialization method

namespace hotwheels
{
	inline HMODULE handle{ };
	inline HWND window{ };

	DWORD WINAPI init( void* module_handle );
}; // namespace hotwheels
#endif
