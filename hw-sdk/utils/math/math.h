#pragma once
#include "types/matrix_3x4.h"
#include "types/vector.h"
#include <corecrt_math_defines.h>
#include <numbers>

#undef min
#undef max

namespace math
{
	namespace util
	{
		constexpr static long double pi = std::numbers::pi_v< long double >;
		constexpr static float pi_f     = static_cast< float >( pi );
	} // namespace util

	math::vec3 angle_vector( const math::vec3& angle );

	void angle_vectors( const math::vec3& angles, math::vec3* fw, math::vec3* rg = nullptr, math::vec3* up = nullptr );

	template< typename T = float >
	T& get_fov( const math::vec3& view_angles, const math::vec3& start, const math::vec3& end );

	template< typename T >
	constexpr T min( const T& t1, const T& t2 );

	template< typename T, typename... ts_ >
	constexpr T min( const T& t1, const T& t2, ts_&&... ts );

	template< typename T >
	constexpr T max( const T& t1, const T& t2 );

	template< typename T, typename... ts_ >
	constexpr T max( const T& t1, const T& t2, ts_&&... ts );

	template< typename T = float >
	T& normalize_yaw( T& yaw );

	constexpr float rad2deg( const float x );
	constexpr float deg2rad( const float x );

} // namespace math

#include "math.inl"
