#include "../dependencies/lazy_importer/lazy_importer.h"
#include "helpers/primitive_definitions/primitives.h"
#include "modules/address/address.h"

#include <Windows.h>
#include <cstdint>
#include <thread>

#ifndef UTILS_H
#	define UTILS_H

namespace utils
{
	void sleep( std::uint32_t time );
	BOOL cheat_create_thread( DWORD WINAPI function( void* ), void* param );

	// templated functions

	template< typename T = address >
	inline T get_v_func( address thisptr, std::uint32_t idx )
	{
		return ( T )( thisptr.to< T* >( )[ idx ] );
	}

	template< typename T, std::uint32_t I, typename... VA >
	inline T call_v_func( address thisptr, VA... args )
	{
		using FN = T( __thiscall* )( unk, decltype( args )... );
		return thisptr.to< FN* >( )[ I ]( thisptr, args... );
	}

} // namespace utils
#endif // ! UTILS_HPP
