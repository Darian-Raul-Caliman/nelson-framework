#include "nspch.h"
#include "Settings.h"
#include "Nelson/Serialization/JsonFile.h"

namespace Nelson {
	void Settings::Load(const std::filesystem::path& path)
	{
		m_Path = path;
		auto loaded = JsonFile::Load(path);
		if (loaded && loaded->is_object())
			m_Data = *loaded;
		else
			m_Data = nlohmann::json::object();

	}
	void Settings::Save() const
	{
		JsonFile::Save(m_Path, m_Data);
	}

}