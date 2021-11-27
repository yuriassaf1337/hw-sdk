
template< auto gradient_type >
void render::impl::render_gradient( int x, int y, int width, int height, color from, color to )
{
	DEVICE_SAFETY( );
	
	vertex verts[ 4 ] = {
		{ static_cast< float >( x ), static_cast< float >( y ), 0.01f, 0.01f, from.to_d3d( ) },
		{ static_cast< float >( x + width ), static_cast< float >( height ), 0.01f, 0.01f, gradient_type == gradient_type_t::HORIZONTAL ? to.to_d3d( ) : from.to_d3d( ) },
		{ static_cast< float >( x ), static_cast< float > ( y + width ), 0.01f, 0.01f, gradient_type == gradient_type_t::HORIZONTAL ? from.to_d3d( ) : to.to_d3d( ) },
		{ static_cast< float >( x + width ), static_cast< float >( y + height ), 0.01f, 0.01f, to.to_d3d( ) } 
	};

	device->SetTexture( 0, nullptr );
	FAIL_CHECK( device->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, &verts, 20 ) );
}

template< auto gradient_type, class T >
void render::impl::render_gradient( const math::vec2< T >& pos, const math::vec2< T >& size, color from, color to )
{
	render_gradient< gradient_type >( pos.x, pos.y, size.x, size.y, from, to );
}

template< class T >
void render::impl::render_rectangle( const math::vec2< T >& pos, const math::vec2< T >& size, color color )
{
	render_rectangle( pos.x, pos.y, size.x, size.y, color );
}

template< class T >
void render::impl::render_filled_rectangle( const math::vec2< T >& pos, const math::vec2< T >& size, color color )
{
	render_filled_rectangle( pos.x, pos.y, size.x, size.y, color );
}

template< class T >
void render::impl::render_text( const math::vec2< T >& pos, std::uint32_t alignment, std::uint32_t flags, const char* string, LPD3DXFONT font, color color )
{
	render_text( pos.x, pos.y, alignment, flags, string, font, color );
}