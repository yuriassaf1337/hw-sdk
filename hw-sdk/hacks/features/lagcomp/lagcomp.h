#pragma once

#include "../../../game/sdk/classes/c_cs_player.h"
#include "../../../globals/includes/includes.h"

namespace lagcomp
{
	struct record {
	public:
		record( ) = default;

		bool valid;
		float simulation_time;

		math::vec3 abs_origin;
		math::vec3 eye_position;
		math::vec3 /*hitboxes idfk how many*/ hitboxes[ 20 ];

		sdk::c_cs_player* player;
	};

	struct impl {
	private:
		// You should kill yourself NOW!
		// [ 1-64 ] is the range of possible player indexes.
		int heap_iterator[ 65 ];
		float lerp_time( );
		bool is_valid( record heap_record );

	public:
		record* heap_records[ 65 ];

		void update( );

		void backtrack_player( record* heap_record );
		void backtrack_player( sdk::c_cs_player* player );
	};
} // namespace lagcomp

inline lagcomp::impl g_lagcomp;
