project "App"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp", "Source/**" }

   includedirs
   {
      "Source",
      "Source/**",
      "Content"
   }
      
   defines
   {
       "_CRT_SECURE_NO_WARNINGS"
   }


   targetdir ("../Build/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Build/Intermediates/" .. OutputDir .. "/%{prj.name}")

   
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