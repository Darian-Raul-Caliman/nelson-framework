#include "PlatformUtils.h"
#include "nspch.h"
#include "Nelson/Log.h"

namespace Nelson {



	std::filesystem::path GetUserDataPath(const std::string& appname)
	{
		const char* appData = std::getenv("APPDATA");
		if (appData == nullptr) {
			NS_CORE_WARN("APPDATA not set, using the current folder");
			return std::filesystem::current_path() / appname;
		}

		return std::filesystem::path(appData) / appname;

	}

}