workspace "KGameEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "KGameEngine/ThirdParty/GLFW/include"
IncludeDir["Glad"] = "KGameEngine/ThirdParty/Glad/include"
IncludeDir["ImGui"] = "KGameEngine/ThirdParty/imgui"
IncludeDir["glm"] = "KGameEngine/ThirdParty/glm"

include "KGameEngine/ThirdParty/GLFW"
include "KGameEngine/ThirdParty/Glad"
include "KGameEngine/ThirdParty/imgui"

project "KGameEngine"
	location "KGameEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "kepch.h"
	pchsource "KGameEngine/src/kepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/ThirdParty/glm/glm/**.hpp",
		"%{prj.name}/ThirdParty/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs 
	{
		"%{prj.name}/src",
		"%{prj.name}/ThirdParty/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"KE_BUILD_DLL",
			"KE_PLATFORM_WINDOWS",	
			"GLFW_INCLUDE_NONE",

		}

	filter "configurations:Debug"
		defines "KE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "KE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "KE_DIST"
		runtime "Release"
		optimize "on"
	

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"KGameEngine/ThirdParty/spdlog/include",
		"KGameEngine/src",
		"KGameEngine/ThirdParty/imgui",
		"%{IncludeDir.glm}"
	}

	links
	{
		"KGameEngine"
	}

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"

		defines
		{
			"KE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "KE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "KE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "KE_DIST"
		runtime "Release"
		optimize "on"