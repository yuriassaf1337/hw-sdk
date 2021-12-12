#include "groupbox.h"
#include "../../../utils/renderer/renderer.h"
#include "../includes/includes.h"
#include "../utils/ui_utils.h"

void gui::groupbox::impl::invoke_groupbox( const std::string& name, const math::vec2< int > size )
{
	// get groupbox id
	const auto my_id = gui::helpers::hash( name );
	m_id             = my_id;

	math::vec2< int > cursor_pos = gui::helpers::pop_cursor( );
	math::vec2< int > group_size{ };

	float m_width{ static_cast< float >( size.x ) / 100.f };
	float m_height{ static_cast< float >( size.y ) / 100.f };

	int width_available  = g_gui.size.x - 110;
	int height_available = g_gui.size.y - 120;

	if ( cursor_pos.x == 16 && m_width == 1.0f )
		width_available += 15;

	group_size.x = static_cast< int >( width_available * m_width );

	if ( cursor_pos.y == 46 && m_height == 1.0f )
		height_available += 15;

	group_size.y = static_cast< int >( height_available * m_height );

	if ( ( cursor_pos.y - 15 + group_size.y ) > g_gui.size.y - 15 ) {
		cursor_pos.x += group_size.x + 40;
		cursor_pos.y = 80;

		gui::helpers::push_cursor( cursor_pos );
		gui::groupbox::impl::invoke_groupbox( name, size );
	} else {
		math::vec2< int > draw_pos = g_gui.position + cursor_pos;

		g_render.render_filled_rectangle( draw_pos - 1, group_size + 2, gui::pallete::third_outline( ) );
		math::vec2< int > final_pos = { cursor_pos + math::vec2< int >( 20, 41 ) };

		gui::helpers::push_cursor( final_pos );
	}
}
