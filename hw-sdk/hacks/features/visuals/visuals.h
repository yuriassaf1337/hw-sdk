#pragma once

#include "../../../game/sdk/include.h"
#include "../../../globals/includes/includes.h"

namespace visuals
{
	struct esp_box {
	public:
		math::vec4 box_dimensions;

		bool outline;
		bool cornered;

		color _color;
	};

	struct esp_object {
	public:
	};

	struct impl {
	private:
		void add_box( esp_object& object );

	public:
		void update( );
		void render( );
	};
} // namespace visuals
