workspace "Converter"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "ConverterCLI"

    outDir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"
    
    project "ConverterLib"
        location "Build/Core"
        kind "SharedLib"
        language "C"

        targetdir   ( "Binaries/" .. outDir .. "/%{prj.name}" )
        objdir      ( "Binaries/Objects/" .. outDir .. "/%{prj.name}" )

        files { "Build/Core/Source/**.c", "Build/Core/Include/**.h" }
        includedirs { "Build/Core/Include" }

        defines { "CVT_BUILD_DLL" }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../../Binaries/" .. outDir .. "/ConverterCLI")
        }

        filter "system:Windows"
            staticruntime "On"
            systemversion "latest"
            system "windows"
            defines { "CVT_WIN" }

        filter "system:Macosx"
            system "macosx"
            defines { "CVT_MACOS" }

            prelinkcommands
            {
               ("mkdir -p ../../Binaries/" .. outDir .. "/ConverterCLI")
            }
    

        filter "system:Linux"
            pic "On"
            system "Linux"
            defines { "CVT_LINUX" }

            prelinkcommands
            {
               ("mkdir -p ../../Binaries/" .. outDir .. "/ConverterCLI")
            }
    

        filter { "configurations:Debug" }
            defines { "CVT_DEBUG", "DEBUG" }
            optimize "Debug"
            symbols "On"

        filter { "configurations:Release" }
            defines { "CVT_RELEASE", "NDEBUG" }
            optimize "Full"
            symbols "Off"

    project "ConverterCLI"
        location "Build/CLI"
        kind "ConsoleApp"
        language "C"

        targetdir   ( "Binaries/" .. outDir .. "/%{prj.name}" )
        objdir      ( "Binaries/Objects/" .. outDir .. "/%{prj.name}" )

        files { "Build/CLI/Source/**.c", "Build/CLI/Include/**.h" }
        includedirs { "Build/CLI/Include", "Build/Core/Include" }

        links { "ConverterLib" }

        filter "system:Windows"
            staticruntime "On"
            systemversion "latest"
            system "windows"
            defines { "CLI_WIN" }

        filter "system:Macosx"
            system "macosx"
            defines { "CLI_MACOS" }

        filter "system:Linux"
            pic "On"
            system "Linux"
            defines { "CLI_LINUX" }

        filter { "configurations:Debug" }
            defines { "CLI_DEBUG", "DEBUG" }
            optimize "Debug"
            symbols "On"

        filter { "configurations:Release" }
            defines { "CLI_RELEASE", "NDEBUG" }
            optimize "Full"
            symbols "Off"