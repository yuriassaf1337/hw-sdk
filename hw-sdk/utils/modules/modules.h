#pragma once
#include "../../globals/includes/includes.h"

namespace modules
{
	class impl
	{
	public:
		impl( ) = default;
		impl( const char* mod_name )
		{
			module_handle = LI_FN( GetModuleHandle )( mod_name );
		};

		address pattern_scan( const char* sig ){

		};

	private:
		HMODULE module_handle{ };
	};
} // namespace modules

// global modules
inline modules::impl g_client_dll = modules::impl( CLIENT_DLL );
