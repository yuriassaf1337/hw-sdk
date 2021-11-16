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
		impl( const char* mod_name ) : module_name{ mod_name }
		{
			module_handle = this->get_module_handle_safe( mod_name );
		};

		address pattern_scan( const char* sig )
		{
			if ( !module_handle )
				console::print< console::log_level::WARNING >( _( "Failed to get handle - [ {} ]" ), module_name );

			const auto module_address   = reinterpret_cast< std::uint8_t* >( module_handle );
			const auto dos_header       = reinterpret_cast< PIMAGE_DOS_HEADER >( module_handle );
			const auto nt_headers       = reinterpret_cast< PIMAGE_NT_HEADERS >( module_address + dos_header->e_lfanew );
			const std::uintptr_t offset = find_pattern( module_address, nt_headers->OptionalHeader.SizeOfImage, sig );

			if ( offset )
				console::print< console::log_level::NORMAL >( _( "Found signature - [ {} -> {} ]" ), module_name, sig );

			return offset;
		};

		template< class T >
		T find_interface( const char* interface_name )
		{
			auto get_jmp_address = []( std::uintptr_t address ) -> std::uintptr_t {
				auto jmp_relative = *reinterpret_cast< std::uintptr_t* >( address + 0x1 );

				address += 0x5;
				address += jmp_relative;

				return address;
			};

			auto pointer = reinterpret_cast< std::uintptr_t >( LI_FN( GetProcAddress )( module_handle, _( "CreateInterface" ) ) );

			while ( *reinterpret_cast< std::uint8_t* >( pointer ) != 0xE9 )
				++pointer;

			pointer = get_jmp_address( pointer );

			while ( *reinterpret_cast< std::uint16_t* >( pointer ) != 0x358B )
				++pointer;

			auto node = **reinterpret_cast< interface_node*** >( pointer + 0x2 );

			char buffer_name[ 128 ]{ };

			while ( node ) {
				std::size_t size;

				for ( size = 0; node->name[ size ] != '\0'; ++size )
					buffer_name[ size ] = node->name[ size ];

				buffer_name[ size ] = '\0';

				if ( HASH( buffer_name ) == HASH( interface_name ) )
					break;

				node = node->next;
			}

			if ( !node ) {
				console::print< console::log_level::FATAL >( _( "Find interface node failed [ interface = {} | module = {} ]" ), interface_name,
				                                             module_name );
				return nullptr;
			}

			void* node_address = node->get( );

			if ( !node_address ) {
				console::print< console::log_level::FATAL >( _( "Find interface node->get( ) failed [ interface = {} | module = {} ]" ),
				                                             interface_name, module_name );
				return nullptr;
			}
			return reinterpret_cast< T >( node_address );
		}

	private:
		HMODULE module_handle{ };
		const char* module_name{ };

		std::uintptr_t find_pattern( std::uint8_t* region_start, std::uintptr_t region_size, const char* pattern )
		{
			std::vector< int > vec_bytes = pattern_to_bytes( pattern );
			for ( unsigned long i = 0UL; i < region_size - vec_bytes.size( ); ++i ) {
				bool byte_found = true;
				for ( unsigned long s = 0UL; s < vec_bytes.size( ); ++s ) {
					if ( region_start[ i + s ] != vec_bytes[ s ] && vec_bytes[ s ] != -1 ) {
						byte_found = false;
						break;
					}
				}

				if ( byte_found )
					return reinterpret_cast< std::uintptr_t >( &region_start[ i ] );
			}
			console::print< console::log_level::FATAL >( _( "Find pattern failed - [ {} ]" ), pattern );
			return 0U;
		}
		std::vector< int > pattern_to_bytes( const char* pattern )
		{
			std::vector< int > vec_bytes = { };
			char* start                  = const_cast< char* >( pattern );
			char* end                    = start + strlen( pattern );

			for ( char* current = start; current < end; ++current ) {
				if ( *current == '?' ) {
					++current;

					if ( *current == '?' )
						++current;

					vec_bytes.push_back( -1 );
				} else
					// convert byte to hex
					vec_bytes.push_back( strtoul( current, &current, 16 ) );
			}

			return vec_bytes;
		}
		constexpr HMODULE get_module_handle_safe( const char* name )
		{
			HMODULE return_module{ };

			while ( !return_module ) {
				return_module = LI_FN( GetModuleHandleA )( name );
				utils::sleep( 1 );
			}

			return return_module;
		}
	};
} // namespace modules

// global modules

inline modules::impl g_client_dll       = modules::impl( CLIENT_DLL );
inline modules::impl g_engine_dll       = modules::impl( ENGINE_DLL );
inline modules::impl g_localize_dll     = modules::impl( LOCALIZE_DLL );
inline modules::impl g_shaderapidx9_dll = modules::impl( SHADERAPIDX9_DLL );
