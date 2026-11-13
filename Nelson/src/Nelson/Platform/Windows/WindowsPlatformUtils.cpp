#include "nspch.h"
#include "Nelson/Platform/PlatformUtils.h"
#include <shellapi.h>
#include "Nelson/Log.h"

namespace Nelson {
	static std::wstring Utf8ToWide(const std::string& text) {
		if (text == "") {
			return {};
		}

		int size = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), (int)text.size(),nullptr,0);

		std::wstring result(size, L'\0');
		MultiByteToWideChar(CP_UTF8, 0, text.c_str(), (int)text.size(), result.data(), size);
		return result;
	}

	std::filesystem::path GetUserDataPath(const std::string& appName)
	{
		const char* appData = std::getenv("APPDATA");
		if (appData == nullptr)
		{
			NS_CORE_WARN("APPDATA nu e setat; folosesc folderul curent");
			return std::filesystem::current_path() / appName;
		}
		return std::filesystem::path(appData) / appName;
	}

	bool OpenURL(const std::string& url)
	{
		bool isWeb = url.rfind("http://", 0) == 0 || url.rfind("https://", 0) == 0;
		if (!isWeb)
		{
			NS_CORE_WARN("OpenURL: refuz adresa '{0}' (doar http:// si https://)", url);
			return false;
		}

		std::wstring wideUrl = Utf8ToWide(url);

		HINSTANCE result = ShellExecuteW(nullptr, L"open", wideUrl.c_str(), nullptr, nullptr, SW_SHOWNORMAL);

		if ((INT_PTR)result <= 32)
		{
			NS_CORE_ERROR("OpenURL: nu am putut deschide '{0}'", url);
			return false;
		}

		return true;
	}
}