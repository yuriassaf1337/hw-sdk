#pragma once

#include "../../globals/includes/includes.h"

#include "../../game/sdk/classes/c_cs_player.h"
#include "../../game/sdk/classes/i_prediction.h"

namespace prediction
{
	struct impl {
		// starts prediction and sets all global variables to predict next tick
		void start( sdk::c_base_player* entity, sdk::c_user_cmd* command );
		// resets all global variables to current tick, doesnt restore predicted values
		void end( sdk::c_base_player* entity, sdk::c_user_cmd* command );
		// updates prediction incase of fps lower then tickrate
		void update( );
		// resets everything and returns to non predicted tick
		void reset( );

	private:
		void post_think( );
	};
} // namespace prediction

inline prediction::impl g_prediction;
