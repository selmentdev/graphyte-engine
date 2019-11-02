newoption {
    trigger = "with-tests",
    description = "Generate project files for unit tests"
}

newoption {
    trigger = "with-cc",
    description = "Generate project files for Content Creation Tools"
}

function graphyte_common()

    filter { "toolset:gcc*", "configurations:checked" }
        buildoptions {
            "-fsanitize=address"
        }

        linkoptions {
            "-fsanitize=address"
        }

    filter {}
    
        includedirs {
            "%{wks.location}/engine/include",
            "./public",
            "./private",
        }

        tags { "sdks-fmt" }

end

function graphyte_module()
    graphyte_common {}
    
    filter { "toolset:msc*" }
        ufinclude {}

    filter { "system:not windows" }
        removefiles {
            "**/Windows/**.?xx",
            "**/Impl.Windows/**.?xx",
        }

    filter { "system:not linux" }
        removefiles {
            "**/Linux/**.?xx",
            "**/Impl.Linux/**.?xx",
        }

    filter { "system:not linux", "system:not android" }
        removefiles {
            "**/Posix/**.?xx",
            "**/Impl.Posix/**.?xx",
        }

    filter { "system:not android" }
        removefiles {
            "**/Android/**.?xx",
            "**/Impl.Android/**.?xx",
        }

    filter {}
end

function graphyte_app()
    graphyte_common {}
    
    filter { "toolset:msc*" }
        ufinclude {}
    
    filter { "toolset:msc*" }
        files {
            "%{wks.location}/engine/resources/*.h",
            "%{wks.location}/engine/resources/*.rc*",
        }

    filter {}
end

function graphyte_test()
    graphyte_common {}
    
    filter { "toolset:msc*" }
        ufinclude {}
    
    filter { "toolset:msc*" }
        files {
            "%{wks.location}/engine/resources/*.h",
            "%{wks.location}/engine/resources/*.rc*",
        }

    filter { "toolset:msc*" }
        optimize "off"

    filter {}
end

