#pragma once
#include "../structs/datamap.h"
#include <basetsd.h>
#include <unordered_map>

namespace sdk::props
{
	using props_type = std::unordered_map< uint32_t, std::unordered_map< uint32_t, std::ptrdiff_t > >;

	inline props_type map;

	void init( );

	UINT32 find_in_datamap( sdk::datamap_t* map, UINT32 name );
} // namespace sdk::props
