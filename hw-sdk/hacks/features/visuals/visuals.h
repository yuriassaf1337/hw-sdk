#pragma once

#include "../../../game/sdk/classes/c_cs_player.h"
#include "../../../game/sdk/classes/i_collideable.h"
#include "../../../game/sdk/include.h"
#include "../../../globals/includes/includes.h"
#include "../../../utils/entity_list/entity_list.h"
#include "../../../utils/renderer/renderer.h"

#include <deque>

namespace visuals
{
	// Welcome to the great wall of esp. I have designed this as a nice object oriented way to
	// Do esp or visuals. If you want to create a new object follow the esp_box struct exactly.
	// Make a render function, all helper functions must be private! If they use rgfl matrix or
	// Use any function that relies i_collidable update them in paint like I do with esp_box rgfl.
	// This is an issue with CS:GO and multicore rendering and I plan on having more than 2 FPS.

	struct esp_box {
	private:
		math::vec4 calculate_box( sdk::c_cs_player* player );

	public:
		void render( sdk::c_cs_player* owner );

		bool outline;
		bool cornered;

		color _color;

		math::vec3 mins;
		math::vec3 maxs;

		math::matrix_3x4 rgfl;
	};

	struct esp_object {
	public:
		esp_object( ){ };
		esp_object( sdk::c_cs_player* owner ) : owner( owner ){ };

		sdk::c_cs_player* owner;

		esp_box box;
	};

	struct impl {
	private:
		void update_box( esp_object& object );

	public:
		std::array< esp_object, 65 > esp_objects;

		void update( );
		void render( );
	};
} // namespace visuals

inline visuals::impl g_visuals;
