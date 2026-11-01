workspace "Nelson"
	architecture "x64"
	toolset "v145"


	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Nelson/vendor/GLFW/include"
IncludeDir["Glad"] = "Nelson/vendor/Glad/include"
IncludeDir["imGui"] = "Nelson/vendor/imGui"
	startproject "Sandbox"

include "premake/GLFW.lua"
include "Nelson/vendor/Glad"
include "Nelson/vendor/imGui"



project "Nelson"
	location "Nelson"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/Nelson")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	pchheader "nspch.h"
	pchsource "Nelson/src/nspch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imGui}"
	}

	links {
		"GLFW",
		"Glad",
		"imGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		buildoptions { "/utf-8" }

		defines {
			"NS_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}



	filter "configurations:Debug"
		defines {"NS_DEBUG", "NS_ENABLE_ASSERTS"}
		symbols "On"

	filter "configurations:Release"
		defines "NS_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "NS_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/Sandbox")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{IncludeDir.imGui}",
		"Nelson/vendor/spdlog/include",
		"Nelson/src"
	}

	links {
		"Nelson"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		buildoptions { "/utf-8" }

		defines {
			"NS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines {"NS_DEBUG", "NS_ENABLE_ASSERTS"}

		symbols "On"

	filter "configurations:Release"
		defines "NS_RELEASE"

		optimize "On"

	filter "configurations:Dist"
		defines "NS_DIST"
		optimize "On"