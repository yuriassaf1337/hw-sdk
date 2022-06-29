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

	g_imgui.begin( _( "dreamhak-main-window" ), nullptr,
	               ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar );
	{
		ImDrawList* window_draw_list = ImGui::GetWindowDrawList( );

		g_imgui.start_decorations( window_draw_list );

		g_imgui.spacing( 2 );

		g_imgui.begin_child( _( "tabs-child" ), ImVec2( -1, 30 ), true, 0 );
		{
			g_imgui.render_tab( _( "aimbot" ), 0 );
			g_imgui.same_line( 0.f, 80.f );

			g_imgui.render_tab( _( "visuals" ), 1 );
			g_imgui.same_line( 0.f, 80.f );

			g_imgui.render_tab( _( "misc" ), 2 );
			g_imgui.same_line( 0.f, 80.f );

			g_imgui.render_tab( _( "recorder" ), 3 );
			g_imgui.same_line( 0.f, 80.f );

			g_imgui.render_tab( _( "config" ), 4 );
			g_imgui.end_child( );
		}

		switch ( g_menu.menu_tab ) {
		case 0: { /* aimbot tab */
			break;
		}
		case 1: { /* visuals tab */
			break;
		}
		case 2: { /* misc tab */

			g_imgui.begin_child( _( "movement-child-header" ), ImVec2( g_imgui.get_content_region_avail( ).x / 2, 13 ) );
			{
				g_imgui.set_cursor_pos_x( g_imgui.get_content_region_avail( ).x / 2 - g_imgui.calc_text_size( _( "movement" ) ).x / 2 );
				g_imgui.text( _( "movement" ) );
				g_imgui.end_child( );
			}

			g_imgui.same_line( );

			g_imgui.begin_child( _( "indicators-child-header" ), ImVec2( g_imgui.get_content_region_avail( ).x, 13 ) );
			{
				g_imgui.set_cursor_pos_x( g_imgui.get_content_region_avail( ).x / 2 - g_imgui.calc_text_size( _( "indicators" ) ).x / 2 );
				g_imgui.text( _( "indicators" ) );
				g_imgui.end_child( );
			}

			g_imgui.begin_child( _( "movement-child-contents" ),
			                     ImVec2( g_imgui.get_content_region_avail( ).x / 2, g_imgui.get_content_region_avail( ).y - 200 ) );
			{
				g_imgui.spacing( );

				g_imgui.checkbox( _( "auto bhop" ), &g_config.find< bool >( HASH( "m_bh" ) ) );
				g_imgui.checkbox( _( "auto jumpbug" ), &g_config.find< bool >( HASH( "m_jb" ) ) );
				g_imgui.keybind( _( "auto jumpbug key" ), &g_config.find< int >( HASH( "m_jb_key" ) ), 15 );
				g_imgui.checkbox( _( "edge jump" ), &g_config.find< bool >( HASH( "m_ej" ) ) );
				g_imgui.keybind( _( "edge jump key" ), &g_config.find< int >( HASH( "m_ej_key" ) ), 15 );
				g_imgui.checkbox( _( "long jump" ), &g_config.find< bool >( HASH( "m_lj" ) ) );
				g_imgui.checkbox( _( "mini jump" ), &g_config.find< bool >( HASH( "m_mj" ) ) );
				g_imgui.keybind( _( "mini jump key" ), &g_config.find< int >( HASH( "m_mj_key" ) ), 1154 );
				g_imgui.checkbox( _( "fast duck" ), &g_config.find< bool >( HASH( "m_fastduck" ) ) );

				g_imgui.end_child( );
			}

			g_imgui.same_line( );

			g_imgui.begin_child( _( "indicators-child-contents" ),
			                     ImVec2( g_imgui.get_content_region_avail( ).x, g_imgui.get_content_region_avail( ).y - 200 ) );
			{
				g_imgui.spacing( );
				g_imgui.end_child( );
			}

			g_imgui.begin_child( _( "game-child-header" ), ImVec2( g_imgui.get_content_region_avail( ).x, 13 ) );
			{
				g_imgui.set_cursor_pos_x( g_imgui.get_content_region_avail( ).x / 2 - g_imgui.calc_text_size( _( "game" ) ).x / 2 );
				g_imgui.text( _( "game" ) );
				g_imgui.end_child( );
			}

			g_imgui.begin_child( _( "game-child-contents" ), ImVec2( g_imgui.get_content_region_avail( ).x, g_imgui.get_content_region_avail( ).y ) );
			{
				g_imgui.spacing( );
				g_imgui.end_child( );
			}
			break;
		}
		case 3: { /* recorder tab */
			break;
		}
		case 4: { /* config tab */
			break;
		}
		}
	}

	g_imgui.end( );
}
