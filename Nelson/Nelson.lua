local NELSON_DIR = _SCRIPT_DIR
print("Nelson se afla in: " .. NELSON_DIR)

outputdir = outputdir or "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

NelsonIncludeDirs =
{

	path.join(NELSON_DIR, "src"),
	path.join(NELSON_DIR, "vendor/spdlog/include"),
	path.join(NELSON_DIR, "vendor/imGui"),
	path.join(NELSON_DIR, "vendor/nlohmann_json/include"),

}

group "Dependencies"
	include "../premake/GLFW.lua"
	include "../premake/NFD.lua"
	include "vendor/Glad"
	include "vendor/imGui"
group ""

project "Nelson"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "nspch.h"
	pchsource "src/nspch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"vendor/GLFW/include",
		"vendor/Glad/include",
		"vendor/imGui",
		"vendor/nlohmann_json/include",
		"vendor/nfd/src/include"
	}

		links
	{
		"GLFW",
		"Glad",
		"imGui",
		"nfd",
		"opengl32.lib"
	}

		filter "system:windows"
		systemversion "latest"
		buildoptions { "/utf-8" }
		defines { "NS_PLATFORM_WINDOWS", "GLFW_INCLUDE_NONE", "_CRT_SECURE_NO_WARNINGS" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		defines { "NS_DEBUG", "NS_ENABLE_ASSERTS" }

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines "NS_RELEASE"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"
		symbols "off"
		defines "NS_DIST"

	filter {}

function NelsonApp()
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs(NelsonIncludeDirs)
	links { "Nelson" }

		filter "system:windows"
		systemversion "latest"
		buildoptions { "/utf-8" }
		defines { "NS_PLATFORM_WINDOWS" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		defines { "NS_DEBUG", "NS_ENABLE_ASSERTS" }

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines "NS_RELEASE"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"
		symbols "off"
		defines "NS_DIST"
		kind "WindowedApp"
		entrypoint "mainCRTStartup"

	filter {}

end
