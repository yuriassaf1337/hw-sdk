#include "visuals.h"

math::box visuals::esp_box::calculate_box( sdk::c_cs_player* player )
{
	math::vec3 mins = this->mins;
	math::vec3 maxs = this->maxs;

	math::matrix_3x4 transform = this->rgfl;

	math::vec3 points[] = { math::vec3( mins.x, mins.y, mins.z ), math::vec3( mins.x, maxs.y, mins.z ), math::vec3( maxs.x, maxs.y, mins.z ),
		                    math::vec3( maxs.x, mins.y, mins.z ), math::vec3( maxs.x, maxs.y, maxs.z ), math::vec3( mins.x, maxs.y, maxs.z ),
		                    math::vec3( mins.x, mins.y, maxs.z ), math::vec3( maxs.x, mins.y, maxs.z ) };

	math::vec3 translated_points[ 8 ];

	for ( int iterator = 0; iterator < 8; iterator++ )
		translated_points[ iterator ] = math::vector_transform( points[ iterator ], transform );

	bool on_screen = false;

	math::vec2< int > screen_points[ 8 ];

	for ( int iterator = 0; iterator < 8; iterator++ ) {
		bool buffer_on_screen = true;

		screen_points[ iterator ] = utils::world_to_screen( translated_points[ iterator ], buffer_on_screen );

		if ( buffer_on_screen )
			on_screen = true;
	}

	float top    = screen_points[ 0 ].y;
	float left   = screen_points[ 0 ].x;
	float right  = screen_points[ 0 ].x;
	float bottom = screen_points[ 0 ].y;

	for ( int iterator = 1; iterator < 8; iterator++ ) {
		if ( left > screen_points[ iterator ].x )
			left = screen_points[ iterator ].x;
		if ( top > screen_points[ iterator ].y )
			top = screen_points[ iterator ].y;
		if ( right < screen_points[ iterator ].x )
			right = screen_points[ iterator ].x;
		if ( bottom < screen_points[ iterator ].y )
			bottom = screen_points[ iterator ].y;
	}

	return math::box( left, top, right, bottom );
}

void visuals::impl::update_box( esp_object& object )
{
	object.box.cornered     = false;
	object.box.outline[ 0 ] = true;
	object.box.outline[ 1 ] = true;
	object.box.draw         = false;
	object.box._color.r     = 255;
	object.box._color.g     = 255;
	object.box._color.b     = 255;
	object.box._color.a     = 255;

	object.box.titles.clear( );

	auto buffer_title = esp_title( );

	buffer_title.location = esp_title_location::TITLE_TOP;
	buffer_title.text     = object.owner->name( ).c_str( ); // yeah....
	buffer_title._color.r = 255;
	buffer_title._color.g = 0;
	buffer_title._color.b = 0;
	buffer_title._color.a = 255;

	object.box.titles.push_back( buffer_title );
}

void visuals::impl::update( )
{
	for ( auto player : g_entity_list.players ) {
		esp_object& buffer_object = esp_objects[ player->entity_index( ) ];

		buffer_object.owner = player;

		if ( true )
			update_box( buffer_object );
	}
}

void visuals::impl::render( )
{
	HEYIMDRAWINHERE = true;

	for ( auto player : g_entity_list.players ) {
		if ( !player )
			continue;

		esp_object& object = esp_objects[ player->entity_index( ) ];

		update( );

		object.box.render( player );
	}

	HEYIMDRAWINHERE = false;
}

void visuals::esp_box::render( sdk::c_cs_player* owner )
{
	auto dimensions = calculate_box( owner );
	auto position   = math::vec2< int >( static_cast< int >( dimensions.x ), static_cast< int >( dimensions.y ) );
	auto size       = math::vec2< int >( static_cast< int >( dimensions.w ), static_cast< int >( dimensions.h ) ) - position;

	if ( this->draw ) {
		if ( this->outline[ 0 ] )
			g_render.render_rectangle< int >( position - math::vec2< int >( 1, 1 ), size + math::vec2< int >( 2, 2 ),
			                                  color( 0, 0, 0, this->_color.a ) );
		if ( this->outline[ 1 ] )
			g_render.render_rectangle< int >( position + math::vec2< int >( 1, 1 ), size - math::vec2< int >( 2, 2 ),
			                                  color( 0, 0, 0, this->_color.a ) );

		g_render.render_rectangle< int >( position, size, this->_color );
	}

	for ( auto& title : this->titles )
		title.render( dimensions );
}

void visuals::esp_title::render( math::box box )
{
	auto font = g_fonts[ HASH( _( "esp_font" ) ) ];

	auto text_size_buffer = g_render.render_text_size( this->text.c_str( ), font );
	auto text_size        = math::vec2< int >( text_size_buffer.x, text_size_buffer.y );

	math::vec2< int > position;

	if ( location == esp_title_location::TITLE_TOP )
		position = math::vec2< int >( ( ( box.x + ( box.w - box.x ) / 2 ) - text_size.x / 2 ) - 2, ( box.y - text_size.y ) - 6 );

	g_render.render_filled_rectangle( position, math::vec2< int >( text_size.x + 5, text_size.y + 4 ), color( 0, 0, 0, this->_color.a * 0.7 ) );
	g_render.render_filled_rectangle( position, math::vec2< int >( 1, text_size.y + 4 ), this->_color );

	g_render.render_text( position + math::vec2< int >( 3, 2 ), font_alignment::AL_DEFAULT, font_flags::FLAG_NONE, this->text.c_str( ), font,
	                      color( 255, 255, 255, 255 ) );
}
