
namespace hooks
{
	// pointers
	inline detour::hook create_move;

	// fns
	using create_move_fn = bool( __thiscall* )( sdk::c_cs_player*, float, sdk::c_user_cmd* );

	// functions
	struct detours {
		static bool __fastcall create_move( sdk::c_cs_player* ecx, void*, float input_sample_time, sdk::c_user_cmd* cmd );
	};
} // namespace hooks