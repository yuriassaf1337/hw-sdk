#pragma once

namespace indicators
{
	struct impl {
		void think( );
		void velocity( );
		void stamina( );
	};
} // namespace indicators

inline indicators::impl g_indicators;
