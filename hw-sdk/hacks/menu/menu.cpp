#include "menu.h"
#include "../../dependencies/imgui/dx9/imgui_impl_dx9.h"
#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_freetype.h"
#include "../../dependencies/imgui/imgui_impl_win32.h"
#include "../../globals/interfaces/interfaces.h"
#include "../../utils/keybinds/keybinds.h"
#include "imgui/imgui_helper.h"

bool menu::impl::init_input( )
{
	D3DDEVICE_CREATION_PARAMETERS creation_params = { };
	while ( FAILED( g_interfaces.device->GetCreationParameters( &creation_params ) ) )
		utils::sleep( 200 );

	window = creation_params.hFocusWindow;

	if ( !window )
		return false;

	return true;
}

void menu::impl::draw( )
{
	if ( !menu_open )
		return;

	g_imgui.set_next_window_size( ImVec2( 500, 450 ), ImGuiCond_Always );

	g_imgui.begin( _( "hotwheels-main-window" ), nullptr,
	               ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar );
	{
		ImDrawList* window_draw_list = ImGui::GetWindowDrawList( );

		g_imgui.start_decorations( window_draw_list );

		g_imgui.spacing( 1 );

		g_imgui.begin_child( _( "tabs-child" ), ImVec2( -1, 30 ), true, 0 );
		{
			g_imgui.set_cursor_pos_x( 12 );
			g_imgui.render_tab( _( "aimbot" ), 0 );
			g_imgui.same_line( 0.f, 59.f );

			g_imgui.render_tab( _( "anti-aim" ), 1 );
			g_imgui.same_line( 0.f, 59.f );

			g_imgui.render_tab( _( "visuals" ), 2 );
			g_imgui.same_line( 0.f, 59.f );

			g_imgui.render_tab( _( "misc" ), 3 );
			g_imgui.same_line( 0.f, 59.f );

			g_imgui.render_tab( _( "skins" ), 4 );
			g_imgui.same_line( 0.f, 59.f );

			g_imgui.render_tab( _( "config" ), 5 );

			g_imgui.end_child( );
		}

		switch ( g_menu.menu_tab ) {
		case 0: { /* aimbot tab */
			g_imgui.begin_child( _( "aimbot-main-child-contents" ),
			                     ImVec2( g_imgui.get_content_region_avail( ).x / 2, g_imgui.get_content_region_avail( ).y ) );
			{
				g_imgui.separator( window_draw_list,
				                   ImVec2( ImGui::GetWindowPos( ).x + g_imgui.calc_text_size( _( "general" ) ).x + 10, ImGui::GetWindowPos( ).y + 5 ),
				                   ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetContentRegionAvail( ).x, ImGui::GetWindowPos( ).y + 5 + 1 ),
				                   _( "general" ) );

				g_imgui.end_child( );
			}

			break;
		}
		case 1: { /* anti aim tab */
			g_imgui.begin_child( _( "anti-aim-child-contents" ),
			                     ImVec2( g_imgui.get_content_region_avail( ).x / 2, g_imgui.get_content_region_avail( ).y ) );
			{
				g_imgui.separator( window_draw_list,
				                   ImVec2( ImGui::GetWindowPos( ).x + g_imgui.calc_text_size( _( "general" ) ).x + 10, ImGui::GetWindowPos( ).y + 5 ),
				                   ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetContentRegionAvail( ).x, ImGui::GetWindowPos( ).y + 5 + 1 ),
				                   _( "general" ) );

				g_imgui.end_child( );
			}

			g_imgui.same_line( );

			g_imgui.begin_child( _( "exploits-child-contents" ),
			                     ImVec2( g_imgui.get_content_region_avail( ).x, g_imgui.get_content_region_avail( ).y ) );
			{
				g_imgui.separator(
					window_draw_list,
					ImVec2( ImGui::GetWindowPos( ).x + g_imgui.calc_text_size( _( "exploits" ) ).x + 10, ImGui::GetWindowPos( ).y + 5 ),
					ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetContentRegionAvail( ).x, ImGui::GetWindowPos( ).y + 5 + 1 ), _( "exploits" ) );

				g_imgui.spacing( );
				g_imgui.end_child( );
			}
			break;
		}
		case 2: { /* visuals tab */
			g_imgui.begin_child( _( "esp-child-contents" ),
			                     ImVec2( g_imgui.get_content_region_avail( ).x / 2, g_imgui.get_content_region_avail( ).y ) );
			{
				g_imgui.separator(
					window_draw_list, ImVec2( ImGui::GetWindowPos( ).x + g_imgui.calc_text_size( _( "esp" ) ).x + 10, ImGui::GetWindowPos( ).y + 5 ),
					ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetContentRegionAvail( ).x, ImGui::GetWindowPos( ).y + 5 + 1 ), _( "esp" ) );

				g_imgui.end_child( );
			}

			g_imgui.same_line( );

			g_imgui.begin_child( _( "chams-child-contents" ),
			                     ImVec2( g_imgui.get_content_region_avail( ).x, g_imgui.get_content_region_avail( ).y / 2 ) );
			{
				g_imgui.separator(
					window_draw_list,
					ImVec2( ImGui::GetWindowPos( ).x + g_imgui.calc_text_size( _( "chams" ) ).x + 10, ImGui::GetWindowPos( ).y + 5 ),
					ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetContentRegionAvail( ).x, ImGui::GetWindowPos( ).y + 5 + 1 ), _( "chams" ) );

				g_imgui.end_child( );
			}

			g_imgui.same_line( );

			g_imgui.begin_child( _( "world-child-contents" ),
			                     ImVec2( g_imgui.get_content_region_avail( ).x, g_imgui.get_content_region_avail( ).y ) );
			{
				g_imgui.separator(
					window_draw_list, ImVec2( ImGui::GetWindowPos( ).x + g_imgui.calc_text_size( _( "glow" ) ).x + 10, ImGui::GetWindowPos( ).y + 5 ),
					ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetContentRegionAvail( ).x, ImGui::GetWindowPos( ).y + 5 + 1 ), _( "world" ) );

				g_imgui.end_child( );
			}
			break;
		}
		case 3: { /* misc tab */
			g_imgui.begin_child( _( "movement-child-contents" ),
			                     ImVec2( g_imgui.get_content_region_avail( ).x / 2, g_imgui.get_content_region_avail( ).y ) );
			{
				g_imgui.separator(
					window_draw_list,
					ImVec2( ImGui::GetWindowPos( ).x + g_imgui.calc_text_size( _( "movement" ) ).x + 10, ImGui::GetWindowPos( ).y + 5 ),
					ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetContentRegionAvail( ).x, ImGui::GetWindowPos( ).y + 5 + 1 ), _( "movement" ) );

				g_imgui.checkbox( _( "auto bhop" ), &g_config.find< bool >( HASH( "m_bh" ) ) );
				g_imgui.checkbox( _( "auto jumpbug" ), &g_config.find< bool >( HASH( "m_jb" ) ) );
				g_imgui.keybind( _( "auto jumpbug key" ), &g_config.find< int >( HASH( "m_jb_key" ) ), 15 );
				g_imgui.checkbox( _( "edge jump" ), &g_config.find< bool >( HASH( "m_ej" ) ) );
				g_imgui.keybind( _( "edge jump key" ), &g_config.find< int >( HASH( "m_ej_key" ) ), 15 );
				if ( g_config.find< bool >( HASH( "m_ej" ) ) )
					g_imgui.checkbox( _( "long jump" ), &g_config.find< bool >( HASH( "m_lj" ) ), 15 );

				g_imgui.checkbox( _( "mini jump" ), &g_config.find< bool >( HASH( "m_mj" ) ) );
				g_imgui.keybind( _( "mini jump key" ), &g_config.find< int >( HASH( "m_mj_key" ) ), 15 );
				g_imgui.checkbox( _( "fast duck" ), &g_config.find< bool >( HASH( "m_fast_duck" ) ) );
				g_imgui.checkbox( _( "auto align" ), &g_config.find< bool >( HASH( "m_auto_align" ) ) );

				g_imgui.end_child( );
			}

			g_imgui.same_line( );

			g_imgui.begin_child( _( "indicators-child-contents" ),
			                     ImVec2( g_imgui.get_content_region_avail( ).x, g_imgui.get_content_region_avail( ).y / 2 ) );
			{
				g_imgui.separator(
					window_draw_list,
					ImVec2( ImGui::GetWindowPos( ).x + g_imgui.calc_text_size( _( "indicators" ) ).x + 10, ImGui::GetWindowPos( ).y + 5 ),
					ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetContentRegionAvail( ).x, ImGui::GetWindowPos( ).y + 5 + 1 ), _( "indicators" ) );

				/* todo - coffin - check if custom clr is on, then render 1 clr picker, else do 3 negative, positive, neutral */
				g_imgui.checkbox( _( "velocity##indicator" ), &g_config.find< bool >( HASH( "m_velocity_indicator" ) ) );
				if ( g_config.find< bool >( HASH( "m_velocity_indicator" ) ) ) {
					g_imgui.checkbox( _( "show pre##velocity" ), &g_config.find< bool >( HASH( "m_velocity_indicator_show_pre" ) ), 15 );
					g_imgui.checkbox( _( "fade##velocity" ), &g_config.find< bool >( HASH( "m_velocity_indicator_fade" ) ), 15 );
				}

				g_imgui.checkbox( _( "stamina##indicator" ), &g_config.find< bool >( HASH( "m_stamina_indicator" ) ) );
				if ( g_config.find< bool >( HASH( "m_stamina_indicator" ) ) ) { }

				g_imgui.checkbox( _( "keybinds" ), &g_config.find< bool >( HASH( "m_keybind_indicator" ) ) );
				//has to be multibox. ik
				ImGui::Combo( _( "displayed keybinds" ), &g_config.find< int >( HASH( "m_displayed_keybinds" ) ), _( "jb\0ej\0ej\0mj" ) );

				g_imgui.spacing( );
				g_imgui.end_child( );
			}

			g_imgui.set_cursor_pos( ImVec2( g_imgui.get_content_region_avail( ).x / 2 + 15, 258 ) );

			g_imgui.begin_child( _( "game-child-contents" ), ImVec2( g_imgui.get_content_region_avail( ).x, g_imgui.get_content_region_avail( ).y ) );
			{
				g_imgui.separator(
					window_draw_list, ImVec2( ImGui::GetWindowPos( ).x + g_imgui.calc_text_size( _( "game" ) ).x + 10, ImGui::GetWindowPos( ).y + 5 ),
					ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetContentRegionAvail( ).x, ImGui::GetWindowPos( ).y + 5 + 1 ), _( "game" ) );

				g_imgui.spacing( );
				g_imgui.end_child( );
			}
			break;
		}
		case 4: { /* skins tab */
			break;
		}
		case 5: { /* config tab */
			g_imgui.begin_child( _( "configuration-child-contents" ),
			                     ImVec2( g_imgui.get_content_region_avail( ).x, g_imgui.get_content_region_avail( ).y ) );
			{
				g_imgui.separator( window_draw_list,
				                   ImVec2( ImGui::GetWindowPos( ).x + g_imgui.calc_text_size( _( "config" ) ).x + 10, ImGui::GetWindowPos( ).y + 5 ),
				                   ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetContentRegionAvail( ).x, ImGui::GetWindowPos( ).y + 5 + 1 ),
				                   _( "config" ) );

				g_imgui.end_child( );
			}
			break;
		}
		}
	}

	g_imgui.end( );
}
