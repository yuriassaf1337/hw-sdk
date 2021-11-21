#pragma once

namespace sdk
{
	struct i_client_unknown {
	};

	struct i_client_renderable {
	};

	struct i_client_networkable {
	};

	struct i_client_thinkable {
	};

	struct i_client_entity : public i_client_unknown, public i_client_renderable, public i_client_networkable, public i_client_thinkable {
	};
} // namespace sdk
