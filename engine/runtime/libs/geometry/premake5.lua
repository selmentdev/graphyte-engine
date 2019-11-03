project "com.graphyte.geometry"
    targetname "com.graphyte.geometry"

    language "c++"

    graphyte_module {}
    
    files {
        "public/**.?xx",
        "private/**.?xx",
        "*.lua",
    }

    filter { "toolset:msc*" }
        pchheader "Geometry.pch.hxx"
        pchsource "private/Geometry.pch.cxx"

    filter { "kind:SharedLib" }
        defines {
            "module_geometry_EXPORTS=1"
        }

    use_com_graphyte_base()
