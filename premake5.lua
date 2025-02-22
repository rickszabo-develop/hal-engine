workspace "Haleng"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "HAL_Engine/vendor/GLFW/include"
IncludeDir["glad"] = "HAL_Engine/vendor/glad/include"
IncludeDir["imgui"] = "HAL_Engine/vendor/imgui"
IncludeDir["glm"] = "HAL_Engine/vendor/glm"

include "HAL_Engine/vendor/GLFW"
include "HAL_Engine/vendor/glad"
include "HAL_Engine/vendor/imgui"

project "HALENGINE"
	location "HAL_Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "halpch.h"
	pchsource "HAL_Engine/HALENGINE/src/halpch.cpp"

	files
	{
		"HAL_Engine/HALENGINE/src/**.h",
		"HAL_Engine/HALENGINE/src/**.cpp"
	}

	includedirs
	{
		"HAL_Engine/HALENGINE/src",
		"HAL_Engine/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
	}

	links
	{
		"GLFW",
		"glad",
		"opengl32.lib",
		"imgui"
	}

	defines
	{
		"_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HALENG_PLATFORM_WINDOWS",
			"HALENG_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "HALENG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HALENG_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HALENG_DIST"
		runtime "Release"
		optimize "on"

project "HalaiGame"
	location "Halai"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Halai/%{prj.name}/src/**.h",
		"Halai/%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"HAL_Engine/vendor/spdlog/include",
		"HAL_Engine/HALENGINE/src",
		"%{IncludeDir.glm}",
		"HAL_Engine/vendor/imgui"
	}

	links
	{
		"HALENGINE"
	}

	defines
	{
		"_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING",
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HALENG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HALENG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HALENG_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HALENG_DIST"
		runtime "Release"
		optimize "on"