#pragma once

#include <nlohmann/json.hpp>
#include <filesystem>
#include <string>

namespace Nelson {
	class Settings
	{
	public:
		void Load(const std::filesystem::path& path);
		void Save() const;

		template<typename T>
		T Get(const std::string& key, const T& defaultValue) const
		{
			if (!m_Data.contains(key)) {
				return defaultValue;
			}

			try
			{
				return m_Data.at(key).get<T>();
			}
			catch (const nlohmann::json::exception&)
			{
				return defaultValue;
			}


		}
		template<typename T>
		void Set(const std::string& key, const T& value)
		{
			m_Data[key] = value;
		}
	private:
		nlohmann::json m_Data = nlohmann::json::object();
		std::filesystem::path m_Path;
	};
}