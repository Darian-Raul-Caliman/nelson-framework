#pragma once
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <filesystem>


#ifdef NS_PLATFORM_WINDOWS
#define NOMINMAX
#include <Windows.h>
#endif
