project "fmt"
    language "C++"

    files {
        "include/**.h",
        "source/format.cc",
        "**.lua"
    }
    includedirs {
        "include"
    }
    defines {
        "FMT_EXCEPTIONS=0",
    }

    filter { "toolset:msc*" }
        disablewarnings {
            "4244",
            "4275",
        }

    filter { "kind:SharedLib" }
        defines {
            "FMT_EXPORT=1",
        }

    filter { "system:android" }
        links {
            "m"
        }
