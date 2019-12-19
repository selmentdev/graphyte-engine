project "lz4"
    language "C"

    kind "StaticLib"

    files {
        "include/**.h",
        "source/**.c",
        "**.lua"
    }

    inlining "explicit"

    includedirs {
        "include",
    }

    filter { "toolset:msc*" }
        ufinclude "false"
