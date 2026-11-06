#pragma once
#include <filesystem>
#include <string>

namespace Nelson {

	std::filesystem::path GetUserDataPath(const std::string& appname);
}

