#pragma once

#include "../../../game/sdk/classes/c_cs_player.h"
#include "../../../globals/includes/includes.h"

namespace lagcomp
{
	struct record {
	public:
		record( ) = default;

		bool valid;
		math::vec3 origin;
		float simulation_time;
	};

	struct impl {
	private:
		// [ 1-64 ] is the range of possible player indexes.
		int heap_iterator[ 65 ];
		float lerp_time( );
		bool is_valid( record heap_record );

	public:
		record* heap_records[ 65 ];

		void update( );
		void backtrack_player( record heap_record );
	};
} // namespace lagcomp

inline lagcomp::impl g_lagcomp;
