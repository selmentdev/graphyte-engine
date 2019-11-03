project "com.graphyte.graphics.glcore"
    targetname "com.graphyte.graphics.glcore"

    language "c++"

    graphyte_module {}

    includedirs {
    }

    files {
        "public/**.?xx",
        "private/**.?xx",
        "*.lua",
    }

    tags {
        "sdks-glad",
    }
        
    filter { "system:linux", "architecture:arm64" }
        links {
            "GLESv2",
        }

    filter { "system:linux", "architecture:not arm64" }
        links {
            "GL",
        }

    filter { "system:windows" }
        links {
            "opengl32",
        }

    filter { "system:linux" }
        links {
            "X11",
            "X11-xcb",
            "dl",
            "udev",
        }

    filter { "system:windows" }
        removeplatforms {
            "arm",
            "arm64",
        }

    filter { "toolset:msc*" }
        pchheader "Graphics.GLCore.pch.hxx"
        pchsource "private/Graphics.GLCore.pch.cxx"

    filter { "kind:SharedLib" }
        defines {
            "module_graphics_glcore_EXPORTS=1"
        }

    use_com_graphyte_base()
    use_com_graphyte_graphics()
