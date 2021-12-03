#pragma once
#include "../../../globals/includes/includes.h"
#include "../enums/field_type.h"

struct data_map;

namespace sdk
{
	struct type_description {
	public:
		field_type type;
		const char* name;
		int offset[ 0x2 ]; // Honestly there's a better way to do this just ignore it though...
		unsigned short size;
		short flags;
		PAD( 0xC );
		data_map* type_description;
		PAD( 0x18 );
	};
} // namespace sdk
