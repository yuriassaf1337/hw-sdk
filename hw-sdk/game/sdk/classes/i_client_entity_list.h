#pragma once

#include "../../../dependencies/hash/hash.h"
#include "../../../dependencies/xor/xor.h"
#include "../../../globals/macros/macros.h"
#include "../../../utils/math/types/vector.h"

#include "../classes/c_handle.h"
#include "i_client_entity.h"

namespace sdk
{
	struct i_client_entity_list {
		virtual i_client_networkable get_client_networkable( int index )                        = 0;
		virtual i_client_networkable get_client_networkable_from_handle( c_base_handle handle ) = 0;

		virtual i_client_unknown get_client_unknown_from_handle( c_base_handle handle ) = 0;

		virtual i_client_entity* get_client_entity( int index )                        = 0;
		virtual i_client_entity* get_client_entity_from_handle( c_base_handle handle ) = 0;

		virtual int number_of_entities( bool include_non_networkable ) = 0;
		virtual int get_highest_entity_index( )                        = 0;
	};
} // namespace sdk
