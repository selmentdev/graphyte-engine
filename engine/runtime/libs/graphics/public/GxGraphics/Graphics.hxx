#pragma once
#include <GxGraphics/Graphics.module.hxx>

namespace Graphyte::Graphics
{
    // TODO: Rename to `InitializeGraphics`, etc.
    GRAPHICS_API void Initialize() noexcept;
    GRAPHICS_API void Finalize() noexcept;
}
