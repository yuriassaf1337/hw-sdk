#include "menu.h"
#include "../../dependencies/imgui/dx9/imgui_impl_dx9.h"
#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_freetype.h"
#include "../../dependencies/imgui/imgui_impl_win32.h"
#include "../../globals/interfaces/interfaces.h"
#include "../../utils/keybinds/keybinds.h"

/* WAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA */
auto color_picker = []( const char* label, color* col, bool alpha, int sameline, bool show_text ) {
	if ( show_text )
		ImGui::Text( label );

	ImVec4 output_color = col->to_imvec4( );

	auto alpha_slider_flag = alpha ? ImGuiColorEditFlags_AlphaBar : ImGuiColorEditFlags_NoAlpha;
	ImGui::SameLine( ImGui::GetWindowWidth( ) - sameline );

	if ( ImGui::ColorEdit4( std::string( _( "##" ) ).append( label ).c_str( ), &output_color.x,
	                        alpha_slider_flag | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip ) ) {
		*col = color( output_color.x, output_color.y, output_color.z, output_color.w );
		return true;
	}

	return false;
};

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

void menu::impl::init( IDirect3DDevice9* device )
{
	ImGui::CreateContext( );

	ImGui_ImplWin32_Init( this->window );
	ImGui_ImplDX9_Init( device );

	ImGuiStyle& style = ImGui::GetStyle( );
	ImGuiIO& io       = ImGui::GetIO( );

	/* colors */
	{
		style.Colors[ ImGuiCol_Border ] = ImVec4( 30 / 255.f, 30 / 255.f, 30 / 255.f, 0.5f );

		style.Colors[ ImGuiCol_ScrollbarBg ]          = ImVec4( 1.f, 1.f, 1.f, 1.f );
		style.Colors[ ImGuiCol_ScrollbarGrab ]        = ImVec4( 1.f, 1.f, 1.f, 1.f );
		style.Colors[ ImGuiCol_ScrollbarGrabActive ]  = ImVec4( 1.f, 1.f, 1.f, 1.f );
		style.Colors[ ImGuiCol_ScrollbarGrabHovered ] = ImVec4( 1.f, 1.f, 1.f, 1.f );

		style.Colors[ ImGuiCol_WindowBg ] = ImVec4( 10 / 255.f, 10 / 255.f, 10 / 255.f, 1.00f );
		style.Colors[ ImGuiCol_PopupBg ]  = ImVec4( 20 / 255.f, 20 / 255.f, 20 / 255.f, 1.00f );
		style.Colors[ ImGuiCol_ChildBg ]  = ImVec4( 15 / 255.f, 15 / 255.f, 15 / 255.f, 1.0f );

		style.Colors[ ImGuiCol_FrameBg ] = g_config.find< color >( HASH( "menu_color" ) ).to_imvec4( );
	}

	/* style */
	{
		style.WindowRounding    = 3.f;
		style.ChildRounding     = 2.f;
		style.FrameRounding     = 2.f;
		style.GrabRounding      = 2.f;
		style.PopupRounding     = 2.f;
		style.ScrollbarRounding = 4.f;
		style.TabRounding       = 3.f;

		style.WindowBorderSize = 2.f;
		style.FrameBorderSize  = 0.f;
		style.ChildBorderSize  = 1.;

		style.ScrollbarSize = 1.f;

		style.FramePadding     = ImVec2( 4, -1 );
		style.WindowPadding    = ImVec2( 8, 8 );
		style.ItemSpacing      = ImVec2( 8, 4 );
		style.ItemInnerSpacing = ImVec2( 4, 4 );
		style.WindowMinSize    = ImVec2( 32, 32 );
		style.WindowTitleAlign = ImVec2( 0.5f, 0.5f );
		style.ButtonTextAlign  = ImVec2( 0.5f, 0.4f );

		style.Alpha = 1.f;
	}

	/* add fonts here */
	ImFontConfig im_tahoma_font_config    = { };
	im_tahoma_font_config.RasterizerFlags = ImGuiFreeType::Monochrome | ImGuiFreeType::MonoHinting;
	this->menu_font                       = io.Fonts->AddFontFromFileTTF( _( "C:\\Windows\\Fonts\\Tahoma.ttf" ), 12.f, &im_tahoma_font_config );

	this->menu_initialised = ImGuiFreeType::BuildFontAtlas( io.Fonts, 0x0 );
}

