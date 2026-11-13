local NFD_DIR = "../Nelson/vendor/nfd"

project "nfd"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	warnings "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		NFD_DIR .. "/src/include/nfd.h"
	}

	includedirs
	{
		NFD_DIR .. "/src/include"
	}

	filter "system:windows"
		systemversion "latest"

		files
		{
			NFD_DIR .. "/src/nfd_win.cpp"
		}

		links
		{
			"ole32.lib",
			"uuid.lib",
			"shell32.lib"
		}


	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "speed"

	filter "configurations:Dist"
		runtime "Release"
		optimize "speed"
		symbols "off"