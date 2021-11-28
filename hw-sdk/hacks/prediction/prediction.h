#pragma once

#include "../../globals/includes/includes.h"

#include "../../game/sdk/classes/c_base_entity.h"
#include "../../game/sdk/classes/c_client_state.h"
#include "../../game/sdk/classes/i_prediction.h"

namespace prediction
{
	struct impl {
		struct backup_vars_impl {
			int tick_base;
			float current_time, frame_time;
			sdk::move_data_t move_data;
		} backup_vars;

		// gets players tickbase correctly
		int get_tick_base( sdk::c_base_player* player );
		// starts prediction and sets all global variables to predict next tick
		void start( sdk::c_base_player* player );
		// resets all global variables to current tick, doesnt restore predicted values
		void end( sdk::c_base_player* player );
		// updates prediction incase of fps lower then tickrate
		void update( );
		// resets everything and returns to non predicted tick
		void reset( );

	private:
		void pre_think( sdk::c_base_player* player );
		void post_think( sdk::c_base_player* player );
	};
} // namespace prediction

inline prediction::impl g_prediction;
