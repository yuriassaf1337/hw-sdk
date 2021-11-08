#pragma once
//	https://www.unknowncheats.me/forum/counterstrike-global-offensive/249206-datamap-variable-grabber.html
#include "../../../globals/macros/macros.h"
#include <cstdint>

namespace sdk
{
	namespace enums
	{
		enum e_td_type
		{
			td_offset_normal = 0,
			td_offset_packet = 1,
			td_offset_count
		};
	} // namespace enums

	struct type_description_t {
		std::int32_t field_type;
		char* field_name;
		int field_offset[ sdk::enums::e_td_type::td_offset_count ];
		std::int16_t field_size;
		std::int16_t flags;
		PAD( 12 );
		datamap_t* td;
		PAD( 24 );
	};

	struct datamap_t {
		type_description_t* data_description;
		int data_fields_count;
		char const* data_class_name;
		datamap_t* data_base_map;
		bool chains_validated;
		bool packed_offsets_computed;
		int packed_size;
	};
} // namespace sdk
