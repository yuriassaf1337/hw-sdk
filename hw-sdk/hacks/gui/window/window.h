#pragma once
#include "../../../game/sdk/classes/i_global_vars.h"
#include "../../../game/sdk/structs/color.h"
#include "../../../globals/intefaces/interfaces.h"
#include "../../../utils/keybinds/keybinds.h"
#include "../../../utils/renderer/renderer.h"
#include "../includes/includes.h"
#include <stack>

namespace gui::forms
{
	struct window_impl {
	public:
		bool begin_window( const std::string_view name );
		void end_window( );

	private:
		float ui_anim_state    = 0.f;
		bool title_bar_hovered = false;
		// SORRY I CANT THINK OF ANOTHER NAME FOR THIS LOL
		void handle_start( std::uint8_t open_key )
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

			render::render_filled_rectangle< int >( g_gui.position, g_gui.size, gui::pallete::first_outline( ) );

			std::stack< math::vec2< int > >( ).swap( g_gui.cursor_pos_stack );

			old_mouse_pos = g_input.mouse.pos;
		}
	};

	struct groupbox_impl {
	};
} // namespace gui::forms

inline gui::forms::window_impl g_window;
inline gui::forms::groupbox_impl g_groupbox;
