#pragma once

namespace sdk
{
	enum class net_channel_type
	{
		GENERIC = 0,
		LOCALPLAYER,
		OTHERPLAYERS,
		ENTITIES,
		SOUNDS,
		EVENTS,
		USERMESSAGES,
		ENTMESSAGES,
		VOICE,
		STRINGTABLE,
		MOVE,
		STRINGCMD,
		SIGNON,
		TOTAL,
	};
} // namespace sdk
