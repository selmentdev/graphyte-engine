group "game"

project "game"
    kind "WindowedApp"
    language "C++"

    graphyte_app {}

    dependson {
        --"module.graphics.d3d11",
        --"module.graphics.d3d12",
        --"module.graphics.glcore",
        --"module.graphics.vulkan",
    }

    files {
        "public/**.hxx",
        "private/**.cxx",
        "**.lua",
    }    

    use_com_graphyte_base()
    use_com_graphyte_launch()
    use_com_graphyte_ai()
    use_com_graphyte_rendering()
    use_com_graphyte_graphics()
    use_com_graphyte_geometry()
    use_com_graphyte_framework()
    use_com_graphyte_entities()
