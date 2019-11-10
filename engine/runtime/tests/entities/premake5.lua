project "test.com.graphyte.entities"
    targetname "test.com.graphyte.entities"
    kind "ConsoleApp"
    
    graphyte_test {}
    
    files {
        "private/**.?xx",
        "public/**.?xx",
        "*.lua",
    }
    
    tags {
        "sdks-catch2",
    }
    
    warnings "off"

    filter { "toolset:msc*" }
        pchheader "Test.Entities.pch.hxx"
        pchsource "private/Test.Entities.pch.cxx"

    filter { "toolset:msc*", "files:**/Main.cxx" }
        flags { "NoPCH" }
    
    filter { "toolset:gcc*" }
        disablewarnings {
            "switch",
            "implicit-fallthrough",
            "unused-parameter",
            "sign-compare",
        }

    use_com_graphyte_base()
    use_com_graphyte_launch()
    use_com_graphyte_rendering()
    use_com_graphyte_graphics()
    use_com_graphyte_geometry()
    use_com_graphyte_framework()
    use_com_graphyte_entities()
