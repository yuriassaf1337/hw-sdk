#pragma once
#include "types/matrix_3x4.h"
#include "types/vector.h"
#include <corecrt_math_defines.h>

namespace math
{
	namespace util
	{
		constexpr static double pi  = M_PI;
		constexpr static float pi_f = static_cast< float >( M_PI );
	} // namespace util

	math::vec3 angle_vector( const math::vec3& angle );

	template< typename T = float >
	T& normalize_yaw( T& yaw );
} // namespace math

#include "math.inl"