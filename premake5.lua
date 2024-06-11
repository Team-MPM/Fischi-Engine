require "vscode"

workspace "Fischi-Engine"
   architecture "x86_64"
   configurations { "Debug", "Release", "Dist" }


group "Engine"
   include "src/Fischi-Engine"
group "Editor"
   include "src/Fischi-Editor"
group "Test"
   include "src/Sandbox"
group "Dependencies"

group ""