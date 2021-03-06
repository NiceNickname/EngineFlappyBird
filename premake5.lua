workspace "Flappy"
   configurations { "Debug", "Release" }
   platforms { "Win64"}
   startproject "Flappy"

   include "Engine/vendor/GLEW"
   include "Engine/vendor/GLFW"

project "Engine"
   location "Engine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"
   staticruntime "On"

   targetdir "%{prj.name}/out/bin/%{cfg.buildcfg}-%{cfg.architecture}"
   objdir "%{prj.name}/out/obj/%{cfg.buildcfg}-%{cfg.architecture}"

   files 
   { 
      "%{prj.name}/src/**.h", 
      "%{prj.name}/src/**.cpp",
      "%{prj.name}/vendor/stb_image/*.h",
      "%{prj.name}/vendor/stb_image/*.cpp"
   }

   defines { "GLEW_STATIC" }

   includedirs 
   { "%{prj.name}/vendor/GLFW/include", 
      "%{prj.name}/vendor/GLEW/include", 
      "%{prj.name}/vendor/stb_image",
      "%{prj.name}/src" 
   }
   
   
   links 
   {
        "opengl32.lib",
        "GLFW",
        "GLEW"
   }

   filter "platforms:Win64"
      system "Windows"
      architecture "x86_64"

   filter "system:windows"
		systemversion "latest"
      
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"



project "Flappy"
	location "Flappy"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir "%{prj.name}/out/bin/%{cfg.buildcfg}-%{cfg.architecture}"
   objdir "%{prj.name}/out/obj/%{cfg.buildcfg}-%{cfg.architecture}"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Engine/vendor/GLEW/include",
      "Engine/vendor/GLFW/include",
      "Engine/vendor/stb_image",
		"Engine/src"
	}

	links
	{
		"Engine"
	}

   filter "platforms:Win64"
      system "Windows"
      architecture "x86_64"

   filter "system:windows"
		systemversion "latest"
      
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      
