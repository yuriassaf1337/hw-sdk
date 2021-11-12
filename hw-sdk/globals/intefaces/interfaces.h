#pragma once

#include <d3dx9.h>
#include <iostream>
#include <string.h>

#include "../../game/sdk/classes/i_client_dll.h"
#include "../../game/sdk/classes/iv_engine_client.h"
#include "../../utils/utils.h"
#include "../macros/macros.h"

namespace interfaces
{
	inline IDirect3DDevice9* device;
	inline sdk::iv_engine_client* engine;
	inline sdk::i_client_dll* client;

	bool init( );
	void unload( ); // unused... // You're unused usendskid.
} // namespace interfaces
