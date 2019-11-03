project "com.graphyte.graphics.d3d11"
    targetname "com.graphyte.graphics.d3d11"

    language "c++"

    graphyte_module {}

    includedirs {
    }

    files {
        "public/**.?xx",
        "private/**.?xx",
        "*.lua",
    }

    links {
        "dxgi",
        "d3d11",
        "dxguid",
    }

    filter { "system:linux or android" }
        removeplatforms {
            "x86",
            "x64",
            "arm",
            "arm64",
        }

    filter { "toolset:msc*" }
        pchheader "Graphics.D3D11.pch.hxx"
        pchsource "private/Graphics.D3D11.pch.cxx"

    filter { "kind:SharedLib" }
        defines {
            "module_graphics_d3d11_EXPORTS=1"
        }

    use_com_graphyte_base()
    use_com_graphyte_graphics()
