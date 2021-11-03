#include "../includes/includes.h"

#ifndef HOTWHEELS_H
#	define HOTWHEELS_H

// cheat initialization method

class c_hotwheels
{
public:
	HMODULE handle{ };
	HWND window{ };

	DWORD WINAPI init( void* module_handle );
};
inline c_hotwheels hotwheels{ };
#endif
