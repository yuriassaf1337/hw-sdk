#include <assert.h>
#include <iostream>

#include "../console/console.h"
#include "renderer.h"

void render::impl::init( IDirect3DDevice9* buffer_device )
{
	render::device = buffer_device;

	fonts::create_font( _( "main_font" ), 14, FW_NORMAL, true, _( "Tahoma" ) );
	fonts::create_font( _( "main_font_bold" ), 14, FW_BOLD, true, _( "Tahoma" ) );
	fonts::create_font( _( "main_verdana_font" ), 13, FW_NORMAL, true, _( "Verdana" ) );
	fonts::create_font( _( "main_verdana_bold_font" ), 13, FW_BOLD, true, _( "Verdana" ) );
	fonts::create_font( _( "indicator_verdana_font" ), 30, FW_BOLD, true, _( "Verdana" ) );

	console::print< console::log_level::DEBUG >( _( "Created {} fonts." ), fonts::font_list.size( ) );
}

void render::impl::setup_state( )
{
	device->CreateStateBlock( D3DSBT_PIXELSTATE, &state );
	state->Capture( );
	device->GetVertexDeclaration( &vertex_declaration );
	device->GetVertexShader( &vertex_shader );

	device->SetVertexShader( nullptr );
	device->SetPixelShader( nullptr );
	device->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );
	device->SetRenderState( D3DRS_LIGHTING, false );
	device->SetRenderState( D3DRS_FOGENABLE, false );
	device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	device->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

	device->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
	device->SetRenderState( D3DRS_SCISSORTESTENABLE, true );
	device->SetRenderState( D3DRS_ZWRITEENABLE, false );
	device->SetRenderState( D3DRS_STENCILENABLE, false );

	device->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, false );
	device->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE, true );

	device->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
	device->SetRenderState( D3DRS_ALPHATESTENABLE, false );
	device->SetRenderState( D3DRS_SEPARATEALPHABLENDENABLE, true );
	device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	device->SetRenderState( D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA );
	device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	device->SetRenderState( D3DRS_DESTBLENDALPHA, D3DBLEND_ONE );

	device->SetRenderState( D3DRS_SRGBWRITEENABLE, false );
	device->SetRenderState( D3DRS_COLORWRITEENABLE,
	                        D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA );

	device->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	device->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	device->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	device->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	device->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	device->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

	device->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	device->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
}

void render::impl::finish_state( )
{
	state->Apply( );
	state->Release( );

	device->SetVertexDeclaration( vertex_declaration );
	device->SetVertexShader( vertex_shader );
}

void render::impl::create_font( std::size_t size, std::size_t weight, bool anti_aliased, const char* name, LPD3DXFONT& font )
{
	DEVICE_SAFETY( );

	FAIL_CHECK( D3DXCreateFont( device, size, 0, weight, 1, false, DEFAULT_CHARSET, 1, anti_aliased ? ANTIALIASED_QUALITY : NONANTIALIASED_QUALITY,
	                            DEFAULT_PITCH, name, &font ) )
}

void render::impl::render_line( int x, int y, int width, int height, color color )
{
	DEVICE_SAFETY( );

	vertex segments[]{ { x, y, color }, { width, height, color } };

	render::device->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );
	FAIL_CHECK( render::device->DrawPrimitiveUP( D3DPT_LINELIST, 1, segments, sizeof( vertex ) ) );
}

void render::impl::render_rectangle( int x, int y, int width, int height, color color )
{
	DEVICE_SAFETY( );

	g_render.render_line( x, y, x + width, y, color );
	g_render.render_line( x, y, x, y + height, color );
	g_render.render_line( x, y + height, x + width, y + height, color );
	g_render.render_line( x + width, y, x + width, y + height, color );
}

void render::impl::render_filled_rectangle( int x, int y, int width, int height, color color )
{
	DEVICE_SAFETY( );

	vertex segments[]{ { x, y, color }, { x + width, y, color }, { x, y + height, color }, { x + width, y + height, color } };

	render::device->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );
	FAIL_CHECK( render::device->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, segments, sizeof( vertex ) ) );
}

D3DXVECTOR2 render::impl::render_text_size( const char* string, LPD3DXFONT font )
{
	RECT rect{ };

	font->DrawTextA( nullptr, string, -1, &rect, DT_CALCRECT, color( 0, 0, 0, 0 ).to_u32( ) );

	return D3DXVECTOR2( rect.left - rect.right, rect.bottom - rect.top );
}

