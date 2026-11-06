
#include "nspch.h"
#include "JsonFile.h"
#include "Nelson/Log.h"
#include <fstream>

namespace Nelson {
	std::optional<nlohmann::json> JsonFile::Load(const std::filesystem::path& path)
	{
		if (!std::filesystem::exists(path))
			return std::nullopt; //daca nu gaseste sau nu deschide fisierul intoarce nullptr


		std::ifstream file(path);
		if (!file.is_open())
		{
			NS_CORE_ERROR("JsonFile: cannot open the file '{0}'", path.string());
			return std::nullopt;
		}

		nlohmann::json data = nlohmann::json::parse(file, nullptr, false);

		if (data.is_discarded()) // invalid
		{
			NS_CORE_ERROR("JsonFile: JSON invalid in file '{0}'", path.string());
			return std::nullopt;
		}

		return data;

	}
	
	bool JsonFile::Save(const std::filesystem::path& path, const nlohmann::json& data)
	{
		if (path.has_parent_path())
		{
			std::error_code ec;
			std::filesystem::create_directories(path.parent_path(), ec);
			if (ec) {
				NS_CORE_ERROR("JsonFile: can't create the filder '{0}: {1}'",
					path.parent_path().string(), ec.message());
				return false;
			}
		}

		std::ofstream file(path);
		if (!file.is_open()) {
			NS_CORE_ERROR("JsonFile: can't write in file '{0}'", path.string());
			return false;
		}

		file << data.dump(4);
		return true;
	}




}