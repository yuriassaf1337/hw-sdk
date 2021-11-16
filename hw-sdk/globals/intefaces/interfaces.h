#pragma once

#include <d3dx9.h>
#include <iostream>
#include <string.h>

#include "../../game/sdk/classes/i_client_dll.h"
#include "../../game/sdk/classes/i_global_vars.h"
#include "../../game/sdk/classes/iv_engine_client.h"
#include "../../utils/utils.h"
#include "../../utils/vfunc/vfunc.h"
#include "../macros/macros.h"

namespace sdk
{
	struct interfaces {
		IDirect3DDevice9* device;
		sdk::iv_engine_client* engine;
		sdk::i_client_dll* client;
		sdk::i_global_vars* globals;
		bool init( );
	};
} // namespace sdk

inline sdk::interfaces g_interfaces;
