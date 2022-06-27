#include "menu.h"
#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_freetype.h"
#include "../../dependencies/imgui/imgui_impl_dx9.h"
#include "../../dependencies/imgui/imgui_impl_win32.h"
#include "../../globals/interfaces/interfaces.h"
#include "../../utils/keybinds/keybinds.h"

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

	/* add fonts here */

	menu_initialised = ImGuiFreeType::BuildFontAtlas( io.Fonts, 0x0 );
}

void menu::impl::draw( )
{
	if ( !menu_open )
		return;

	ImGui::SetNextWindowSize( ImVec2( 500, 400 ), ImGuiCond_Always );
	ImGui::Begin( _( "dreamhak-main-window" ), nullptr,
	              ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar );
	{
		ImGui::Text( "Hello, world!" );

		/* todo - coffin - orginise menu tommorrow, just adding the checkboxes from before */

		ImGui::Checkbox( _( "bhop" ), &g_config.find< bool >( HASH( "m_bh" ) ) );
	}
	ImGui::End( );
}
