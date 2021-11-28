#include "movement.h"

void movement::impl::bhop( )
{
	// will return if player is noclip/ladder/fly mode
	[[unlikely]] if ( g_ctx.local->move_type( ).has_any_of(
						  { sdk::move_type::MOVE_NOCLIP, sdk::move_type::MOVE_LADDER, sdk::move_type::MOVE_FLY } ) ) return;

	// remove jump flag if player in air
	if ( !g_ctx.local->flags( ).has( sdk::flags::ONGROUND ) )
		g_ctx.cmd->buttons.add( sdk::buttons::IN_JUMP );
}
