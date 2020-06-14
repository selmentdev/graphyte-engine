#pragma once
#include "OpenGLGpuCommon.hxx"
#include <GxGraphics/Graphics/PixelFormat.hxx>

namespace Graphyte::Graphics
{
    PixelFormat OpenGLGpuGetPixelFormat(
        GLenum internal_format) noexcept;

    PixelFormat OpenGLGpuGetPixelFormat(
        GLenum format,
        GLenum type) noexcept;

    bool OpenGLGpuGetPixelFormat(
        PixelFormat pixel_format,
        GLenum& internal_format,
        GLboolean& compressed) noexcept;

    bool OpenGLGpuGetPixelFormat(
        PixelFormat pixel_format,
        GLenum& format,
        GLenum& type) noexcept;
}
