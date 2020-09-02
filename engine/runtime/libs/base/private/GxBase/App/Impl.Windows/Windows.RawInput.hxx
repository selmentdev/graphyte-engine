#pragma once
#include <GxBase/App.hxx>

namespace Graphyte::App::Impl
{
    BASE_API void EnableRawInputKeyboard(Window& window, bool enable, bool enforce) noexcept;
    BASE_API void EnableRawInputMouse(Window& window, bool enable, bool enforce) noexcept;
}
