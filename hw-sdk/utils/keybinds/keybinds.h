#pragma once

#include <Windows.h>
#include <deque>
#include <functional>

class keybind
{
public:
	std::size_t key;
	std::function< void( bool ) > callback;
};

namespace keybinds
{
	inline std::deque< keybind > list;

	void add_keybind( std::size_t key, std::function< void( bool ) > callback );

	void remove_keybind( std::size_t key );

	void handle_input( UINT message, WPARAM parameter );
} // namespace keybinds
