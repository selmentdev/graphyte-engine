project "com.graphyte.base"
    targetname "com.graphyte.base"

    language "c++"

    files {
        "public/**.hxx",
        "private/**.cxx",
        "private/**.hxx",
        "*.lua",
        "*.natvis",
    }

    tags {
        "sdks-lz4",
        --"sdks-yaml",
        --"sdks-zlib",
        --"sdks-mbedtls",
        --"sdks-curl",
        --"sdks-mpack",
        --"sdks-rapidjson",
    }

    graphyte_module {}

    filter { "toolset:msc*" }
        pchheader "Base.pch.hxx"
        pchsource "private/Base.pch.cxx"

    filter { "kind:SharedLib" }
        defines {
            "module_base_EXPORTS=1"
        }

    filter { "system:windows" }
        links {
            "ntdll",
            "comctl32",
            "dbghelp",
            "iphlpapi",
            "ws2_32",
            "dwmapi",
            "xinput",
            "xaudio2",
            "advapi32",
            "gdi32",
            "shell32",
            "ole32",
            "Faultrep",
            "Bcrypt.lib",
            "Mincore.lib",
        }

    filter { "system:linux" }
        links {
            "pthread",
            "uuid",
            "dl",
            --"SDL2",
            "unwind",
            "unwind-generic",
        }

    filter { "system:linux", "architecture:x86_64" }
        links {
            "unwind-x86_64",
        }

    filter { "system:linux", "architecture:arm64" }
        links {
            "unwind-aarch64",
        }

