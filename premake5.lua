require "vscode"

vulkan_sdk_path = os.getenv("VULKAN_SDK") 

workspace "Fischi-Engine"
   architecture "x86_64"
   configurations { "Debug", "Release", "Dist" }

flags {
    "MultiProcessorCompile"
}

staticruntime "off"

group "Engine"
    include "src/Fischi-Engine"
group "Editor"
    -- include "src/Fischi-Editor"
group "Test"
    include "src/Sandbox"
group "Dependencies"

group ""