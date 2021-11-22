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

void math::angle_vectors( const math::vec3& angles, math::vec3* fw, math::vec3* rg, math::vec3* up )
{
	const float cp = std::cos( math::deg2rad( angles.x ) ), sp = std::sin( math::deg2rad( angles.x ) );
	const float cy = std::cos( math::deg2rad( angles.y ) ), sy = std::sin( math::deg2rad( angles.y ) );
	const float cr = std::cos( math::deg2rad( angles.z ) ), sr = std::sin( math::deg2rad( angles.z ) );

	if ( fw ) {
		fw->x = cp * cy;
		fw->y = cp * sy;
		fw->z = -sp;
	}

	if ( rg ) {
		rg->x = -1.f * sr * sp * cy + -1.f * cr * -sy;
		rg->y = -1.f * sr * sp * sy + -1.f * cr * cy;
		rg->z = -1.f * sr * cp;
	}

	if ( up ) {
		up->x = cr * sp * cy + -sr * -sy;
		up->y = cr * sp * sy + -sr * cy;
		up->z = cr * cp;
	}
}

constexpr float math::rad2deg( const float x )
{
	return x * ( 180.f / math::util::pi_f );
}

constexpr float math::deg2rad( const float x )
{
	return x * ( math::util::pi_f / 180.f );
}
