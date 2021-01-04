workspace "Mimou"
	architecture "x64"
	
	configurations {
		"Debug",
		"Release",
		"Dist"
	}
	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)

IncludeDir = {}
IncludeDir["GLFW"] = "Mimou/vendor/GLFW/include"
IncludeDir["glad"] = "Mimou/vendor/glad/include"
IncludeDir["imgui"] = "Mimou/vendor/imgui"

-- This include the lua file in the GLFW
include "Mimou/vendor/GLFW"
include "Mimou/vendor/glad"
include "Mimou/vendor/imgui"



project "Mimou"
	location "Mimou"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mmpch.h"
	pchsource "Mimou/src/mmpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}"
	}

	links {
		"GLFW",
		"glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"MM_PLATFORM_WINDOWS",
			"MM_BUILD_DLL",
			"MM_ENABLE_ASSERTS",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "MM_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "MM_RELEASE"
		buildoptions "/MD"
		symbols "On"

	filter "configurations:DIST"
		defines "MM_DIST"
		buildoptions "/MD"
		symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Mimou/vendor/spdlog/include",
		"Mimou/src"
	}

	links {
		"Mimou"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"MM_PLATFORM_WINDOWS",
		}
	
	filter "configurations:Debug"
		defines "MM_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "MM_RELEASE"
		buildoptions "/MD"
		symbols "On"

	filter "configurations:DIST"
		defines "MM_DIST"
		buildoptions "/MD"
		symbols "On"
