#pragma once
#include <filesystem>
#include <string>

namespace Nelson {

	std::filesystem::path GetUserPath(const std::string& appname);
}

