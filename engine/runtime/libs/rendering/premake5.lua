project "com.graphyte.rendering"
    targetname "com.graphyte.rendering"

    language "c++"

    graphyte_module {}

    
    files {
        "public/**.?xx",
        "private/**.?xx",
        "*.lua",
    }

    filter { "toolset:msc*" }
        pchheader "Rendering.pch.hxx"
        pchsource "private/Rendering.pch.cxx"

    filter { "kind:SharedLib" }
        defines {
            "module_rendering_EXPORTS=1"
        }

    use_com_graphyte_base()
    use_com_graphyte_graphics()
    use_com_graphyte_geometry()
