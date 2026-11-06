#pragma once

#pragma once
#include <nlohmann/json.hpp>
#include <filesystem>
#include <optional>

namespace Nelson {

	class JsonFile
	{
	public: // intoarce json sau nimic si nullopt daca eroare
		static std::optional<nlohmann::json> Load(const std::filesystem::path& path);
		//true daca salvarea a reusit
		static bool Save(const std::filesystem::path& path, const nlohmann::json& data);

	private:
		const std::filesystem::path c_path;
	};
}