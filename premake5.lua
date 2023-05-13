include "../../premake/common_premake_defines.lua"

project "spdlog"
	kind "StaticLib"
	language "C++"
	cppdialect "C++latest"
	cdialect "C17"
	targetname "%{prj.name}"
	inlining "Auto"

	files {
		"./**.h",
		"./**.cpp"
	}

	excludes {
		"./bench/**.cpp",
		"./tests/**.cpp",
		"./example/**.cpp"
	}

	includedirs {		
		"%{IncludeDir.fmt}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.vulkan_sdk}",
		"%{IncludeDir.general_includes}"
	}

	defines {
		"SPDLOG_COMPILED_LIB"
	}

 	filter "configurations:Debug"
		defines { "MLE_DEBUG_BUILD", "DEBUG" }
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines { "MLE_RELEASE_BUILD", "NDEBUG" }
		flags { "LinkTimeOptimization" }
		runtime "Release"
		optimize "speed"
		intrinsics "on"

	filter "configurations:Distribution"
		defines {  "MLE_DISTRIBUTION_BUILD", "NDEBUG" }
		flags { "LinkTimeOptimization" }
		runtime "Release"
		optimize "speed"
		intrinsics "on"