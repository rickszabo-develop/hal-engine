workspace "Haleng"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "HALENGINE"
	location "HAL_Engine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"HAL_Engine/HALENGINE/src/**.h",
		"HAL_Engine/HALENGINE/src/**.cpp"
	}

	includedirs
	{
		"HAL_Engine/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"HALENG_PLATFORM_WINDOWS",
			"HALENG_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/HalaiGame")
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