void render::impl::render_text( int x, int y, unsigned int alignment, unsigned int flags, const char* string, LPD3DXFONT font, color _color )
{
	DEVICE_SAFETY( );

	RECT rect{ };

	D3DXVECTOR2 text_size = g_render.render_text_size( string, font );

	auto set_rect = []( RECT* rect, int x, int y ) { SetRect( rect, x, y, x, y ); };

	if ( !( alignment & font_alignment::AL_DEFAULT ) ) {
		if ( alignment & font_alignment::AL_VERTICAL_TOP )
			y -= text_size.y;
		if ( alignment & font_alignment::AL_VERTICAL_CENTER )
			y -= text_size.y / 2;
		if ( alignment & font_alignment::AL_HORIZONTAL_LEFT )
			x -= text_size.x;
		if ( alignment & font_alignment::AL_HORIZONTAL_CENTER )
			x -= text_size.x;
	}

	if ( flags & font_flags::FLAG_NONE ) {
		set_rect( &rect, x, y );
		font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, _color.to_u32( ) );
	} else {
		if ( flags & font_flags::FLAG_DROPSHADOW ) {
			set_rect( &rect, x + 1, y + 1 );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, color( _color.r, 0, 0, 0 ).to_u32( ) );

			set_rect( &rect, x, y );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, _color.to_u32( ) );
		}

		if ( flags & font_flags::FLAG_OUTLINE ) {
			set_rect( &rect, x, y + 1 );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, color( 255, 0, 0, 0 ).to_u32( ) );
			set_rect( &rect, x + 1, y );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, color( 255, 0, 0, 0 ).to_u32( ) );
			set_rect( &rect, x, y - 1 );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, color( 255, 0, 0, 0 ).to_u32( ) );
			set_rect( &rect, x - 1, y );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, color( 255, 0, 0, 0 ).to_u32( ) );

			set_rect( &rect, x + 1, y );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, color( 255, 0, 0, 0 ).to_u32( ) );
			set_rect( &rect, x, y + 1 );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, color( 255, 0, 0, 0 ).to_u32( ) );
			set_rect( &rect, x - 1, y );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, color( 255, 0, 0, 0 ).to_u32( ) );
			set_rect( &rect, x, y - 1 );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, color( 255, 0, 0, 0 ).to_u32( ) );

			set_rect( &rect, x + 1, y + 1 );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, color( 255, 0, 0, 0 ).to_u32( ) );
			set_rect( &rect, x - 1, y - 1 );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, color( 255, 0, 0, 0 ).to_u32( ) );
			set_rect( &rect, x + 1, y - 1 );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, color( 255, 0, 0, 0 ).to_u32( ) );
			set_rect( &rect, x - 1, y + 1 );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, color( 255, 0, 0, 0 ).to_u32( ) );

			set_rect( &rect, x, y );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, _color.to_u32( ) );
		}
	}
}

void render::impl::render_vertical_gradient( int x, int y, int width, int height, color from, color to, bool is_horizontal )
{
	DEVICE_SAFETY( );

	math::vec2< float > a{ static_cast< float >( x ), static_cast< float >( y ) }, b{ static_cast< float >( width ), static_cast< float >( height ) };

	struct vertex_mod {
		float x, y, z, rhw;
		std::uint32_t c;
	};

	vertex_mod vertices[ 4 ]{
		{ a.x, a.y, 0.01f, 0.01f, from.to_u32( ) },
		{ b.x, a.y, 0.01f, 0.01f, is_horizontal ? to.to_u32( ) : from.to_u32( ) },
		{ a.x, b.y, 0.01f, 0.01f, is_horizontal ? from.to_u32( ) : to.to_u32( ) },
		{ b.x, b.y, 0.01f, 0.01f, to.to_u32( ) },
	};

	device->SetTexture( 0x0, nullptr );
	device->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, &vertices, 20 );
}

void fonts::create_font( const char* name, std::size_t size, std::size_t weight, bool anti_aliased, const char* font_name )
{
	LPD3DXFONT buffer_font;

	g_render.create_font( size, weight, anti_aliased, font_name, buffer_font );

	font_list.push_back( { buffer_font, HASH( name ) } );
}
