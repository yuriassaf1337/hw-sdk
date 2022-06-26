#include "menu.h"

#include "window/tab/group/objects/checkbox.h"
#include "window/tab/group/objects/slider_float.h"
#include "window/tab/group/objects/slider_int.h"

#include "window/window.h"

static auto main_window = new menu::window{ };

bool menu::impl::init( )
{
	// blame liga
	static auto aimbot  = new menu::tab{ main_window, _( "aimbot" ) };
	static auto visuals = new menu::tab{ main_window, _( "visuals" ) };
	static auto misc    = new menu::tab{ main_window, _( "misc" ) };
	static auto config  = new menu::tab{ main_window, _( "config" ) };

	// TODO: move these to cfg init(or maybe leave here i dont mind tbh)
	g_config.insert( _( "menu_color" ), config::option( color( 67, 0, 187 ) ) );

	g_config.insert( _( "menu_size_x" ), config::option( 550, 0, 0 ) );
	g_config.insert( _( "menu_size_y" ), config::option( 500, 0, 0 ) );

	g_config.insert( _( "buffer_value_bool_1" ), config::option( false ) );
	g_config.insert( _( "buffer_value_int_1" ), config::option( 12, 0, 100 ) );
	g_config.insert( _( "buffer_value_bool_2" ), config::option( false ) );
	g_config.insert( _( "buffer_value_int_2" ), config::option( 12, 0, 100 ) );
	g_config.insert( _( "buffer_value_bool_3" ), config::option( false ) );
	g_config.insert( _( "buffer_value_int_3" ), config::option( 12, 0, 100 ) );

	g_config.insert( _( "buffer_value_float_1" ), config::option( 12.f, 0.f, 100.f ) );

	g_config.insert( _( "buffer_keybind_1" ), config::option( 'V', 0, 0 ) );

	g_config.insert( _( "m_bh" ), config::option( false ) );
	g_config.insert( _( "m_jb" ), config::option( false ) );
	g_config.insert( _( "m_jb_key" ), config::option( 0, 0, 0 ) );

	g_config.insert( _( "m_ej" ), config::option( false ) );
	g_config.insert( _( "m_ej_key" ), config::option( 0, 0, 0 ) );
	g_config.insert( _( "m_lj" ), config::option( false ) );

	g_config.insert( _( "m_mj" ), config::option( false ) );
	g_config.insert( _( "m_mj_key" ), config::option( 0, 0, 0 ) );
	g_config.insert( _( "m_fastduck" ), config::option( false ) );

	{
		static auto group1 = new menu::group{ aimbot, std::string( "group1" ), static_cast< int >( group_position::GROUP_LEFT ), false };
		static auto group2 = new menu::group{ aimbot, std::string( "group2" ), static_cast< int >( group_position::GROUP_LEFT ), false };
		static auto group3 = new menu::group{ aimbot, std::string( "group3" ), static_cast< int >( group_position::GROUP_RIGHT ), true };

		static auto checkbox1 = new menu::check_box{ group1, HASH( "buffer_value_bool_1" ), _( "test" ) };
		checkbox1->add_keybind( HASH( "buffer_keybind_1" ) );

		static auto slider1   = new menu::slider_int{ group1, HASH( "buffer_value_int_1" ), _( "test" ) };
		static auto checkbox2 = new menu::check_box{ group1, HASH( "buffer_value_bool_2" ), _( "test" ) };
		checkbox2->add_color_picker( HASH( "menu_color" ) );

		static auto slider2   = new menu::slider_int{ group1, HASH( "buffer_value_int_2" ), _( "test" ) };
		static auto checkbox3 = new menu::check_box{ group1, HASH( "buffer_value_bool_3" ), _( "test" ) };
		checkbox3->add_color_picker( HASH( "menu_color" ) );

		static auto slider3 = new menu::slider_int{ group1, HASH( "buffer_value_int_3" ), _( "test" ) };
		static auto slider4 = new menu::slider_float{ group1, HASH( "buffer_value_float_1" ), _( "test" ) };

		group1->objects.push_back( checkbox1 );
		group1->objects.push_back( slider1 );
		group1->objects.push_back( checkbox2 );
		group1->objects.push_back( slider2 );
		group1->objects.push_back( checkbox3 );
		group1->objects.push_back( slider3 );
		group1->objects.push_back( slider4 );
		group1->objects.push_back( checkbox1 );
		group1->objects.push_back( slider1 );
		group1->objects.push_back( checkbox2 );
		group1->objects.push_back( slider2 );
		group1->objects.push_back( checkbox3 );
		group1->objects.push_back( slider3 );
		group1->objects.push_back( slider4 );

		aimbot->groups.push_back( group1 );
		aimbot->groups.push_back( group2 );
		aimbot->groups.push_back( group3 );
	}
	// vis
	{

	}

	// misc
	{
		enum misc_groups_t : int {
			MOVEMENT = 0,
			INDICATORS,
			GAME
		};

		// groups
		static std::vector< menu::group* > misc_tab_groups = { new menu::group{ misc, _( "movement" ), group_position::GROUP_LEFT, true },
			                                                   new menu::group{ misc, _( "indicators" ), group_position::GROUP_RIGHT, false },
			                                                   new menu::group{ misc, _( "game" ), group_position::GROUP_RIGHT, false } };

		// misc-movement
		{
			static auto bh = new menu::check_box{ misc_tab_groups[ misc_groups_t::MOVEMENT ], HASH( "m_bh" ), _( "auto bhop" ) };

			static auto jb = new menu::check_box{ misc_tab_groups[ misc_groups_t::MOVEMENT ], HASH( "m_jb" ), _( "auto jumpbug" ) };
			jb->add_keybind( HASH( "m_jb_key" ) );

			static auto ej = new menu::check_box{ misc_tab_groups[ misc_groups_t::MOVEMENT ], HASH( "m_ej" ), _( "edge jump" ) };
			ej->add_keybind( HASH( "m_ej_key" ) );

			static auto lj = new menu::check_box{ misc_tab_groups[ misc_groups_t::MOVEMENT ], HASH( "m_lj" ), _( "long jump" ) };

			static auto mj = new menu::check_box{ misc_tab_groups[ misc_groups_t::MOVEMENT ], HASH( "m_mj" ), _( "mini jump" ) };
			mj->add_keybind( HASH( "m_mj_key" ) );

			static auto fd = new menu::check_box{ misc_tab_groups[ misc_groups_t::MOVEMENT ], HASH( "m_fastduck" ), _( "fast duck" ) };

			misc_tab_groups[ misc_groups_t::MOVEMENT ]->objects.push_back( bh );
			misc_tab_groups[ misc_groups_t::MOVEMENT ]->objects.push_back( jb );
			misc_tab_groups[ misc_groups_t::MOVEMENT ]->objects.push_back( ej );
			misc_tab_groups[ misc_groups_t::MOVEMENT ]->objects.push_back( lj );
			misc_tab_groups[ misc_groups_t::MOVEMENT ]->objects.push_back( mj );
			misc_tab_groups[ misc_groups_t::MOVEMENT ]->objects.push_back( fd );
		}

		for ( auto group : misc_tab_groups )
			misc->groups.push_back( group );
	}

	main_window->tabs.push_back( aimbot );
	main_window->tabs.push_back( visuals );
	main_window->tabs.push_back( misc );
	main_window->tabs.push_back( config );

	g_input.add_keybind( VK_INSERT, [ & ]( bool pressed ) {
		if ( pressed )
			menu_open = !menu_open;
	} );

	g_input.add_keybind( VK_HOME, [ & ]( bool pressed ) {
		if ( pressed )
			g_config.save( "test.json" );
	} );

	g_input.add_keybind( VK_END, [ & ]( bool pressed ) {
		if ( pressed )
			g_config.load( "test.json" );
	} );

	return true;
}

void menu::impl::draw( )
{
	if ( !menu_open )
		return;

	auto menu_size_x = g_config.find< int >( HASH( "menu_size_x" ) );
	auto menu_size_y = g_config.find< int >( HASH( "menu_size_y" ) );

	static auto menu_position_x = g_ctx.screen_size.x / 2 - menu_size_x / 2;
	static auto menu_position_y = g_ctx.screen_size.y / 2 - menu_size_y / 2;

	main_window->draw( menu_position_x, menu_position_y, menu_size_x, menu_size_y );
	main_window->input( menu_position_x, menu_position_y, menu_size_x, menu_size_y );
}
