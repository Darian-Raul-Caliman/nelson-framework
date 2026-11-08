#pragma once
#include <string>

namespace Nelson {


	class Clipboard
	{
	public:
		static void SetText(const std::string& text);
		static std::string GetText();
	};
}