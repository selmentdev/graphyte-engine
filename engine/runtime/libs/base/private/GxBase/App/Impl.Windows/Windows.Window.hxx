#pragma once
#include <GxBase/Diagnostics.hxx>
#include <GxBase/System.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/System/Impl.Windows/Windows.Types.hxx>
#include <GxBase/App.hxx>

namespace Graphyte::App
{
    struct Window final
    {
        WINDOWPLACEMENT PreFullscreenPlacement{};
        WindowSizeLimits SizeLimits{};
        HWND Hwnd{ nullptr };
        WindowType Type{ WindowType::Game };
        WindowMode Mode{ WindowMode::Windowed };
        float DpiScale{ 1.0f };
    };
}
