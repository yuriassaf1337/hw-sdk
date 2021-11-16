#pragma once
#include "../../../game/sdk/structs/color.h"
#include "../../../utils/console/console.h"
#include <cstdint>
#include <unordered_map>

namespace configs
{
	enum class variable_type_t : std::int32_t
	{
		TYPE_BOOL = 0,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_COLOR,
		TYPE_MAX
	};

	struct variable_t {
	public:
		std::uint32_t hash{ };
		configs::variable_type_t variable_type{ };

		// values
		bool as_bool{ };
		int as_int{ };
		float as_float{ };
		color as_color{ };
		// ctors
		//(clang doesnt let me format this right lol)
		explicit variable_t( const int value, std::uint32_t hashed ) : hash( hashed ), as_int( value ), variable_type( variable_type_t::TYPE_INT ){ };

		explicit variable_t( const bool value, std::uint32_t hashed )
			: hash( hashed ), as_bool( value ), variable_type( variable_type_t::TYPE_BOOL ){ };

		explicit variable_t( const float value, std::uint32_t hashed )
			: hash( hashed ), as_float( value ), variable_type( variable_type_t::TYPE_FLOAT ){ };

		explicit variable_t( const color value, std::uint32_t hashed )
			: hash( hashed ), as_color( value ), variable_type( variable_type_t::TYPE_COLOR ){ };
	};

	struct impl {
	public:
		std::unordered_map< std::uint32_t, configs::variable_t > variable_map;

		template< typename T >
		static T& get( std::uint32_t hash )
		{
			const auto value = variable_map.find( hash );

			if ( !value._Ptr )
				return *( T* )nullptr;

			switch ( value._Ptr->_Myval.second.variable_type ) {
			case variable_type_t::TYPE_BOOL:
				return *( T* )&value._Ptr->_Myval.second.bvalue;
			case variable_type_t::TYPE_INT:
				return *( T* )&value._Ptr->_Myval.second.ivalue;
			case variable_type_t::TYPE_FLOAT:
				return *( T* )&value._Ptr->_Myval.second.fvalue;
			case variable_type_t::TYPE_COLOR:
				return *( T* )&value._Ptr->_Myval.second.cvalue;
			case variable_type_t::TYPE_MAX:
				return *( T* )nullptr;
			}

			console::print< console::log_level::FATAL >( "Config '{}' failed - [ hash {} ]", __func__, hash );

			return nullptr;
		}
	};
} // namespace configs

inline configs::impl g_cfg;
