project "kubykEngine"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"
   
   
   includedirs { "Source" }
   libdirs { "Lib/link" }
   files { "Source/**.h", "Source/**.cpp" }

   
      
   defines
   {
       "_CRT_SECURE_NO_WARNINGS"
   }


   targetdir ("..Build/" .. OutputDir .. "/%{prj.name}")
   objdir ("..Build/Intermediates/" .. OutputDir .. "/%{prj.name}")

   links { "imgui", "opengl32", "gl", "glm", "assimp" }
   
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