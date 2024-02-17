include "../../premake/common_premake_defines.lua"

project "spdlog"
	kind "StaticLib"
	language "C++"
	cppdialect "C++latest"
	cdialect "C17"
	targetname "%{prj.name}"
	inlining "Auto"

	files {
		"./include/**.h",
		"./src/**.cpp"
	}

	excludes {
		"./src/bundled_fmtlib_format.cpp"
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