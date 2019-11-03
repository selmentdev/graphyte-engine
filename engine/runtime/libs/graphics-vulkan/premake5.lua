project "com.graphyte.graphics.vulkan"
    targetname "com.graphyte.graphics.vulkan"

    language "c++"

    graphyte_module {}

    includedirs {
        "%{wks.location}/sdks/libvulkanvma/include",
    }

    files {
        "public/**.?xx",
        "private/**.?xx",
        "*.lua",
    }

    links {
        "libvulkanvma"
    }

    includedirs {
        "$(VULKAN_SDK)/include",
    }

    filter { "system:windows", "architecture:x86" }
        links {
            "$(VULKAN_SDK)/lib32/vulkan-1.lib",
        }

    filter { "system:windows", "architecture:x64" }
        links {
            "$(VULKAN_SDK)/lib/vulkan-1.lib",
        }

    filter { "system:linux or android" }
        removeplatforms {
            "x86",
            "x64",
            "arm",
            "arm64",
        }

    filter { "system:windows" }
        removeplatforms {
            "arm",
            "arm64",
        }

    filter { "toolset:msc*" }
        pchheader "Graphics.Vulkan.pch.hxx"
        pchsource "private/Graphics.Vulkan.pch.cxx"

    filter { "kind:SharedLib" }
        defines {
            "module_graphics_vulkan_EXPORTS=1"
        }

    use_com_graphyte_base()
    use_com_graphyte_graphics()
