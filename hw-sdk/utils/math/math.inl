
template< typename T >
T& math::normalize_yaw( T& yaw )
{
	if ( yaw > T( 180 ) )
		yaw -= static_cast< T >( std::roundf( yaw / 360.f ) * 360.f );
	else if ( yaw < T( -180 ) )
		yaw += static_cast< T >( std::roundf( yaw / 360.f ) * 360.f );

	return T( yaw );
}

template< typename T >
constexpr T math::min( const T& t1, const T& t2 )
{
	return t1 < t2 ? t1 : t2;
}

template< typename T, typename... ts_ >
constexpr T math::min( const T& t1, const T& t2, ts_&&... ts )
{
	return t1 < t2 ? min( t1, std::forward< ts_ >( ts )... ) : min( t2, std::forward< ts_ >( ts )... );
}

template< typename T >
constexpr T math::max( const T& t1, const T& t2 )
{
	return t1 > t2 ? t1 : t2;
}

template< typename T, typename... ts_ >
constexpr T math::max( const T& t1, const T& t2, ts_&&... ts )
{
	return t1 > t2 ? max( t1, std::forward< ts_ >( ts )... ) : max( t2, std::forward< ts_ >( ts )... );
}