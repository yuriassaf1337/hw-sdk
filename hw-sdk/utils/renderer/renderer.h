#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <deque>
#include <iostream>

#include "../../dependencies/hash/hash.h"
#include "../../dependencies/xor/xor.h"
#include "../../globals/macros/macros.h"

#include "../../game/sdk/structs/color.h"

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

enum font_flags
{
	font_flag_none,
	font_flag_dropshadow,
	font_flag_outline
};

enum font_alignment
{
	font_alignment_default,
	font_alignment_vertical_top,
	font_alignment_vertical_center,
	font_alignment_horizontal_left,
	font_alignment_horizontal_center,
};

class vertex
{
public:
	float x{ }, y{ }, z{ }, rhw{ };
	D3DCOLOR _color{ };
	D3DXVECTOR2 position{ }, tex_coord{ };

	vertex( ) = default;

	vertex( const float x, const float y, color c )
	{
		this->x      = x;
		this->y      = y;
		this->_color = D3DCOLOR_ARGB( c.a, c.r, c.g, c.b );
	}

	vertex( int x, int y, color c )
	{
		this->x      = static_cast< float >( x );
		this->y      = static_cast< float >( y );
		this->_color = D3DCOLOR_ARGB( c.a, c.r, c.g, c.b );
	}

	vertex( float x, float y, float w, float h, color c )
	{
		this->position  = { x, y };
		this->tex_coord = { w, h };
		this->_color    = D3DCOLOR_ARGB( c.a, c.r, c.g, c.b );
	}

	vertex( const D3DXVECTOR2& pos, const D3DXVECTOR2& coord = D3DXVECTOR2( 0, 0 ) )
	{
		this->position  = pos;
		this->tex_coord = coord;
	}
};

struct font {
	LPD3DXFONT _font;
	unsigned int name;
};

namespace render
{
	inline IDirect3DDevice9* device;

	void init( IDirect3DDevice9* buffer_device );

	void create_font( std::size_t size, std::size_t weight, bool anti_aliased, const char* name, LPD3DXFONT& font );

	void render_line( int x, int y, int width, int height, color color );

	void render_rectangle( int x, int y, int width, int height, color color );
	void render_filled_rectangle( int x, int y, int width, int height, color color );

	D3DXVECTOR2 render_text_size(const char* string, LPD3DXFONT font);
	void render_text(int x, int y, unsigned int alignment, unsigned int flags, const char* string, LPD3DXFONT font, color color);
} // namespace render

namespace fonts
{
	// TODO @ liga - this is cancer, we dont want have to create a pointer to every font we create
	// takes way more work. we could just do a hashed string vector and push back font names, ex:
	//
	// inline std::vector<std::uint32_t> fonts;
	// fonts.push_back(HASH("main_font"));

	inline std::deque< font > font_list;

	void create_font( const char* name, std::size_t size, std::size_t weight, bool anti_aliased, const char* font_name );

	inline LPD3DXFONT find( const char* name )
	{
		for ( auto iterator = font_list.begin( ); iterator != font_list.end( ); iterator++ ) {
			if ( iterator->name == HASH( name ) )
				return iterator->_font;
		}

		return nullptr;
	}
	inline LPD3DXFONT find( unsigned int name )
	{
		for ( auto iterator = font_list.begin( ); iterator != font_list.end( ); iterator++ ) {
			if ( iterator->name == name )
				return iterator->_font;
		}

		return nullptr;
	}
} // namespace fonts
