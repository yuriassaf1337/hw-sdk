#ifndef FRAME_STAGE_H
#define FRAME_STAGE_H

namespace sdk::enums
{
	enum class frame_stage
	{
		UNDEFINED = -1,
		START,
		NET_UPDATE_START,
		NET_UPDATE_POSTDATAUPDATE_START,
		NET_UPDATE_POSTDATAUPDATE_END,
		NET_UPDATE_END,
		RENDER_START,
		RENDER_END
	};
} // namespace sdk::enums

#endif
