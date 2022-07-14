
namespace hooks
{
	inline WNDPROC wnd_proc;

	// pointers
	inline detour::hook create_move;
	inline detour::hook send_net_msg;

	// fns
	using create_move_fn = bool( __thiscall* )( sdk::c_cs_player*, float, sdk::c_user_cmd* );

	// functions
	struct detours {
		static LONG WINAPI wnd_proc( HWND window, UINT message, WPARAM parameter, LPARAM long_parameter );

		static bool __fastcall create_move( sdk::c_cs_player* ecx, void*, float input_sample_time, sdk::c_user_cmd* cmd );

		static bool __stdcall ret_add( LPCSTR );

		static bool __fastcall send_net_msg( void* ecx, void* edx, sdk::i_net_msg* net_message, bool reliable, bool voice );
	};

	// ret_add hooks
	namespace ret_add
	{
		inline detour::hook return_address_hook_client;
		inline detour::hook return_address_hook_engine;
		inline detour::hook return_address_hook_studio;
		inline detour::hook return_address_hook_material;

		static bool init( )
		{
			HOOK( hooks::ret_add::return_address_hook_client.create( g_client_dll.pattern_scan( _( "55 8B EC 56 8B F1 33 C0 57" ) ).as< void* >( ),
			                                                         &hooks::detours::ret_add ) );

			HOOK( hooks::ret_add::return_address_hook_engine.create( g_engine_dll.pattern_scan( _( "55 8B EC 56 8B F1 33 C0 57" ) ).as< void* >( ),
			                                                         &hooks::detours::ret_add ) );

			HOOK( hooks::ret_add::return_address_hook_studio.create(
				g_studio_render_dll.pattern_scan( _( "55 8B EC 56 8B F1 33 C0 57" ) ).as< void* >( ), &hooks::detours::ret_add ) );

			HOOK( hooks::ret_add::return_address_hook_material.create(
				g_material_system_dll.pattern_scan( _( "55 8B EC 56 8B F1 33 C0 57" ) ).as< void* >( ), &hooks::detours::ret_add ) );

			return true;
		};
	}
} // namespace hooks