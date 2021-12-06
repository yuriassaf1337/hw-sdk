#include "window.h"
#include "../../../globals/ctx/ctx.h"
#include "../cfg/cfg.h"
#include "../utils/utils.h"
#include "tabs/tabs.h"

void gui::elements::window_impl::util_t::draw_background( )
{
	// render all 3 menu outlines
	g_render.render_filled_rectangle< int >( g_gui.position, g_gui.size, gui::pallete::first_outline( ) );
	g_render.render_filled_rectangle< int >( g_gui.position + 2, g_gui.size - 4, gui::pallete::second_outline( ) );
	g_render.render_filled_rectangle< int >( g_gui.position + math::vec2< int >( 4, 36 ), g_gui.size - math::vec2< int >( 8, 40 ),
	                                         gui::pallete::third_outline( ) );

	// render menu's main gradient
	g_render.render_gradient< gradient_type_t::VERTICAL, int >( g_gui.position + math::vec2< int >( 6, 38 ),
	                                                            math::vec2< int >( g_gui.size.x - 12, g_gui.size.y - 44 ),
	                                                            color( 32, 32, 32, g_gui.main.alpha ), color( 24, 24, 24, g_gui.main.alpha ) );
}

void gui::elements::window_impl::util_t::draw_title_header( )
{
	// black header outline
	g_render.render_filled_rectangle< int >( g_gui.position + 2, math::vec2< int >( g_gui.size.x - 4, 32 ), gui::pallete::first_outline( ) );
	// grey header outline
	g_render.render_filled_rectangle< int >( g_gui.position + 2, math::vec2< int >( g_gui.size.x - 4, 30 ), gui::pallete::second_outline( ) );
	// gradient
	g_render.render_gradient< gradient_type_t::VERTICAL, int >( g_gui.position + 4, math::vec2< int >( g_gui.size.x - 8, 26 ),
	                                                            color( 27, 27, 27, g_gui.main.alpha ), color( 17, 17, 17, g_gui.main.alpha ) );
}

void gui::elements::window_impl::util_t::handle_drag( bool hover, const math::vec2< int >& delta )
{
	if ( !g_gui.main.dragging && g_input.key_state< input::key_state_t::KEY_DOWN >( VK_LBUTTON ) && hover )
		g_gui.main.dragging = true;
	else if ( g_gui.main.dragging && g_input.key_state< input::key_state_t::KEY_DOWN >( VK_LBUTTON ) ) {
		g_gui.position += delta;

		g_gui.position.x = std::clamp< int >( g_gui.position.x, 0, g_ctx.screen_size.x - g_gui.size.x );
		g_gui.position.y = std::clamp< int >( g_gui.position.y, 0, g_ctx.screen_size.y - g_gui.size.y );
	} else if ( g_gui.main.dragging && !g_input.key_state< input::key_state_t::KEY_RELEASED >( VK_LBUTTON ) )
		g_gui.main.dragging = false;
}

void gui::elements::window_impl::util_t::handle_resize( bool hover )
{
	if ( !g_gui.main.resizing && g_input.key_state< input::key_state_t::KEY_DOWN >( VK_LBUTTON ) && hover )
		g_gui.main.resizing = true;
	else if ( g_gui.main.resizing && g_input.key_state< input::key_state_t::KEY_DOWN >( VK_LBUTTON ) ) {
		g_gui.size = g_input.mouse.pos - g_gui.position;

		g_gui.size.x = std::clamp< int >( g_gui.size.x, 537, 900 );
		g_gui.size.y = std::clamp< int >( g_gui.size.y, 621, 800 );

	} else if ( g_gui.main.resizing && !g_input.key_state< input::key_state_t::KEY_RELEASED >( VK_LBUTTON ) )
		g_gui.main.resizing = false;
}

bool gui::elements::window_impl::begin_window( const std::string_view name )
{
	static math::vec2< int > old_mouse_pos;
	math::vec2< int > delta = g_input.mouse.pos - old_mouse_pos;
	// menu was toggled
	if ( g_input.key_state< input::key_state_t::KEY_RELEASED >( open_key ) ) {
		// main window alpha lower then max alpha
		if ( g_gui.main.alpha <= color::MAX_ALPHA ) {
			// reset element focused id
			if ( g_gui.focused_id != UNFOCUSED )
				g_gui.focused_id = UNFOCUSED;
			// reset dragging flag
			if ( g_gui.main.dragging )
				g_gui.main.dragging = false;
		}

		// switch between open and closed once menu key was released
		g_gui.main.open = !g_gui.main.open;
	}

	// handle menu alpha
	if ( g_gui.main.open ) {
		ui_anim_state += ( 1.0f / 0.25f ) * g_interfaces.globals->frame_time;
		ui_anim_state = std::clamp( ui_anim_state, 0.f, 1.f );

		g_gui.main.alpha = std::clamp< float >( gui::easing::out_quint( ui_anim_state ) * 255.f, 0.f, 255.f );
	} else {
		ui_anim_state -= ( 1.0f / 0.25f ) * g_interfaces.globals->frame_time;
		ui_anim_state = std::clamp( ui_anim_state, 0.f, 1.f );

		g_gui.main.alpha = std::clamp< float >( gui::easing::in_quint( ui_anim_state ) * 255.f, 0.f, 255.f );
	}

	title_bar_hovered   = g_input.mouse.in_params( g_gui.position, math::vec2< int >( g_gui.size.x, 50 ) );
	resize_area_hovered = g_input.mouse.in_params( g_gui.position + ( g_gui.size - math::vec2< int >( 30, 30 ) ), math::vec2< int >( 35, 35 ) );

	// make sure we're not focused on any elements to move menu
	if ( g_gui.focused_id == UNFOCUSED ) {
		// handle dragging
		utils.handle_drag( title_bar_hovered, delta );

		// handle resizing
		utils.handle_resize( resize_area_hovered );
	}

	utils.draw_background( );

	utils.draw_title_header( );

	// render text and add a .vip next to it.
	g_render.render_text( g_gui.position + math::vec2< int >( 12, 10 ), font_alignment::AL_DEFAULT, font_flags::FLAG_OUTLINE_SEMI, name.data( ),
	                      g_fonts[ HASH( "main_font_bold" ) ], color( 255, 255, 255, g_gui.main.alpha ) );

	g_render.render_text( g_gui.position +
	                          math::vec2< int >( 13 + g_render.render_text_size( name.data( ), g_fonts[ HASH( "main_font_bold" ) ] ).x, 10 ),
	                      font_alignment::AL_DEFAULT, font_flags::FLAG_OUTLINE_SEMI, _( ".vip" ), g_fonts[ HASH( "main_font_bold" ) ],
	                      g_cfg.as_color< configs::alpha_type::GUI_ALPHA >( _( "main_menu_color" ) ) );

	// swap stack
	std::stack< math::vec2< int > >( ).swap( g_gui.cursor_pos_stack );

	// just a random number for now but this is were elements should be starting to draw from starting window position
	gui::helpers::push_cursor( { 20, 60 } );

	old_mouse_pos = g_input.mouse.pos;

	return true;
}

void gui::elements::window_impl::end_window( )
{
	// do tabs here
	if ( !g_gui.tabs.empty( ) ) {
		g_tabs.think( g_gui.tabs );
	}
}
