#pragma once

#include "../../../globals/ctx/ctx.h"
#include "../../../globals/includes/includes.h"

namespace movement
{
	struct impl {
		struct pre_prediction {
			void think( );
		} pre_prediction;
		struct post_prediction {
			void think( );
		} post_prediction;
		void bhop( );
	};
} // namespace movement

inline movement::impl g_movement;
