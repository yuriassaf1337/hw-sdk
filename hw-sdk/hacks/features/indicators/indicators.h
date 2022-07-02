#pragma once

namespace indicators
{
	struct impl {
		void reset_data( );
		void render( );
		void velocity( );
		void stamina( );
	};
} // namespace indicators

inline indicators::impl g_indicators;
