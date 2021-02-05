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
IncludeDir["glm"] = "Mimou/vendor/glm"

-- This include the lua file in the GLFW
include "Mimou/vendor/GLFW"
include "Mimou/vendor/glad"
include "Mimou/vendor/imgui"


project "Mimou"
	location "Mimou"
--	kind "SharedLib"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mmpch.h"
	pchsource "Mimou/src/mmpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}

	links {
		"GLFW",
		"glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"MM_PLATFORM_WINDOWS",
			"MM_BUILD_DLL",
			"MM_ENABLE_ASSERTS",
			"GLFW_INCLUDE_NONE"
		}

--		postbuildcommands {
--			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
--		}
	
	filter "configurations:Debug"
		defines "MM_DEBUG"
		buildoptions "/MTd"
		symbols "on"

	filter "configurations:Release"
		defines "MM_RELEASE"
		buildoptions "/MD"
		symbols "on"

	filter "configurations:DIST"
		defines "MM_DIST"
		buildoptions "/MD"
		symbols "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Mimou/vendor/spdlog/include",
		"Mimou/src",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.glad}"
	}

	links {
		"Mimou"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"MM_PLATFORM_WINDOWS",
		}
	
	filter "configurations:Debug"
		defines "MM_DEBUG"
		buildoptions "/MTd"
		symbols "on"

	filter "configurations:Release"
		defines "MM_RELEASE"
		buildoptions "/MD"
		symbols "on"

	filter "configurations:DIST"
		defines "MM_DIST"
		buildoptions "/MD"
		symbols "on"
