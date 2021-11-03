#ifndef CONSOLE_H
#define CONSOLE_H

// deps
#include "../../dependencies/tinyformat.h"
#include "../../dependencies/xor/xor.h"

#include <Windows.h>
#include <consoleapi.h>
#include <consoleapi2.h>
#include <consoleapi3.h>
#include <stdio.h>
#include <windef.h>

namespace console
{
	bool init( );

	void unload( );
} // namespace console

#endif
