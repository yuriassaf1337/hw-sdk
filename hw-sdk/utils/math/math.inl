#pragma once

template< typename T >
T& math::normalize_yaw( T& yaw )
{
	if ( yaw > T( 180 ) )
		yaw -= static_cast< T >( roundf( yaw / 360.f ) * 360.f );
	else if ( yaw < T( -180 ) )
		yaw += static_cast< T >( roundf( yaw / 360.f ) * 360.f );

	return T( yaw );
}