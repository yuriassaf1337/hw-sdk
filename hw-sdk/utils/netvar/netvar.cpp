#include "netvar.h"

// sdk::recv_var_proxy_fn netvar::find_proxy_table( sdk::recv_table* table, const char* var, sdk::recv_var_proxy_fn function )
//{
//	return sdk::recv_var_proxy_fn( );
// }
//
// sdk::recv_var_proxy_fn netvar::change_proxy( const char* table, const char* var, sdk::recv_var_proxy_fn function )
//{
//	return sdk::recv_var_proxy_fn( );
// }

std::uintptr_t netvar::get_offset( sdk::recv_table* table, const char* var )
{
	for ( std::size_t i = 0; i < table->props; i++ ) {
		auto current_prop = table->props_ptr[ i ];

		if ( HASH( var ) == HASH( current_prop.var_name ) )
			return current_prop.offset;

		if ( auto data_table = current_prop.data_table ) {
			std::uintptr_t offset = get_offset( data_table, var );

			if ( offset )
				return offset + current_prop.offset;
		}
	}

	return std::uintptr_t( );
}

std::uintptr_t netvar::get_table( const char* table, const char* var )
{
	auto classes = g_interfaces.client->get_all_classes( );

	for ( auto current_table = classes; current_table; current_table = current_table->next ) {
		if ( HASH( table ) == HASH( current_table->network_name ) )
			return get_offset( current_table->recv_table, var );
	}

	return std::uintptr_t( );
}
