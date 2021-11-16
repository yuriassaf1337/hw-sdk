#pragma once

#include "../../../utils/math/types/vector.h"
#include "../utils/utils.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <deque>
#include <map>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace gui::pallete
{
	// full black
	static inline color first_outline( const float alpha = g_gui.main.alpha )
	{
		return color( 0, 0, 0, alpha );
	}
	// light grey
	static inline color second_outline( const float alpha = g_gui.main.alpha )
	{
		return color( 54, 54, 54, alpha );
	}
	// dark grey
	static inline color third_outline( const float alpha = g_gui.main.alpha )
	{
		return color( 38, 34, 38, alpha );
	}
} // namespace gui::pallete
