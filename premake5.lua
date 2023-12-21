workspace "KGameEngine"
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
IncludeDir["GLFW"] = "KGameEngine/ThirdParty/GLFW/include"
IncludeDir["Glad"] = "KGameEngine/ThirdParty/Glad/include"
IncludeDir["ImGui"] = "KGameEngine/ThirdParty/imgui"
IncludeDir["glm"] = "KGameEngine/ThirdParty/glm"

include "KGameEngine/ThirdParty/GLFW"
include "KGameEngine/ThirdParty/Glad"
include "KGameEngine/ThirdParty/imgui"

project "KGameEngine"
	location "KGameEngine"
	kind "SharedLib"
	language "C++"

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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"KE_BUILD_DLL",
			"KE_PLATFORM_WINDOWS",	
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "KE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "KE_RELEASE"
		buildoptions "/MD"
		symbols "On"

	filter "configurations:Dist"
		defines "KE_DIST"
		buildoptions "/MD"
		symbols "On"
	

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"KE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "KE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "KE_RELEASE"
		buildoptions "/MD"
		symbols "On"

	filter "configurations:Dist"
		defines "KE_DIST"
		buildoptions "/MD"
		symbols "On"