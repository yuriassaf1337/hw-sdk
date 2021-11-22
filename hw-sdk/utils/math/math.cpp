#include "math.h"
#include "types/vector.h"

math::vec3 math::angle_vector( const math::vec3& angle )
{
	const auto sy = std::sin( angle.y / 180.f * math::util::pi_f );
	const auto cy = std::cos( angle.y / 180.f * math::util::pi_f );

	const auto sp = std::sin( angle.x / 180.f * math::util::pi_f );
	const auto cp = std::cos( angle.x / 180.f * math::util::pi_f );

	return math::vec3( cp * cy, cp * sy, -sp );
}

float math::rad2deg( const float x )
{
	return static_cast< float >( x * ( 180.f / math::util::pi_f ) );
}

float math::deg2rad( const float x )
{
	return static_cast< float >( x * ( math::util::pi_f / 180.f ) );
}
