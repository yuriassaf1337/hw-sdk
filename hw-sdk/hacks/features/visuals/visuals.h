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

	enum class esp_title_location : int
	{
		TITLE_TOP = 0,
		TITLE_LEFT,
		TITLE_BOTTOM,
		TITLE_RIGHT
	};

	struct esp_title {
	public:
		void render( math::box box );

		std::string m_text{ };

		color m_color{ };

		esp_title_location m_location{ };
	};

	struct esp_box {
	private:
		math::box calculate_box( sdk::c_cs_player* player );

	public:
		void render( sdk::c_cs_player* owner );

		bool m_outline[ 2 ]{ }; // 0 = outside, 1 = inside.
		bool m_cornered{ };

		color m_color{ };

		math::vec3 m_mins{ };
		math::vec3 m_maxs{ };

		math::matrix_3x4 m_rgfl{ };

		bool m_draw{ };

		std::deque< esp_title > m_titles{ };
	};

	struct esp_object {
	public:
		esp_object( ) = default;
		esp_object( sdk::c_cs_player* owner ) : m_owner( owner ){ };

		sdk::c_cs_player* m_owner{ };

		esp_box m_box{ };
	};

	struct impl {
	private:
		void update_box( esp_object& object );

	public:
		std::array< esp_object, 65 > esp_objects{ };

		void update( );
		void render( );

		bool HEYIMDRAWINHERE{ }; // dream please don't remove drain gang $$$$$$
	};
} // namespace visuals

inline visuals::impl g_visuals;
