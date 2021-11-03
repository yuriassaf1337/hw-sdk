#include "helpers/primitive_definitions/primitives.h"
#include <cstdint>
#include <thread>

#ifndef UTILS_H
#	define UTILS_H
namespace utils
{
	void sleep( std::uint32_t time )
	{
		std::this_thread::sleep_for( chr::milliseconds( time ) );
	}
} // namespace utils
#endif // ! UTILS_HPP
