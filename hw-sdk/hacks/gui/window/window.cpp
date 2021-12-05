#include "window.h"
#include "../cfg/cfg.h"
#include "../utils/utils.h"
#include "tabs/tabs.h"

bool gui::forms::window_impl::begin_window( const std::string_view name )
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
	} // \/ temp size for now
	title_bar_hovered = g_input.mouse.in_params( g_gui.position, math::vec2< int >( g_gui.size.x, 50 ) );

	// make sure we're not focused on any elements to move menu
	if ( g_gui.focused_id == UNFOCUSED ) {
		// set is dragging flag
		if ( !g_gui.main.dragging && g_input.key_state< input::key_state_t::KEY_DOWN >( VK_LBUTTON ) && title_bar_hovered )
			g_gui.main.dragging = true;
		else if ( g_gui.main.dragging && g_input.key_state< input::key_state_t::KEY_DOWN >( VK_LBUTTON ) )
			g_gui.position += delta;
		else if ( g_gui.main.dragging && !g_input.key_state< input::key_state_t::KEY_RELEASED >( VK_LBUTTON ) )
			g_gui.main.dragging = false;
	}

	// render all 3 menu outlines
	g_render.render_rectangle< int >( g_gui.position, g_gui.size, gui::pallete::first_outline( ) );
	g_render.render_rectangle< int >( g_gui.position + 1, g_gui.size - 2, gui::pallete::second_outline( ) );
	g_render.render_rectangle< int >( g_gui.position + 2, g_gui.size - 4, gui::pallete::third_outline( ) );

	// render menu's main gradient
	g_render.render_gradient< gradient_type_t::VERTICAL, int >( g_gui.position + 3, g_gui.size - 6, color( 25, 25, 25, g_gui.main.alpha ),
	                                                            color( 17, 17, 17, g_gui.main.alpha ) );

	// render text and add a .vip next to it.
	g_render.render_text( g_gui.position + math::vec2< int >( 12, 10 ), font_alignment::AL_DEFAULT, font_flags::FLAG_OUTLINE, name.data( ),
	                      g_fonts[ HASH( "main_font" ) ], color( 255, 255, 255, g_gui.main.alpha ) );

	color accent = g_cfg.as_color< configs::alpha_type::GUI_ALPHA >( _( "main_menu_color" ) );

	g_render.render_text( g_gui.position + math::vec2< int >( 14 + g_render.render_text_size( name.data( ), g_fonts[ HASH( "main_font" ) ] ).x, 10 ),
	                      font_alignment::AL_DEFAULT, font_flags::FLAG_OUTLINE, _( ".vip" ), g_fonts[ HASH( "main_font" ) ], accent);

	// swap stack
	std::stack< math::vec2< int > >( ).swap( g_gui.cursor_pos_stack );

	// just a random number for now but this is were elements should be starting to draw from starting window position
	gui::helpers::push_cursor( { 20, 60 } );

	old_mouse_pos = g_input.mouse.pos;

	return true;
}

void gui::forms::window_impl::end_window( )
{
	// do tabs here
	if ( !g_gui.tabs.empty( ) ) {
		g_tabs.think( g_gui.tabs );
	}
}
