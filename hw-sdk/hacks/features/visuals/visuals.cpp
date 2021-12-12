#include "visuals.h"

math::vec4 visuals::impl::calculate_box( sdk::c_cs_player* player )
{
	sdk::i_collideable* collideable = player->get_collideable( );

	if ( !collideable )
		return { };

	math::vec3 mins = collideable->obb_mins( );
	math::vec3 maxs = collideable->obb_maxs( );

	math::matrix_3x4 transform = player->rgfl_coordinate_frame( );

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

	return { left, top, right, bottom };
}

void visuals::impl::add_box( esp_object& object )
{
	object.box.cornered = false;
	object.box.outline  = true;
	object.box._color   = color( 255, 255, 255, 255 );
}

void visuals::impl::update( ) 
{
	
}

void visuals::impl::render( ) { }