workspace "graphyte"
    configurations {
        "debug",
        "profile",
        "checked",
        "release",
    }

    platforms {
        "x86",
        "x64",
        "arm64",
        "arm",
    }

    defaultplatform "x64"

    -- common directories
    objdir "%{wks.location}/build/%{cfg.buildcfg}-%{cfg.system}-%{cfg.platform}/obj"
    targetdir "%{wks.location}/build/%{cfg.buildcfg}-%{cfg.system}-%{cfg.platform}/bin"
    debugdir "$(TargetDir)"

    systemversion "latest"
    warnings "extra"
    rtti "off"
    stringpooling "on"
    --strictaliasing "level3"
    pic "on"
    nativewchar "on"
    --largeadressaware "on"
    intrinsics "on"
    inlining "disabled"
    functionlevellinking "on"
    floatingpoint "fast"
    endian "little"
    editorintegration "on"
    startproject "game"
    exceptionhandling "off"

    jmcdisabled {}
    ufenabled {}

    flags {
        "MultiProcessorCompile",
        "FatalWarnings",
        "NoManifest",
    }

    -- setup architectures
    filter { "platforms:x64" }
        architecture "x64"

    filter { "platforms:arm64" }
        architecture "arm64"

    filter { "platforms:arm" }
        architecture "arm"

    -- determine compiler
    filter { "system:windows" }
        toolset "msc"

    filter { "system:linux" }
        toolset "clang"

    filter { "system:android" }
        toolset "clang"
        androidapilevel(28)
        --toolchainversion "5.0"
        --stl "libc++"

    -- choose language stancards
    filter { "language:C" }
        cdialect "C11"

    filter { "system:linux", "language:C++", "toolset:clang*" }
        buildoptions {
            "-std=c++2a",
            "-Wno-c99-extensions",
        }

    -- use specific C/C++ features
    filter { "language:C++ or language:C" }
        defines {
            "__STDC_WANT_LIB_EXT1__=1",
            "__STDINT_MACROS",
            "__STDINT_LIMITS",
            "__STDC_CONSTANT_MACROS",
            "__STDC_FORMAT_MACROS",
            "__STDC_LIMIT_MACROS",
        }

    -- configure architecture specific flags
    filter { "architecture:x86*" }
        vectorextensions "avx"

        defines {
            "GRAPHYTE_MATH_NO_INTRINSICS=0",
        }

    filter { "architecture:arm64 or arm" }
        editandcontinue "off"
        
        defines {
            "GRAPHYTE_MATH_NO_INTRINSICS=1",
        }

    filter { "kind:ConsoleApp or WindowedApp" }
        linkgroups "on"

    -- configure toolsets
    filter { "toolset:msc*" }
        exceptionhandling "SEH"
        cppdialect "c++latest"
        buildoptions {
            "/permissive-",
            "/bigobj",
            "/Zc:char8_t",      -- NOTE: This one must be removed once MSVC will support it on regular basis.
            "/Zc:inline",
            "/Zc:throwingNew",
            "/Zc:__cplusplus",  -- https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/
        }
        linkoptions {
            "/ignore:4221", -- LNK4221: This object file does not define any previously undefined public symbols, so it will not be used by any link operation that consumes this library
            "/ignore:4006", -- LNK4006: __NULL_IMPORT_DESCRIPTOR already defined in dbghelp.lib(dbghelp.dll); second definition ignored
        }
        defines {
            "_HAS_EXCEPTIONS=0",
        }
        disablewarnings {
            "4263",         -- 'function' : member function does not override any base class virtual member function
            "4264",         -- 'virtual_function' : no override available for virtual member function from base 'class'; function is hidden
            "4275",         -- non - DLL-interface class 'class_1' used as base for DLL-interface class 'class_2'
        }

    filter { "toolset:msc*", "configurations:release" }
        defines {
            "_HAS_ITERATOR_DEBUGGING=0",
            "_SCL_SECURE=0",
            "_SECURE_SCL=0",
            "_CRT_SECURE_INVALID_PARAMETER=",
        }
        buildoptions {
            "/sdl-",
        }

    filter { "toolset:gcc*" }
        --visibility "hidden"
        --inlinesvisibility "hidden"
        buildoptions {
            "-fno-finite-math-only",
        }

    filter { "toolset:clang*" }
        buildoptions {
            "-fno-finite-math-only",
        }
    
    -- setup configurations
    -- optimization: https://docs.microsoft.com/en-us/cpp/build/reference/o-options-optimize-code?view=vs-2019
    filter { "configurations:debug" }
        defines {
            "GX_CONFIG_DEBUG",
            "DEBUG",
            "_DEBUG",
        }
        runtime "debug"
        symbols "on"

    filter { "configurations:checked" }
        defines {
            "GX_CONFIG_CHECKED",
            "NDEBUG",
        }

        runtime "release"
        optimize "speed"
        inlining "auto"

    filter { "configurations:profile" }
        defines {
            "GX_CONFIG_PROFILE",
            "NDEBUG",
        }
        runtime "release"
        optimize "speed"
        inlining "auto"

    filter { "configurations:release" }
        defines {
            "GX_CONFIG_RELEASE",
            "NDEBUG",
        }
        runtime "release"
        optimize "speed"
        inlining "auto"

    filter {}
        kind "SharedLib"
        defines { "GRAPHYTE_STATIC_BUILD=0" }

