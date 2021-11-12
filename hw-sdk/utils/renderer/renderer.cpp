#include <iostream>

#include "../../dependencies/hash/hash.h"
#include "../../dependencies/xor/xor.h"
#include "../../globals/macros/macros.h"

#include "renderer.h"

#include <assert.h>

#define DEVICE_SAFETY                                                                                                                                \
	if ( !device )                                                                                                                                   \
		assert( _( "Forgot to initialize device?" ) );

#define FAIL_CHECK( return_code )                                                                                                                    \
	if ( FAILED( return_code ) )                                                                                                                     \
		assert( _( "Operation failed." ) );

void render::init( IDirect3DDevice9* buffer_device )
{
	device = buffer_device;

	create_font( 14, FW_NORMAL, true, _( "Tahoma" ), fonts::main_font );
	create_font( 14, FW_BOLD, true, _( "Tahoma" ), fonts::main_bold_font );
}

void render::create_font( std::size_t size, std::size_t weight, bool anti_aliased, const char* name, LPD3DXFONT& font )
{
	DEVICE_SAFETY

	FAIL_CHECK( D3DXCreateFont( device, size, 0, weight, 1, false, DEFAULT_CHARSET, 1, anti_aliased ? ANTIALIASED_QUALITY : NONANTIALIASED_QUALITY,
	                            DEFAULT_PITCH, name, &font ) )
}