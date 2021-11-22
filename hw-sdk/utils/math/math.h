#pragma once
#include "types/matrix_3x4.h"
#include "types/vector.h"
#include <corecrt_math_defines.h>

#undef min
#undef max

namespace math
{
	namespace util
	{
		constexpr static long double pi = M_PI;
		constexpr static float pi_f     = static_cast< float >( M_PI );
	} // namespace util

	math::vec3 angle_vector( const math::vec3& angle );

	template< typename T >
	constexpr T min( const T& t1, const T& t2 );

	template< typename T, typename... ts_ >
	constexpr T min( const T& t1, const T& t2, ts_&&... ts );

	template< typename T >
	constexpr T max( const T& t1, const T& t2 );

	template< typename T, typename... ts_ >
	constexpr T max( const T& t1, const T& t2, ts_&&... ts );

	float rad2deg( const float x );
	float deg2rad( const float x );

	template< typename T = float >
	T& normalize_yaw( T& yaw );
} // namespace math

#include "math.inl"
