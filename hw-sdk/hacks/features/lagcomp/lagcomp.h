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
		std::array< int, 24 > heap_iterator;
		std::array< record*, 24 > heap_records;

	public:
		void update( );
	};
} // namespace lagcomp

inline lagcomp::impl g_lagcomp;
