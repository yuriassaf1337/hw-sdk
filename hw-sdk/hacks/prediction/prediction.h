#pragma once

#include "../../globals/includes/includes.h"

#include "../../game/sdk/classes/i_prediction.h"

namespace prediction
{
	struct impl {
		// starts prediction and sets all global variables to predict next tick
		void start( );
		// resets all global variables to current tick, doesnt restore predicted values
		void end( );
		// updates prediction incase of fps lower then tickrate
		void update( );
		// resets everything and returns to non predicted tick
		void reset( );

	private:
		void post_think( );
	};
} // namespace prediction

inline prediction::impl g_prediction;
