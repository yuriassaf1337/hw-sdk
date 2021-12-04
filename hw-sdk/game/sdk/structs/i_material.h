#pragma once
#include "../../../utils/math/types/vector.h"
#include "../../../utils/vfunc/vfunc.h"
#include "../enums/material_var_flags.h"

namespace sdk
{
	struct i_material_var {
		void set_vector( const math::vec3& vec )
		{
			virtual_func::call< void, const math::vec3& >( this, 11, vec );
		}

		void set_component_value( float val, float comp )
		{
			virtual_func::call< void, float, float >( this, 26, val, comp );
		}
	};

	struct i_material {
		virtual const char* get_name( )               = 0;
		virtual const char* get_texture_group_name( ) = 0;

		sdk::i_material_var* find_var( const char* name, bool* found = nullptr, bool complain = true )
		{
			return virtual_func::call< sdk::i_material_var*, const char*, bool*, bool >( this, 11, name, found, complain );
		}

		void set_material_var_flag( sdk::material_var_flags flag, bool on )
		{
			virtual_func::call< void, sdk::material_var_flags, bool >( this, 29, flag, on );
		}
	};
} // namespace sdk
