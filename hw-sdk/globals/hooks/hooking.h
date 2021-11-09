#pragma once

#include <iostream>

#include "../../dependencies/minhook/include/MinHook.h"
#include "../../utils/console/console.h"

template< class T >
class hook_helper
{
private:
	void* source;
	void* original;

public:
	template< typename S, typename D >
	void create( S source, D destination, const char* name = _( "undefined" ) )
	{
		if ( MH_CreateHook( reinterpret_cast< void* >( source ), reinterpret_cast< void* >( destination ), &original ) != MH_OK )
			console::format_log< console::log_level::FATAL >( _( "failed to hook {} [{} -> {}]" ), name, reinterpret_cast< void* >( source ),
			                                                  reinterpret_cast< void* >( destination ) );

		MH_EnableHook( reinterpret_cast< void* >( source ) );

		this->source = source;

		console::format_log< console::log_level::NORMAL >( _( "hooked {} [{} -> {}]" ), name, reinterpret_cast< void* >( source ),
		                                                   reinterpret_cast< void* >( destination ) );
	}

	void disable( )
	{
		MH_DisableHook( source );
	}

	template< typename R, typename... A >
	R call_original( A... arguments )
	{
		return reinterpret_cast< T* >( original )( arguments... );
	}

	T* get_original( )
	{
		return reinterpret_cast< T* >( original );
	};
};

namespace hooks
{
	void init( );
	void unload( );
} // namespace hooks
