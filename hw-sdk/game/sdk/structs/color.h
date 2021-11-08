#pragma once
#include <algorithm>
#include <iostream>

// https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-levels-3-and-4-c4244?view=msvc-160
#pragma warning( disable : 4244 )

struct color {
	unsigned char r, g, b, a;

	// ctors
	constexpr color( ) : r{ 0 }, g{ 0 }, b{ 0 }, a{ 255 } { };

	constexpr color( unsigned char re, unsigned char gr, unsigned char bl, unsigned char al = 255 ) : r{ re }, g{ gr }, b{ bl }, a{ al } { };

	constexpr color( std::uint32_t hex ) : r( ( hex >> 24 ) & 0xFF ), g( ( hex >> 16 ) & 0xFF ), b( ( hex >> 8 ) & 0xFF ), a( hex & 0xFF ){ };

	constexpr std::uint32_t to_u32( ) const
	{
		return ( ( r & 0xff ) << 24 ) + ( ( g & 0xff ) << 16 ) + ( ( b & 0xff ) << 8 ) + ( a & 0xff );
	}
	constexpr static color from_u32( unsigned int col )
	{
		return color( static_cast< int >( ( col >> 0 ) & 0xFF ), static_cast< int >( ( col >> 8 ) & 0xFF ),
		              static_cast< int >( ( col >> 16 ) & 0xFF ), static_cast< int >( ( col >> 24 ) & 0xFF ) );
	};
	constexpr color set_alpha( std::uint8_t new_alpha )
	{
		return color( r, g, b, std::clamp< std::uint8_t >( new_alpha, ( std::uint8_t )0, ( std::uint8_t )255 ) );
	}
	constexpr color lerp( const color col, const float t )
	{
		const auto lerp = []( const unsigned char from, const unsigned char to, const float t ) {
			return ( unsigned char )( ( 1.f - t ) * from + t * to );
		};

		color lerped = *this;

		lerped.r = lerp( r, col.r, t );
		lerped.g = lerp( g, col.g, t );
		lerped.b = lerp( b, col.b, t );
		lerped.a = lerp( a, col.a, t );

		return lerped;
	}
	// operators:
	constexpr bool operator==( const color& other ) const
	{
		return other.r == r && other.g == g && other.b == b && other.a == a;
	}
	constexpr bool operator!=( const color& other ) const
	{
		return other.r != r || other.g != g || other.b != b || other.a != a;
	}
	constexpr color& operator*=( const float f )
	{
		r = static_cast< int >( r * f );
		g = static_cast< int >( g * f );
		b = static_cast< int >( b * f );
		return *this;
	}
	constexpr color operator( )( const int al ) const
	{
		return color( r, g, b, al );
	}
	constexpr color& operator/=( const float d )
	{
		const auto float_division = 1.f / d;
		*this *= float_division;

		return *this;
	}
	constexpr color& operator*( const float coeff ) const
	{
		auto color = *this;
		return color *= coeff;
	}
	constexpr color& operator=( color col ) const
	{
		color cf{ *this };
		cf.r = col.r;
		cf.g = col.g;
		cf.b = col.b;
		return cf;
	};
	constexpr color& operator+( color col ) const
	{
		color cf = { *this };
		cf.r += col.r;
		cf.g += col.g;
		cf.b += col.b;
		cf.a += col.a;

		return cf;
	};
	constexpr color& operator-( color col ) const
	{
		color cf = { *this };
		cf.r -= col.r;
		cf.g -= col.g;
		cf.b -= col.b;
		cf.a -= col.a;

		return cf;
	};
};
