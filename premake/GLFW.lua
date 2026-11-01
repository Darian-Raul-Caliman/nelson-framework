local GLFW_DIR = "../Nelson/vendor/GLFW"

project "GLFW"
	kind "StaticLib"
	language "C"
	staticruntime "on"      
	warnings "off"          

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		GLFW_DIR .. "/include/GLFW/glfw3.h",
		GLFW_DIR .. "/include/GLFW/glfw3native.h",
		GLFW_DIR .. "/include/GLFW/glfw3native.h",
		GLFW_DIR .. "/src/context.c",
		GLFW_DIR .. "/src/init.c",
		GLFW_DIR .. "/src/input.c",
		GLFW_DIR .. "/src/monitor.c",
		GLFW_DIR .. "/src/null_init.c",
		GLFW_DIR .. "/src/null_joystick.c",
		GLFW_DIR .. "/src/null_monitor.c",
		GLFW_DIR .. "/src/null_window.c",

		GLFW_DIR .. "/src/platform.c",
		GLFW_DIR .. "/src/vulkan.c",
		GLFW_DIR .. "/src/window.c",
	}

	filter "system:windows"
		systemversion "latest"

		files
		{
			GLFW_DIR .. "/src/win32_init.c",
			GLFW_DIR .. "/src/win32_joystick.c",
			GLFW_DIR .. "/src/win32_module.c",
			GLFW_DIR .. "/src/win32_monitor.c",
			GLFW_DIR .. "/src/win32_time.c",
			GLFW_DIR .. "/src/win32_thread.c",
			GLFW_DIR .. "/src/win32_window.c",
			GLFW_DIR .. "/src/wgl_context.c",
			GLFW_DIR .. "/src/egl_context.c",
			GLFW_DIR .. "/src/osmesa_context.c"
		}
		
		defines {"_GLFW_WIN32", "_CRT_SECURE_NO_WARNINGS"}

	filter "system:linux"
		pic "On"
		
		files
		{
			GLFW_DIR .."/src/x11_init.c",
			GLFW_DIR .."/src/x11_monitor.c",
			GLFW_DIR .."/src/x11_window.c",
			GLFW_DIR .."/src/xkb_unicode.c",
			GLFW_DIR .."/src/posix_time.c",
			GLFW_DIR .."/src/posix_thread.c",
			GLFW_DIR .."/src/posix_module.c",
			GLFW_DIR .."/src/glx_context.c",
			GLFW_DIR .."/src/egl_context.c",
			GLFW_DIR .."/src/osmesa_context.c",
			GLFW_DIR .."/src/linux_joystick.c"
		}

		defines
		{
			"_GLFW_X11"
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
