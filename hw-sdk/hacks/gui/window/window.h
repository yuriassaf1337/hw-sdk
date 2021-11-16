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
		window_impl( ) = default;
		explicit window_impl( std::uint8_t vk_key ) : open_key( vk_key ){ };

		bool begin_window( const std::string_view name );
		void end_window( );

	private:
		float ui_anim_state    = 0.f;
		bool title_bar_hovered = false;
		std::uint8_t open_key{ };
	};

	struct groupbox_impl {
	};
} // namespace gui::forms

inline gui::forms::window_impl g_window{ gui::forms::window_impl( VK_INSERT ) };
inline gui::forms::groupbox_impl g_groupbox;
