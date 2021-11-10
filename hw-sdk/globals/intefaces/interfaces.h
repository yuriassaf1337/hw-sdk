#pragma once

#include <d3dx9.h>
#include <iostream>
#include <string.h>

#include "../../utils/utils.h"
#include "../macros/macros.h"

namespace interfaces
{
	inline IDirect3DDevice9* device;

	bool init( );
	void unload( ); // unused...
} // namespace interfaces
