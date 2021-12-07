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
		int heap_iterator[ 63 ];

	public:
		record* heap_records[ 63 ];

		bool is_valid( );
		void update( );
	};
} // namespace lagcomp

inline lagcomp::impl g_lagcomp;
