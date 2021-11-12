#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>

#include "../../game/sdk/structs/color.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace render
{
	inline IDirect3DDevice9* device;

	void init( IDirect3DDevice9* buffer_device );

	void create_font( std::size_t size, std::size_t weight, bool anti_aliased, const char* name, LPD3DXFONT& font );

	void render_rectangle( int x, int y, int width, int height, color color );
	void render_filled_rectangle( int x, int y, int width, int height, color color );
} // namespace render

namespace fonts
{
	inline LPD3DXFONT main_font;
	inline LPD3DXFONT main_bold_font;
} // namespace fonts
