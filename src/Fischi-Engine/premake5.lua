project "Fischi-Engine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   staticruntime "off"

   targetdir ("%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
   objdir ("%{wks.location}/obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")

   files { 
      "**.h", 
      "**.c",
      "**.cpp"
   }

   includedirs {
      ".",
      "%{wks.location}/src",
      "%{wks.location}/dependencies/spdlog/include",
   }

   links{

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

        links {
            "dl",
            "pthread",
            "Xrandr",
            "Xi",
            "Xinerama",
            "Xcursor",
            "Xxf86vm",
            "X11",
            "wayland-client"
        }

   filter "configurations:Debug"
      defines { "FISCHI_DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "FISCHI_RELEASE" }
      optimize "On"

   filter "configurations:Dist"
      defines { "FISCHI_DIST" }
      optimize "On"

      postbuildcommands {
         "{COPY} %{wks.location}/resources %{cfg.targetdir}/resources"
      }