function configfunction()
    local ver = os.getversion()
    local os_version = string.format("%d.%d.%d", ver.majorversion, ver.minorversion, ver.revision, ver.description)
    local os_host = os.host()
    local build_commit = os.outputof('git log -1 --format=%H')
    local build_commit_short = os.outputof('git log -1 --format=%h')
    local build_branch = os.outputof('git rev-parse --abbrev-ref HEAD')

    local date = os.date('*t')
    local reference = os.time{ day = 1, month = 1, year = 2000 }
    local buildnumber = tonumber(math.floor(os.difftime(os.time(), reference) / (60 * 15)))

    local build_version_major = date.year - 2000
    local build_version_minor = date.month
    local build_version_release = date.yday
    local build_version_build = buildnumber

    local build_version = string.format('%d.%d.%d.%d',
        build_version_major,
        build_version_minor,
        build_version_release,
        build_version_build
    )

    local build_timestamp = os.date("!%Y-%m-%dT%H:%M:%SZ")

    return string.format(
        '#define GRAPHYTE_BUILD_OS_VERSION        "%s"\n' ..
        '#define GRAPHYTE_BUILD_OS_HOST           "%s"\n' ..
        '#define GRAPHYTE_BUILD_COMMIT            "%s"\n' ..
        '#define GRAPHYTE_BUILD_COMMIT_SHORT      "%s"\n' ..
        '#define GRAPHYTE_BUILD_BRANCH            "%s"\n' ..
        '#define GRAPHYTE_BUILD_UUID              "%s"\n' ..
        '#define GRAPHYTE_BUILD_VERSION           "%s"\n' ..
        '#define GRAPHYTE_BUILD_VERSION_MAJOR     %d\n' ..
        '#define GRAPHYTE_BUILD_VERSION_MINOR     %d\n' ..
        '#define GRAPHYTE_BUILD_VERSION_RELEASE   %d\n' ..
        '#define GRAPHYTE_BUILD_VERSION_BUILD     %d\n' ..
        '#define GRAPHYTE_BUILD_TIMESTAMP         "%s"\n',
        os_version,
        os_host,
        build_commit or "<unknown>",
        build_commit_short or "<unknown>",
        build_branch or "<unknown>",
        os.uuid('graphyte'):gsub('-', ''):lower(),
        build_version,
        build_version_major,
        build_version_minor,
        build_version_release,
        build_version_build,
        build_timestamp
    );
end

io.writefile('engine/include/Graphyte/Build.Version.hxx', configfunction())


