workspace "Laika"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "Sandbox"

    outDir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

    project "Sandbox"
        location "Build/Sandbox"
        kind "ConsoleApp"
        language "C"

        targetdir   ( "Binaries/" .. outDir .. "/%{prj.name}" )
        objdir      ( "Binaries/Objects/" .. outDir .. "/%{prj.name}" )

        files { "Build/Sandbox/Source/**.c" }
        includedirs { "Build/Core/Include" }

        links { "LaikaLib" }

        filter "system:Windows"
            staticruntime "On"
            systemversion "latest"
            system "windows"
            defines { "SBX_WIN", "LKA_WIN", "_CRT_SECURE_NO_WARNINGS" }

        filter "system:Macosx"
            system "macosx"
            defines { "SBX_MACOS", "LKA_MACOS" }

        filter "system:Linux"
            pic "On"
            system "Linux"
            defines { "SBX_LINUX", "LKA_LINUX" }
            buildoptions { "-Wno-unused-result" }

        filter { "configurations:Debug" }
            defines { "SBX_DEBUG", "DEBUG" }
            optimize "Debug"
            symbols "On"

        filter { "configurations:Release" }
            defines { "SBX_RELEASE", "NDEBUG" }
            optimize "Full"
            symbols "Off"

    project "LaikaLib"
        location "Build/Core"
        kind "SharedLib"
        language "C"

        targetdir   ( "Binaries/" .. outDir .. "/%{prj.name}" )
        objdir      ( "Binaries/Objects/" .. outDir .. "/%{prj.name}" )

        files { "Build/Core/Source/**.c", "Build/Core/Include/**.h" }
        includedirs { "Build/Core/Include" }

        defines { "LKA_BUILD_DLL" }

        filter "system:Windows"
            staticruntime "On"
            systemversion "latest"
            system "windows"
            defines { "LKA_WIN", "_CRT_SECURE_NO_WARNINGS" }

            postbuildcommands
            {
                "{COPY} ../../Binaries/" .. outDir .. "/LaikaLib/*.dll ../../Binaries/" .. outDir .. "/LaikaCLI",
                "{COPY} ../../Binaries/" .. outDir .. "/LaikaLib/*.lib ../../Binaries/" .. outDir .. "/LaikaCLI",
                "{COPY} ../../Binaries/" .. outDir .. "/LaikaLib/*.dll ../../Binaries/" .. outDir .. "/Sandbox",
                "{COPY} ../../Binaries/" .. outDir .. "/LaikaLib/*.lib ../../Binaries/" .. outDir .. "/Sandbox"
            }

        filter "system:Macosx"
            system "macosx"
            defines { "LKA_MACOS" }

            prelinkcommands
            {
               ("mkdir -p ../../Binaries/" .. outDir .. "/LaikaCLI"),
               ("mkdir -p ../../Binaries/" .. outDir .. "/Sandbox")
            }
    
            postbuildcommands
            {
                ("{COPY} %{cfg.buildtarget.relpath} ../../Binaries/" .. outDir .. "/LaikaCLI"),
                ("{COPY} %{cfg.buildtarget.relpath} ../../Binaries/" .. outDir .. "/Sandbox")
            }

        filter "system:Linux"
            pic "On"
            system "Linux"
            defines { "LKA_LINUX" }
            buildoptions { "-Wno-unused-result" }

            prelinkcommands
            {
               ("mkdir -p ../../Binaries/" .. outDir .. "/LaikaCLI"),
               ("mkdir -p ../../Binaries/" .. outDir .. "/Sandbox")
            }
    
            postbuildcommands
            {
                ("{COPY} %{cfg.buildtarget.relpath} ../../Binaries/" .. outDir .. "/LaikaCLI"),
                ("{COPY} %{cfg.buildtarget.relpath} ../../Binaries/" .. outDir .. "/Sandbox")
            }

        filter { "configurations:Debug" }
            defines { "LKA_DEBUG", "DEBUG" }
            optimize "Debug"
            symbols "On"

        filter { "configurations:Release" }
            defines { "LKA_RELEASE", "NDEBUG" }
            optimize "Full"
            symbols "Off"

    project "LaikaCLI"
        location "Build/CLI"
        kind "ConsoleApp"
        language "C"

        targetdir   ( "Binaries/" .. outDir .. "/%{prj.name}" )
        objdir      ( "Binaries/Objects/" .. outDir .. "/%{prj.name}" )

        files { "Build/CLI/Source/**.c", "Build/CLI/Include/**.h" }
        includedirs { "Build/CLI/Include", "Build/Core/Include" }

        links { "LaikaLib" }

        filter "system:Windows"
            staticruntime "On"
            systemversion "latest"
            system "windows"
            defines { "CLI_WIN", "LKA_WIN", "_CRT_SECURE_NO_WARNINGS" }

        filter "system:Macosx"
            system "macosx"
            defines { "CLI_MACOS", "LKA_MACOS" }

        filter "system:Linux"
            pic "On"
            system "Linux"
            defines { "CLI_LINUX", "LKA_LINUX" }
            buildoptions { "-Wno-unused-result" }

        filter { "configurations:Debug" }
            defines { "CLI_DEBUG", "DEBUG" }
            optimize "Debug"
            symbols "On"

        filter { "configurations:Release" }
            defines { "CLI_RELEASE", "NDEBUG" }
            optimize "Full"
            symbols "Off"