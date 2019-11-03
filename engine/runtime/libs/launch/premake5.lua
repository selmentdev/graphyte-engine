project "com.graphyte.launch"
    targetname "com.graphyte.launch"
    kind "StaticLib"

    language "c++"

    files {
        "public/**.?xx",
        "private/**.?xx",
        "*.lua",
    }

    graphyte_module {}

    use_com_graphyte_base()
    use_com_graphyte_framework()
    use_com_graphyte_graphics()
