#pragma once
#include <string>
#include <vector>

namespace gui::tabs
{
	struct impl {
		void think( const std::vector< std::string_view >& feeder );
	};
} // namespace gui::tabs

inline gui::tabs::impl g_tabs;
