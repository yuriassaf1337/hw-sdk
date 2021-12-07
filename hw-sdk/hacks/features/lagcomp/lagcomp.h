#pragma once
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

	public:
		record* heap_records[ 65 ];

		bool is_valid( );
		void update( );
	};
} // namespace lagcomp

inline lagcomp::impl g_lagcomp;