function use_com_graphyte_base()
    filter {}
        links {
            "com.graphyte.base",
        }
        includedirs {
            "%{wks.location}/engine/runtime/libs/base/public",
        }
    filter { "system:linux" }
        links {
            "pthread",
            "uuid",
            "dl",
            "SDL2",
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

    filter {}
end;

function use_com_graphyte_launch()
    filter {}
        links {
            "com.graphyte.launch",
        }
        includedirs {
            "%{wks.location}/engine/runtime/libs/launch/public",
        }
    filter {}
end;

function use_com_graphyte_graphics()
    filter {}
        links {
            "com.graphyte.graphics",
        }
        includedirs {
            "%{wks.location}/engine/runtime/libs/graphics/public",
        }
    filter {}
end;

function use_com_graphyte_framework()
    filter {}
        links {
            "com.graphyte.framework",
        }
        includedirs {
            "%{wks.location}/engine/runtime/libs/framework/public",
        }
    filter {}
end;

function use_com_graphyte_geometry()
    filter {}
        links {
            "com.graphyte.geometry",
        }
        includedirs {
            "%{wks.location}/engine/runtime/libs/geometry/public",
        }
    filter {}
end;

function use_com_graphyte_rendering()
    filter {}
        links {
            "com.graphyte.rendering",
        }
        includedirs {
            "%{wks.location}/engine/runtime/libs/rendering/public",
        }
    filter {}
end;

function use_com_graphyte_entities()
    filter {}
        links {
            "com.graphyte.entities",
        }
        includedirs {
            "%{wks.location}/engine/runtime/libs/entities/public",
        }
    filter {}
end;

function use_com_graphyte_ai()
    filter {}
        links {
            "com.graphyte.ai",
        }
        includedirs {
            "%{wks.location}/engine/runtime/libs/ai/public",
        }
    filter {}
end;

function use_com_graphyte_assets_base()
    filter {}
        links {
            "com.graphyte.assets.base",
        }
        includedirs {
            "%{wks.location}/engine/developer/assets/libs/base/public",
        }
    filter {}
end;

include 'engine'
include 'game'
include 'sdks'

solution "*"

    --
    -- Modules
    --

    filter { "tags:com_graphyte_base" }
        links {
            "module.base",
        }
        includedirs {
            "%{wks.location}/engine/runtime/libs/base/public",
        }


    --
    -- SDKs
    --

    filter { "tags:sdks-catch2" }
        includedirs {
            "%{wks.location}/sdks/catch2/include"
        }

    filter { "tags:sdks-curl" }
        links {
            "curl",
        }    
        includedirs {
            "%{wks.location}/sdks/curl/include"
        }

    filter { "tags:sdks-fmt" }
        defines {
            "FMT_SHARED=1",
            "FMT_EXCEPTIONS=0",
        }
        links {
            "fmt",
        }
        includedirs {
            "%{wks.location}/sdks/fmt/include"
        }

    filter { "tags:sdks-freetype" }
        links {
            "freetype",
        }
        includedirs {
            "%{wks.location}/sdks/freetype/include"
        }

    filter { "tags:sdks-glad" }
        links {
            "glad",
        }    
        includedirs {
            "%{wks.location}/sdks/glad/include"
        }

    filter { "tags:sdks-pugixml" }
        links {
            "pugixml",
        }
        includedirs {
            "%{wks.location}/sdks/pugixml/include"
        }
        defines {
            "PUGIXML_API=__declspec(dllimport)",
            "PUGIXML_CLASS=__declspec(dllimport)"
        }

    ----------------------------------------------
    -- LUA
    ----------------------------------------------

    filter { "tags:sdks-lua", "kind:SharedLib", "toolset:msc*" }
        defines {
            "LUA_BUILD_AS_DLL=1",
        }

    filter { "tags:sdks-lua", "system:linux" }
        defines {
            "LUA_USE_LINUX=1"
        }
        links {
            "dl",
            "m",
        }

    filter { "tags:sdks-lua" }
        links {
            "lua",
        }
        includedirs {
            "%{wks.location}/sdks/lua/include"
        }

    filter { "tags:sdks-lz4" }
        links {
            "lz4",
        }
        includedirs {
            "%{wks.location}/sdks/lz4/include"
        }

    filter { "tags:sdks-mbedtls" }
        links {
            "mbedtls",
        }
        includedirs {
            "%{wks.location}/sdks/mbedtls/include"
        }

    filter { "tags:sdks-png" }
        links {
            "png",
        }
        includedirs {
            "%{wks.location}/sdks/png/include"
        }


    -------------
    -- sol2
    -------------

    filter { "tags:sdks-sol2" }
        includedirs {
            "%{wks.location}/sdks/sol2/include"
        }


    -------------
    -- SQLITE
    -------------

    filter { "tags:sdks-sqlite" }
        links {
            "sqlite",
        }
        includedirs {
            "%{wks.location}/sdks/sqlite/include"
        }

    filter { "tags:sdks-sqlite", "toolset:msc*" }
        defines {
            "SQLITE_API=__declspec(dllimport)"
        }

    --------------------
    -- yaml
    --------------------
    filter { "tags:sdks-yaml" }
        links {
            "yaml",
        }

        includedirs {
            "%{wks.location}/sdks/yaml/include"
        }

        defines {
            "YAML_DECLARE_STATIC=1",
        }


    -----------------------
    -- zlib
    -----------------------
    filter { "tags:sdks-zlib" }
        links {
            "zlib",
        }
    
        includedirs {
            "%{wks.location}/sdks/zlib/include"
        }

        defines {
            "ZLIB_CONST=1",
            "STDC=1",
        }

    filter { "tags:sdks-zlib", "toolset:msc*" } -- "platforms:shared", 
        defines {
            "ZLIB_DLL=1",
        }

    filter { "tags:sdks-zlib", "system:linux or system:android" }
        defines {
            "Z_HAVE_UNISTD_H=1",
        }

    -----------------------
    -- mpack
    -----------------------

    filter { "tags:sdks-mpack" }
        links {
            "mpack",
        }

        includedirs {
            "%{wks.location}/sdks/mpack/include"
        }

    -----------------------
    -- rapidjson
    -----------------------
    filter { "tags:sdks-rapidjson" }
        includedirs {
            "%{wks.location}/sdks/RapidJSON/include"
        }
