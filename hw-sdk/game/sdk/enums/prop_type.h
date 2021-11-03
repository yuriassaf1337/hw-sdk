#include <cstdint>
#ifndef PROP_TYPE_H
#	define PROP_TYPE_H

namespace sdk::enums
{
	enum class prop_type : std::uint32_t
	{
		INT = 0,
		FLOAT,
		VECTOR,
		VECTOR2D,
		STRING,
		ARRAY,
		DATATABLE,
		INT64,
		SENDPROPTYPEMAX
	};
} // namespace sdk::enums

#endif
