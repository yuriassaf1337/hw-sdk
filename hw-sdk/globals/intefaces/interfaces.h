#pragma once

#include <d3dx9.h>
#include <iostream>
#include <string.h>

#include "../macros/macros.h"
#include "../../utils/utils.h"

namespace interfaces
{
	inline IDirect3DDevice9* device;

	void init();
	void unload(); //unused...
}