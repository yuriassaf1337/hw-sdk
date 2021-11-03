#ifndef MOVE_TYPE_H
#define MOVE_TYPE_H

namespace sdk::enums
{
	enum class move_type
	{
		NONE = 0,
		ISOMETRIC,
		WALK,
		STEP,
		FLY,
		FLYGRAVITY,
		VPHYSICS,
		PUSH,
		NOCLIP,
		LADDER,
		OBSERVER,
		CUSTOM,
		LAST     = CUSTOM,
		MAX_BITS = 4
	};
} // namespace sdk::enums

#endif
