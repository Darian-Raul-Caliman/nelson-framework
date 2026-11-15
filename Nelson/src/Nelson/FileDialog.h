#pragma once
#include <filesystem>
#include <optional>
#include <string>
#include <vector>


namespace Nelson {


	struct FileFilter {
		std::string Name;
		std::string Extensions;
	};

	class FileDialog
	{
	public:

		static std::optional<std::filesystem::path> OpenFile(
			const std::vector<FileFilter>& filters = {});

		static std::optional<std::filesystem::path> SaveFile(
			const std::vector<FileFilter>& filters = {},
			const std::string& defaultName = "");

		static std::optional<std::filesystem::path> PickFolder();
	};
	

}