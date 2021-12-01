#pragma once

#include "../../../globals/ctx/ctx.h"
#include "../../../globals/includes/includes.h"

namespace movement
{
	enum edgebug_type : int
	{
		standing = 0,
		ducking,
		onetick
	};

	struct impl {
		struct pre_prediction {
			void think( );
		} pre_prediction;
		struct post_prediction {
			void think( );
		} post_prediction;

		struct edgebug_t {
			bool success;
			bool failed;
			int ticks;
			int tickcount;
			float moused_x;
			static movement::edgebug_type mode;

			edgebug_t ( )
			{
				memset(this, false, sizeof this);
			}
		};

		struct longjump_t {
			bool standalone = false, start_timer = false;
			int timestamp;

			longjump_t ( )
			{
				memset(this, false, sizeof this);
			}
		};

		void bhop( );

		void edgebug( );
	};
} // namespace movement

inline movement::impl g_movement;
