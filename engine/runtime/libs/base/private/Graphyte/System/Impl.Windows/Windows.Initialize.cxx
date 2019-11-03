#include "Base.pch.hxx"

#include "../Platform.impl.hxx"

namespace Graphyte::System::Impl
{
    void InitializePlatform() noexcept
    {
        //
        // Initialize COM.
        //

        if (HRESULT hComInitialized = CoInitialize(nullptr); hComInitialized != S_OK && hComInitialized != S_FALSE)
        {
            GX_ABORT("Cannot initialize COM");
        }


        //
        // Setup C locale.
        //

        std::setlocale(LC_ALL, "en_US.UTF-8");


        //
        // Setup leak detection in C library.
        //

#if defined(_MSC_VER)
#ifndef NDEBUG
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
#endif

        //
        // Initialize WSA.
        //

        WSADATA wsadata{};

        if (int error = WSAStartup(MAKEWORD(2, 2), &wsadata); error == 0)
        {
            if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wVersion) != 2)
            {
                GX_ABORT("Could not initialize WinSock: invalid version {}.{}",
                    LOBYTE(wsadata.wVersion),
                    HIBYTE(wsadata.wVersion)
                );
            }
        }
        else
        {
            GX_ABORT("Could not initialize WinSock: {}", Diagnostics::GetMessageFromSystemError(error));
        }

        //
        // Compute time divisor.
        //

        GSecondsPerCycle = 1.0 / static_cast<double>(System::GetTimestampResolution());
    }

    void FinalizePlatform() noexcept
    {
        //
        // Cleanup WSA.
        //

        WSACleanup();


        //
        // Cleanup COM.
        //

        CoUninitialize();
    }
}
