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

include "HAL_Engine/vendor/GLFW"
include "HAL_Engine/vendor/glad"

project "HALENGINE"
	location "HAL_Engine"
	kind "SharedLib"
	language "C++"

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
		"%{IncludeDir.glad}"
	}

	links
	{
		"GLFW",
		"glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"HALENG_PLATFORM_WINDOWS",
			"HALENG_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/HalaiGame")
		}

	filter "configurations:Debug"
		defines "HALENG_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "HALENG_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "HALENG_DIST"
		buildoptions "/MD"
		optimize "On"

project "HalaiGame"
	location "Halai"
	kind "ConsoleApp"
	language "C++"

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
		"HAL_Engine/HALENGINE/src"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"HALENG_PLATFORM_WINDOWS"
		}

		links
		{
			"HALENGINE"
		}

	filter "configurations:Debug"
		defines "HALENG_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "HALENG_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "HALENG_DIST"
		optimize "On"