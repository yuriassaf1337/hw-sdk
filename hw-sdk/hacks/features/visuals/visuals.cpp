#include "visuals.h"

math::vec4 visuals::esp_box::calculate_box( sdk::c_cs_player* player )
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

	return math::vec4( left, top, right, bottom );
}

void visuals::impl::update_box( esp_object& object )
{
	object.box.cornered = false;
	object.box.outline  = true;
	object.box._color.r = 255;
	object.box._color.g = 255;
	object.box._color.b = 255;
	object.box._color.a = 255;
}

void visuals::impl::update( )
{
	for ( auto& player : g_entity_list.players ) {
		esp_object& buffer_object = esp_objects[ player->entity_index( ) ];

		buffer_object.owner = player;

		if ( true )
			update_box( buffer_object );
	}
}

void visuals::impl::render( )
{
	for ( auto& player : g_entity_list.players ) {
		esp_object& object = esp_objects[ player->entity_index( ) ];

		object.box.render( player );
	}
}

void visuals::esp_box::render( sdk::c_cs_player* owner )
{
	auto dimensions = calculate_box( owner );
	auto position   = math::vec2< int >( static_cast< int >( dimensions.x ), static_cast< int >( dimensions.y ) );
	auto size       = math::vec2< int >( static_cast< int >( dimensions.z ), static_cast< int >( dimensions.w ) ) - position;

	 if ( this->outline ) {
		g_render.render_rectangle< int >( position - math::vec2< int >( 1, 1 ), size + math::vec2< int >( 2, 2 ), color( 0, 0, 0, this->_color.a ) );
		g_render.render_rectangle< int >( position + math::vec2< int >( 1, 1 ), size - math::vec2< int >( 2, 2 ), color( 0, 0, 0, this->_color.a ) );
	 }

	g_render.render_rectangle< int >( position, size, this->_color );
}
