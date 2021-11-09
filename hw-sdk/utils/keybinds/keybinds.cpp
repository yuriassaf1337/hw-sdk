#include "keybinds.h"

void keybinds::add_keybind( std::size_t key, std::function< void( bool ) > callback )	
{
	list.push_back( { key, callback } );
}

void keybinds::remove_keybind( std::size_t key )
{
	for ( auto iterator = list.begin( ); iterator != list.end( ); iterator++ ) 
	{
		if ( iterator->key = key )
			list.erase( iterator );
	}
}

void keybinds::handle_input( UINT message, WPARAM parameter )
{
	switch ( message ) {
	case WM_KEYUP: {
		for ( auto iterator = list.begin( ); iterator != list.end( ); iterator++ ) 
		{
			if ( iterator->key == parameter )
				iterator->callback( false );
		}

		break;
	}

	case WM_KEYDOWN: {
		for ( auto iterator = list.begin( ); iterator != list.end( ); iterator++ ) 
		{
			if ( iterator->key == parameter )
				iterator->callback( true );
		}

		break;
	}
	}
}