project "com.graphyte.graphics"
    targetname "com.graphyte.graphics"

    language "c++"

    files {
        "public/**.?xx",
        "private/**.?xx",
        "*.lua",
    }

    removefiles {
        "**/MaterialSystem/*",
    }

    tags {
        "sdks-png",
    }

    graphyte_module {}

    filter { "toolset:msc*" }
        pchheader "Graphics.pch.hxx"
        pchsource "private/Graphics.pch.cxx"
    filter { "kind:SharedLib" }

        defines {
            "module_graphics_EXPORTS=1"
        }

    use_com_graphyte_base()