void menu::impl::draw( )
{
	if ( !menu_open )
		return;

	ImGui::SetNextWindowSize( ImVec2( 500, 450 ), ImGuiCond_Always );
	ImGui::Begin( _( "dreamhak-main-window" ), nullptr,
	              ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar );
	{
		ImDrawList* window_draw_list = ImGui::GetWindowDrawList( );

		auto render_decorations = [ & ]( ) {
			window_draw_list->AddRectFilledMultiColor(
				ImVec2( ImGui::GetWindowPos( ).x, ImGui::GetWindowPos( ).y + 25 ),
				ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetWindowSize( ).x / 2, ImGui::GetWindowPos( ).y + 25 + 1 ),
				g_config.find< color >( HASH( "menu_color" ) ).get_u32( 0.f ), g_config.find< color >( HASH( "menu_color" ) ).get_u32( ),
				g_config.find< color >( HASH( "menu_color" ) ).get_u32( ), g_config.find< color >( HASH( "menu_color" ) ).get_u32( 0.f ) );

			window_draw_list->AddRectFilledMultiColor(
				ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetWindowSize( ).x / 2, ImGui::GetWindowPos( ).y + 25 ),
				ImVec2( ( ImGui::GetWindowPos( ).x + ImGui::GetWindowSize( ).x / 2 ) + ImGui::GetWindowSize( ).x / 2,
			            ImGui::GetWindowPos( ).y + 25 + 1 ),
				g_config.find< color >( HASH( "menu_color" ) ).get_u32( ), g_config.find< color >( HASH( "menu_color" ) ).get_u32( 0.f ),
				g_config.find< color >( HASH( "menu_color" ) ).get_u32( 0.f ), g_config.find< color >( HASH( "menu_color" ) ).get_u32( ) );

			ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 - ImGui::CalcTextSize( _( "smegma.hack" ) ).x / 2 );
			ImGui::Text( _( "smegma" ) );
			ImGui::SameLine( 0, 0 );
			ImGui::TextColored( g_config.find< color >( HASH( "menu_color" ) ).to_imvec4( ), _( ".hack" ) );
		};

		render_decorations( );

		ImGui::Spacing( );
		ImGui::Spacing( );

		ImGui::BeginChild( _( "tabs-child" ), ImVec2( -1, 30 ), true );
		{
			ImGui::RenderTab( _( "aimbot" ), 0 );
			ImGui::SameLine( 0.f, 80.f );
			ImGui::RenderTab( _( "visuals" ), 1 );
			ImGui::SameLine( 0.f, 80.f );
			ImGui::RenderTab( _( "misc" ), 2 );
			ImGui::SameLine( 0.f, 80.f );
			ImGui::RenderTab( _( "recorder" ), 3 );
			ImGui::SameLine( 0.f, 80.f );
			ImGui::RenderTab( _( "config" ), 4 );
			ImGui::EndChild( );
		}

		switch ( g_menu.menu_tab ) {
		case 0: { /* aimbot tab */
			break;
		}
		case 1: { /* visuals tab */
			break;
		}
		case 2: { /* misc tab */
			ImGui::BeginChild( _( "movement-child-header" ), ImVec2( ImGui::GetContentRegionAvail( ).x / 2, 13 ) );
			{
				ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 - ImGui::CalcTextSize( _( "movement" ) ).x / 2 );
				ImGui::Text( _( "movement" ) );
				ImGui::EndChild( );
			}

			ImGui::SameLine( );

			ImGui::BeginChild( _( "indicators-child-header" ), ImVec2( ImGui::GetContentRegionAvail( ).x, 13 ) );
			{
				ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 - ImGui::CalcTextSize( _( "indicators" ) ).x / 2 );
				ImGui::Text( _( "indicators" ) );
				ImGui::EndChild( );
			}

			ImGui::BeginChild( _( "movement-child-contents" ),
			                   ImVec2( ImGui::GetContentRegionAvail( ).x / 2, ImGui::GetContentRegionAvail( ).y - 200 ) );
			{
				ImGui::Spacing( );
				ImGui::Checkbox( _( "auto bhop" ), &g_config.find< bool >( HASH( "m_bh" ) ) );
				ImGui::Checkbox( _( "auto jumpbug" ), &g_config.find< bool >( HASH( "m_jb" ) ) );
				ImGui::Keybind( _( "auto jumpbug key" ), &g_config.find< int >( HASH( "m_jb_key" ) ), 14 );
				ImGui::EndChild( );
			}

			ImGui::SameLine( );

			ImGui::BeginChild( _( "indicators-child-contents" ),
			                   ImVec2( ImGui::GetContentRegionAvail( ).x, ImGui::GetContentRegionAvail( ).y - 200 ) );
			{
				ImGui::Spacing( );
				ImGui::EndChild( );
			}

			ImGui::BeginChild( _( "game-child-header" ), ImVec2( ImGui::GetContentRegionAvail( ).x, 13 ) );
			{
				ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 - ImGui::CalcTextSize( _( "game" ) ).x / 2 );
				ImGui::Text( _( "game" ) );
				ImGui::EndChild( );
			}

			ImGui::BeginChild( _( "game-child-contents" ),
			                   ImVec2( ImGui::GetContentRegionAvail( ).x, ImGui::GetContentRegionAvail( ).y ) );
			{
				ImGui::Spacing( );
				ImGui::EndChild( );
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
	ImGui::End( );
}