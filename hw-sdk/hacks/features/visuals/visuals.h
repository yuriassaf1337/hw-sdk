#pragma once

#include "../../../game/sdk/classes/c_cs_player.h"
#include "../../../game/sdk/classes/i_collideable.h"
#include "../../../game/sdk/include.h"
#include "../../../globals/includes/includes.h"

namespace visuals
{
	struct esp_box {
	public:
		bool outline;
		bool cornered;

		color _color;
	};

	struct esp_object {
	public:
		esp_box box;
	};

	struct impl {
	private:
		math::vec4 calculate_box( sdk::c_cs_player* player );
		void add_box( esp_object& object );

	public:
		// Personally I feel like this is the best way to do it as if we did a shitty std::vector and used an iterator it would use too
		// Much cpu to the point where having esp in general would just be a waste. I experienced this on my TF2 cheat and had aids fps.

		std::array< esp_object, 65 > esp_objects;

		void update( );
		void render( );
	};
} // namespace visuals
