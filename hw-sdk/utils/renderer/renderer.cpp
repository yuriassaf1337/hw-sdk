#include <assert.h>
#include <iostream>

#include "../console/console.h"
#include "renderer.h"

void render::init( IDirect3DDevice9* buffer_device )
{
	device = buffer_device;

	fonts::create_font( _( "main_font" ), 14, FW_NORMAL, true, _( "Tahoma" ) );
	fonts::create_font( _( "main_font_bold" ), 14, FW_BOLD, true, _( "Tahoma" ) );

	auto Test = fonts::find( _( "main_font" ) );

	auto* Test2 = &fonts::font_list;
}

void render::create_font( std::size_t size, std::size_t weight, bool anti_aliased, const char* name, LPD3DXFONT& font )
{
	DEVICE_SAFETY( );

	FAIL_CHECK( D3DXCreateFont( device, size, 0, weight, 1, false, DEFAULT_CHARSET, 1, anti_aliased ? ANTIALIASED_QUALITY : NONANTIALIASED_QUALITY,
	                            DEFAULT_PITCH, name, &font ) )
}

void render::render_line( int x, int y, int width, int height, color color )
{
	DEVICE_SAFETY( );

	vertex segments[]{ { x, y, color }, { width, height, color } };

	device->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );
	FAIL_CHECK( device->DrawPrimitiveUP( D3DPT_LINELIST, 1, segments, sizeof( vertex ) ) );
}

void render::render_rectangle( int x, int y, int width, int height, color color )
{
	DEVICE_SAFETY( );

	render_line( x, y, x + width, y, color );
	render_line( x, y, x, y + height, color );
	render_line( x, y + height, x + width, y + height, color );
	render_line( x + width, y, x + width, y + height, color );
}

void render::render_filled_rectangle( int x, int y, int width, int height, color color )
{
	DEVICE_SAFETY( );

	vertex segments[]{ { x, y, color }, { x + width, y, color }, { x, y + height, color }, { x + width, y + height, color } };

	device->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );
	FAIL_CHECK( device->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, segments, sizeof( vertex ) ) );
}

void fonts::create_font( const char* name, std::size_t size, std::size_t weight, bool anti_aliased, const char* font_name )
{
	LPD3DXFONT buffer_font;

	render::create_font( size, weight, anti_aliased, font_name, buffer_font );

	font_list.push_back( { buffer_font, HASH( name ) } );
}
