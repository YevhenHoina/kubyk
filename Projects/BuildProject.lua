project "kubykProject"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"
   
   files { "Source/**.h", "Source/**.cpp" }
   includedirs { 
    --All the Engine
    "$(SolutionDir)Engine/Source/inсlude/assimp",
    "$(SolutionDir)Engine/Source/inсlude/GL",
    "$(SolutionDir)Engine/Source/inсlude/GLM",
    "$(SolutionDir)Engine/Source/inсlude/GLSW",
    "$(SolutionDir)Engine/Source/inсlude/ImGui",
    "$(SolutionDir)Engine/Source",
    
    "$(SolutionDir)Project/Source"
   }
   libdirs { "$(SolutionDir)Engine/Binaries" }
   

   
      
   defines
   {
       "_CRT_SECURE_NO_WARNINGS"
   }


   targetdir ("$(SolutionDir)Project/Build/" .. OutputDir .. "/%{prj.name}")
   objdir ("$(SolutionDir)Project/Build/Intermediates/" .. OutputDir .. "/%{prj.name}")

   links { "glfw3.lib", "opengl32.lib", "user32.lib", "gdi32.lib", "shell32.lib" }
   
   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }
    
   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"