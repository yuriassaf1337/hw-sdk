#include "window.h"

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
		if ( !g_gui.main.dragging && g_input.key_state< input::key_state_t::KEY_RELEASED >( VK_LBUTTON ) && title_bar_hovered )
			g_gui.main.dragging = true;
		else if ( g_gui.main.dragging && g_input.key_state< input::key_state_t::KEY_DOWN >( VK_LBUTTON ) )
			g_gui.position -= delta;
		else if ( g_gui.main.dragging && !g_input.key_state< input::key_state_t::KEY_DOWN >( VK_LBUTTON ) )
			g_gui.main.dragging = false;
	}

	// outer outline (TODO: change this to an outline so we dont draw useless black background under menu)
	render::render_filled_rectangle< int >( g_gui.position, g_gui.size, gui::pallete::first_outline( ) );
	render::render_text( g_gui.position + math::vec2< int >( 20, 20 ), font_alignment::AL_VERTICAL_TOP, font_flags_t::FLAG_DROPSHADOW, name.data( ),
	                     fonts::find( _( "main_font" ) ), color( 255, 255, 255, 255 ) );
	// swap stack
	std::stack< math::vec2< int > >( ).swap( g_gui.cursor_pos_stack );

	// just a random number for now but this is were elements should be starting to draw from starting window position
	gui::helpers::push_cursor( { 20, 60 } );

	old_mouse_pos = g_input.mouse.pos;

	return true;
}
