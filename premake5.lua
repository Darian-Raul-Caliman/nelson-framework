workspace "Nelson"
	architecture "x64"
	toolset "v145"
	configurations { "Debug", "Release", "Dist" }
	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


include "Nelson/Nelson.lua"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	files
	{
		"Sandbox/src/**.h",
		"Sandbox/src/**.cpp"
	}

	NelsonApp()