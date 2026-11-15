#include "nspch.h"
#include "Nelson/FileDialog.h"
#include "Nelson/Log.h"

#include <nfd.h>


namespace Nelson {


	static std::vector<nfdu8filteritem_t> ToNfdFilters(const std::vector<FileFilter>& filters)
	{
		std::vector<nfdu8filteritem_t> result;
		for (const FileFilter& filter : filters)
			result.push_back({ filter.Name.c_str(), filter.Extensions.c_str() });
		return result;
	}

	static std::optional<std::filesystem::path> ToResult(nfdresult_t result, nfdu8char_t* outPath) {
		switch (result)
		{
		case NFD_OKAY:
		{
			std::filesystem::path path = std::filesystem::u8path(outPath);
			NFD_FreePathU8(outPath);
			return path;
		}
		case NFD_CANCEL:
		{
			return std::nullopt;
		}
		case NFD_ERROR:
		{
			NS_CORE_ERROR("Filedialog: {0}", NFD_GetError());
			return std::nullopt;
		}

		}
		return std::nullopt;
	}

	std::optional<std::filesystem::path> FileDialog::OpenFile(const std::vector<FileFilter>& filters)
	{
		std::vector<nfdu8filteritem_t> nfdFilters = ToNfdFilters(filters);
		nfdu8char_t* outPath = nullptr;

		nfdresult_t result = NFD_OpenDialogU8(&outPath, nfdFilters.data(),
			(nfdfiltersize_t)nfdFilters.size(), nullptr);
		return ToResult(result, outPath);

	}

	std::optional<std::filesystem::path> FileDialog::SaveFile(const std::vector<FileFilter>& filters,
		const std::string& defaultName)
	{
		std::vector<nfdu8filteritem_t> nfdFilters = ToNfdFilters(filters);
		const nfdu8char_t* name = defaultName.empty() ? nullptr : defaultName.c_str();
		nfdu8char_t* outPath = nullptr;

		nfdresult_t result = NFD_SaveDialogU8(&outPath, nfdFilters.data(),
			(nfdfiltersize_t)nfdFilters.size(), nullptr, name);

		return ToResult(result, outPath);
	}

	void FileDialog::Init()
	{
		nfdresult_t result = NFD_Init();
		if (result == NFD_ERROR) {
			NS_CORE_ERROR("Filedialog: {0}", NFD_GetError());
		}

	}

	void FileDialog::Shutdown()
	{
		NFD_Quit();
	}


	std::optional<std::filesystem::path> FileDialog::PickFolder()
	{
		nfdu8char_t* outPath = nullptr;
		nfdu8char_t* defaultPath = nullptr;
		nfdresult_t result = NFD_PickFolderU8(&outPath, defaultPath);

		return ToResult(result, outPath);

	}
}