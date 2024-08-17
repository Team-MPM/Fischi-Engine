project "Fischi-Engine"
kind "SharedLib"
language "C++"
cppdialect "C++20"

targetdir("%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
objdir("%{wks.location}/obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")

files {
    "**.h",
    "**.c",
    "**.cpp"
}

includedirs {
    ".",
    "%{wks.location}/src",
    "%{wks.location}/dependencies/spdlog/include",
    vulkan_sdk_path .. "/Include"
}

links {
    vulkan_sdk_path .. "/Lib/vulkan-1"
}

defines {
    "FISCHI_BUILD_DLL"
}

filter "system:windows"
    systemversion "latest"
    
    defines {
        "FISCHI_PLATFORM_WINDOWS"
    }
    
filter "system:linux"
    defines {
        "FISCHI_PLATFORM_LINUX"
    }
    
    linkoptions {
        "-ldl",
        "-lpthread",
        "-lXrandr",
        "-lXi",
        "-lXinerama",
        "-lXcursor",
        "-lXxf86vm",
        "-lX11",
        "-lwayland-client"
    }

filter "configurations:Debug"
    defines { "FISCHI_DEBUG" }
    symbols "On"

    links {
        vulkan_sdk_path .. "/Lib/shaderc_sharedd"
    }

filter "configurations:Release"
    defines { "FISCHI_RELEASE" }
    optimize "On"

    links {
        vulkan_sdk_path .. "/Lib/shaderc_sharedd"
    }

filter "configurations:Dist"
    defines { "FISCHI_DIST" }
    optimize "On"

    links {
        vulkan_sdk_path .. "/Lib/shaderc_shared"
    }

    postbuildcommands {
        "{COPY} %{wks.location}/resources %{cfg.targetdir}/resources"
    }