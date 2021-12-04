#pragma once
#include "../../dependencies/mocking_bird/mocking_bird.h"
#include "../../globals/includes/includes.h"
#include "../helpers/function_enforce/function_enforce.h"
#include "address/address.h"

namespace modules
{
	class impl
	{
	public:
		impl( ) = default;
		explicit impl( const char* mod_name )
		{
			module_name   = mod_name;
			module_handle = get_module_handle_safe( mod_name );
		};

		address pattern_scan( const char* sig );

		template< class T >
		T find_interface( const char* interface_name );

		constexpr HMODULE get_module_handle_safe( const char* name );

	private:
		HMODULE module_handle{ };

		const char* module_name{ };

		std::uintptr_t find_pattern( std::uint8_t* region_start, std::uintptr_t region_size, const char* pattern );

		std::vector< int > pattern_to_bytes( const char* pattern );
	};
} // namespace modules

// global modules

inline modules::impl g_client_dll       = modules::impl( CLIENT_DLL );
inline modules::impl g_engine_dll       = modules::impl( ENGINE_DLL );
inline modules::impl g_localize_dll     = modules::impl( LOCALIZE_DLL );
inline modules::impl g_shaderapidx9_dll = modules::impl( SHADERAPIDX9_DLL );
inline modules::impl g_vstdlib_dll      = modules::impl( VSTDLIB_DLL );

#include "modules.inl"
