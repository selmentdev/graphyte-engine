#pragma once
#include <Graphyte/Application.hxx>


// =================================================================================================
//
// GPU driver markers.
//

// https://docs.nvidia.com/gameworks/content/technologies/desktop/optimus.htm
extern "C" { GX_LIB_EXPORT uint32_t NvOptimusEnablement = 1; }
// https://gpuopen.com/amdpowerxpressrequesthighperformance/
extern "C" { GX_LIB_EXPORT uint32_t AmdPowerXpressRequestHighPerformance = 1; }


// =================================================================================================
//
// Application entry point.
//

extern int GraphyteMain(int argc, char** argv) noexcept;


// =================================================================================================
//
// Launch specific main function.
//

namespace Graphyte::Launch
{
    extern int Main(int argc, char** argv) noexcept;
}


// =================================================================================================
//
// System specific main.
//

int main(int argc, char** argv)
{
    return Graphyte::Launch::Main(argc, argv);
}


// =================================================================================================
//
// Windows specific main.
//

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
INT
#if !defined(_MAC)
#if defined(_M_CEE_PURE)
__clrcall
#else
WINAPI
#endif
#else
CALLBACK
#endif
WinMain(
    [[maybe_unused]] _In_       HINSTANCE hInstance,
    [[maybe_unused]] _In_opt_   HINSTANCE hPrevInstance,
    [[maybe_unused]] _In_       LPSTR lpCmdLine,
    [[maybe_unused]] _In_       INT nShowCmd
)
{
    return Graphyte::Launch::Main(__argc, __argv);
}

#endif
