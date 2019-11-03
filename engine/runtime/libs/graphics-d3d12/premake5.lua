project "com.graphyte.graphics.d3d12"
    targetname "com.graphyte.graphics.d3d12"

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
        "d3d12",
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
        pchheader "Graphics.D3D12.pch.hxx"
        pchsource "private/Graphics.D3D12.pch.cxx"

    filter { "kind:SharedLib" }
        defines {
            "module_graphics_d3d12_EXPORTS=1"
        }

    use_com_graphyte_base()
    use_com_graphyte_graphics()
