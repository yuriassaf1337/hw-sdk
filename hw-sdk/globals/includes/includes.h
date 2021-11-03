#ifndef INCLUDES_H
#define INCLUDES_H

// libs
#include <Windows.h>
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <d3d9.h>
#include <exception>
#include <filesystem>
#include <fstream>
#include <functional>
#include <intrin.h>
#include <iosfwd>
#include <mutex>
#include <process.h>
#include <sstream>
#include <stdexcept>
#include <tchar.h>
#include <thread>

// string enc/xor float
#include "../../dependencies/hash/hash.h"
#include "../../dependencies/xor/xor.h"

// helpers
#include "../../utils/helpers/bit_flag.h"
#include "../../utils/helpers/primitive_definitions/primitives.h"

// utils
#include "../../utils/console/console.h"
#include "../../utils/utils.h"

// g_csgo global
#include "../../globals/csgo.h"

#endif
