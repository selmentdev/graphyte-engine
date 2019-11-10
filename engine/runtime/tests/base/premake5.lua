project "test.com.graphyte.base"
    targetname "test.com.graphyte.base"
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
        pchheader "Test.Base.pch.hxx"
        pchsource "private/Test.Base.pch.cxx"

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
