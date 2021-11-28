#pragma once

#include <d3dx9.h>
#include <iostream>
#include <string.h>

#include "../../game/sdk/classes/c_client_state.h"
#include "../../game/sdk/classes/c_input.h"
#include "../../game/sdk/classes/i_client_dll.h"
#include "../../game/sdk/classes/i_client_entity_list.h"
#include "../../game/sdk/classes/i_cvar.h"
#include "../../game/sdk/classes/i_global_vars.h"
#include "../../game/sdk/classes/i_prediction.h"
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
		sdk::c_input* input;
		sdk::i_client_entity_list* entity_list;
		sdk::i_game_movement* game_movement;
		sdk::i_prediction* prediction;
		sdk::i_move_helper* move_helper;
		sdk::i_cvar* convar;
		sdk::c_client_state* client_state;

		bool init( );
	};
} // namespace sdk

inline sdk::interfaces g_interfaces;
