#include "visuals.h"
#include <comdef.h>

math::box visuals::esp_box::calculate_box( sdk::c_cs_player* player )
{
	auto& player_info = g_entity_list.players[ player->entity_index( ) ];

	math::vec3 mins = player_info.m_mins;
	math::vec3 maxs = player_info.m_maxs;

	math::matrix_3x4 transform = player_info.m_rgfl;

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
	object.m_box.m_cornered     = false;
	object.m_box.m_outline[ 0 ] = true;
	object.m_box.m_outline[ 1 ] = true;
	object.m_box.m_draw         = false;

	object.m_box.m_color.r = 255;
	object.m_box.m_color.g = 255;
	object.m_box.m_color.b = 255;
	object.m_box.m_color.a = 255;

	object.m_box.m_titles.clear( );

	auto buffer_title = esp_title( );

	buffer_title.m_location = esp_title_location::TITLE_TOP;
	buffer_title.m_text     = object.m_owner->name( );
	buffer_title.m_color.r  = 200;
	buffer_title.m_color.g  = 50;
	buffer_title.m_color.b  = 0;
	buffer_title.m_color.a  = 255;

	object.m_box.m_titles.push_back( buffer_title );

	auto& current_weapon = g_entity_list.players[ object.m_owner->entity_index( ) ].m_weapon;

	if ( current_weapon ) {
		auto weapon_info      = current_weapon->get_weapon_data( );
		auto weapon_name_wide = g_interfaces.localize->find( weapon_info->hud_name );

		_bstr_t conversion( weapon_name_wide );

		const char* weapon_name = conversion;

		buffer_title.m_location = esp_title_location::TITLE_BOTTOM;
		buffer_title.m_text     = console::format( _( "{}: {}/{}" ), weapon_name, current_weapon->clip_mag( ), weapon_info->max_clip1 );
		buffer_title.m_color.r  = 50;
		buffer_title.m_color.g  = 50;
		buffer_title.m_color.b  = 200;
		buffer_title.m_color.a  = 255;

		object.m_box.m_titles.push_back( buffer_title );
	}
}

void visuals::impl::update( )
{
	for ( auto& player_info : g_entity_list.players ) {
		auto player = g_interfaces.entity_list->get_client_entity< sdk::c_cs_player* >( player_info.m_index );

		if ( !player_info.m_valid || !player )
			continue;

		esp_object& buffer_object = esp_objects[ player->entity_index( ) ];

		buffer_object.m_owner = player;

		if ( true )
			update_box( buffer_object );
	}
}

void visuals::impl::render( )
{
	for ( auto& player_info : g_entity_list.players ) {
		auto player = g_interfaces.entity_list->get_client_entity< sdk::c_cs_player* >( player_info.m_index );

		if ( !player_info.m_valid || !player )
			continue;

		esp_object& object = esp_objects[ player->entity_index( ) ];

		update( );

		object.m_box.render( player );
	}
}

void visuals::esp_box::render( sdk::c_cs_player* owner )
{
	auto dimensions = calculate_box( owner );
	auto position   = math::vec2< int >( static_cast< int >( dimensions.x ), static_cast< int >( dimensions.y ) );
	auto size       = math::vec2< int >( static_cast< int >( dimensions.w ), static_cast< int >( dimensions.h ) ) - position;

	if ( m_draw ) {
		if ( m_outline[ 0 ] )
			g_render.render_rectangle< int >( position - math::vec2< int >( 1, 1 ), size + math::vec2< int >( 2, 2 ), color( 0, 0, 0, m_color.a ) );
		if ( m_outline[ 1 ] )
			g_render.render_rectangle< int >( position + math::vec2< int >( 1, 1 ), size - math::vec2< int >( 2, 2 ), color( 0, 0, 0, m_color.a ) );

		g_render.render_rectangle< int >( position, size, m_color );
	}

	int iterator = 0;

	for ( auto& title : m_titles ) {
		title.render( dimensions, iterator );

		iterator++;
	}
}

void visuals::esp_title::render( math::box box, int offset )
{
	auto font = g_fonts[ HASH( _( "esp_font" ) ) ];

	auto text_size_buffer = g_render.render_text_size( m_text.c_str( ), font );
	auto text_size        = math::vec2< int >( text_size_buffer.x, text_size_buffer.y );

	math::vec2< int > position;

	if ( m_location == esp_title_location::TITLE_TOP )
		position = math::vec2< int >( ( ( box.x + ( box.w - box.x ) / 2 ) - text_size.x / 2 ) - 2,
		                              ( ( box.y - text_size.y ) - ( ( text_size.y + 4 ) * offset ) ) - 6 );
	if ( m_location == esp_title_location::TITLE_BOTTOM )
		position = math::vec2< int >( ( ( box.x + ( box.w - box.x ) / 2 ) - text_size.x / 2 ) - 2,
		                              ( ( box.h + text_size.y ) - ( ( text_size.y + 4 ) * offset ) ) + 6 );

	g_render.render_filled_rectangle( position, math::vec2< int >( text_size.x + 5, text_size.y + 4 ), color( 0, 0, 0, m_color.a * 0.7 ) );
	g_render.render_filled_rectangle( position, math::vec2< int >( 1, text_size.y + 4 ), m_color );

	g_render.render_text( position + math::vec2< int >( 3, 2 ), font_alignment::AL_DEFAULT, font_flags::FLAG_NONE, m_text.c_str( ), font,
	                      color( 255, 255, 255, 255 ) );
}
