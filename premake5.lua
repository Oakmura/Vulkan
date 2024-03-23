workspace "Vulkan"
    architecture "x86_64"
    startproject "Vulkan"

    configurations
    {
        "Debug",
        "Release",
        "Distribution",
    }

    flags
    {
        "MultiProcessorCompile"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    
    -- Include directories relative to root folder (solution directory)
    IncludeDir = {}
    IncludeDir["glm"] = "%{wks.location}/%{wks.name}/vendor/glm"
    IncludeDir["glfw"] = "%{wks.location}/%{wks.name}/vendor/glfw/include"
    IncludeDir["Vulkan"] = "C:/VulkanSDK/1.3.280.0/Include"
    
    
group "Dependencies"    
    include "Vulkan/vendor/glfw"
group ""

    project "Vulkan"
        location "Vulkan"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

        pchheader "Precompiled.h"
        pchsource "%{wks.location}/%{wks.name}/src/Precompiled.cpp"

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/vendor/glm/glm/**.hpp",
            "%{prj.name}/vendor/glm/glm/**.inl",
        }

        defines
        {
            "_CRT_SECURE_NO_WARNINGS"
        } 

        includedirs
        {
            "%{prj.name}/src",
            "%{IncludeDir.glm}",
            "%{IncludeDir.glfw}",
            "%{IncludeDir.Vulkan}",
        }

        links
        {
            "%{IncludeDir.Vulkan}/../Lib/vulkan-1.lib",
            "glfw",
        }

        filter "system:windows"
            systemversion "latest"

        filter "configurations:Debug"
            defines { "DEBUG", "_DEBUG" }
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            defines { "RELEASE", "NDEBUG" }
            runtime "Release"
            optimize "on"
            symbols "off"

        filter "configurations:Distribution"
            defines { "DIST", "NDEBUG" }
            runtime "Release"
            optimize "full"
            symbols "off"