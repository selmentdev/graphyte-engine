project "libvulkanvma"
    kind "StaticLib"

    language "C++"

    files {
        "include/**.h",
        "source/**.cxx",
        "**.lua"
    }

    inlining "explicit"

    includedirs {
        "include",
        "$(VULKAN_SDK)/include",
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
        disablewarnings {
            "4100",
            "4127",
            "4189",
        }
