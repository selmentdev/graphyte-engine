#include "OpenGLGpuTexture.hxx"
#include "OpenGLGpuDevice.hxx"
#include "OpenGLGpuPixelFormat.hxx"
#include "OpenGLGpuDevice.hxx"

namespace Graphyte::Graphics
{
}

namespace Graphyte::Graphics
{
    GpuTexture2DHandle OpenGLGpuDevice::CreateTexture2D(
        const GpuTextureCreateArgs& args) noexcept
    {
        auto native = new OpenGLGpuTexture();

        GLenum internalFormat{};
        GLenum storageFormat{};
        GLenum storageType{};
        GLboolean compressed{ GL_FALSE };

        OpenGLGpuGetPixelFormat(
            args.DataFormat,
            internalFormat,
            compressed);

        OpenGLGpuGetPixelFormat(
            args.DataFormat,
            storageFormat,
            storageType);

        GPU_GL_VALIDATE(glCreateTextures(
            GL_TEXTURE_2D,
            1,
            &native->m_Resource));

        native->m_Target = GL_TEXTURE_2D;

        GPU_GL_VALIDATE(glTextureStorage2D(
            native->m_Resource,
            static_cast<GLsizei>(args.MipCount),
            internalFormat,
            static_cast<GLsizei>(args.Width),
            static_cast<GLsizei>(args.Height)));

        if (args.Data != nullptr)
        {
            uint32_t w = args.Width;
            uint32_t h = args.Height;

            for (uint32_t mip_slice = 0; mip_slice < args.MipCount; ++mip_slice)
            {
                if (compressed != GL_FALSE)
                {
                    GPU_GL_VALIDATE(glCompressedTextureSubImage2D(
                        native->m_Resource,
                        static_cast<GLsizei>(mip_slice),
                        0,
                        0,
                        static_cast<GLsizei>(w),
                        static_cast<GLsizei>(h),
                        internalFormat,
                        static_cast<GLsizei>(args.Data[mip_slice].SlicePitch),
                        args.Data[mip_slice].Memory));
                }
                else
                {
                    GPU_GL_VALIDATE(glTextureSubImage2D(
                        native->m_Resource,
                        static_cast<GLint>(mip_slice),
                        0,
                        0,
                        static_cast<GLsizei>(w),
                        static_cast<GLsizei>(h),
                        storageFormat,
                        storageType,
                        args.Data[mip_slice].Memory));
                }

                w = std::max<uint32_t>(1U, w >> 1U);
                h = std::max<uint32_t>(1U, h >> 1U);
            }
        }

        return native;
    }

    void OpenGLGpuDevice::DestroyTexture2D(
        GpuTexture2DHandle handle) noexcept
    {
        GX_ASSERT(handle)
        auto native = static_cast<OpenGLGpuTexture*>(handle);

        GX_ASSERT(native->m_Target == GL_TEXTURE_2D);

        GPU_GL_VALIDATE(glDeleteTextures(
            1,
            &native->m_Resource));

        delete native;
    }

    void OpenGLGpuDevice::UpdateTexture2D(
        GpuTexture2DHandle handle,
        uint32_t mip_level,
        const GpuRect* rect,
        const void* data,
        uint32_t pitch) noexcept
    {
        (void)handle;
        (void)mip_level;
        (void)rect;
        (void)data;
        (void)pitch;
    }

    void OpenGLGpuDevice::GenerateMipmapsTexture2D(
        GpuTexture2DHandle handle) noexcept
    {
        (void)handle;
    }

    std::unique_ptr<Image> OpenGLGpuDevice::SaveTexture2D(
        GpuTexture2DHandle handle) noexcept
    {
        (void)handle;
        return nullptr;
    }
}

namespace Graphyte::Graphics
{
    GpuTexture2DArrayHandle OpenGLGpuDevice::CreateTexture2DArray(
        const GpuTextureCreateArgs& args) noexcept
    {
        auto native = new OpenGLGpuTexture();

        GLenum internalFormat{};
        GLenum storageFormat{};
        GLenum storageType{};
        GLboolean compressed{ GL_FALSE };

        OpenGLGpuGetPixelFormat(
            args.DataFormat,
            internalFormat,
            compressed);

        OpenGLGpuGetPixelFormat(
            args.DataFormat,
            storageFormat,
            storageType);

        GPU_GL_VALIDATE(glCreateTextures(
            GL_TEXTURE_2D_ARRAY,
            1,
            &native->m_Resource));

        native->m_Target = GL_TEXTURE_2D_ARRAY;

        GPU_GL_VALIDATE(glTextureStorage3D(
            native->m_Resource,
            static_cast<GLsizei>(args.MipCount),
            internalFormat,
            static_cast<GLsizei>(args.Width),
            static_cast<GLsizei>(args.Height),
            static_cast<GLsizei>(args.Depth)));

        if (args.Data != nullptr)
        {
            for (uint32_t array_slice = 0; array_slice < args.Depth; ++array_slice)
            {
                uint32_t w = args.Width;
                uint32_t h = args.Height;

                for (uint32_t mip_slice = 0; mip_slice < args.MipCount; ++mip_slice)
                {
                    size_t slice = Image::CalcSubresource(
                        mip_slice,
                        array_slice,
                        args.MipCount);

                    GPU_GL_VALIDATE(glTextureSubImage3D(
                        native->m_Resource,
                        static_cast<GLint>(mip_slice),
                        0,
                        0,
                        static_cast<GLint>(array_slice),
                        static_cast<GLsizei>(w),
                        static_cast<GLsizei>(h),
                        1,
                        storageFormat,
                        storageType,
                        args.Data[slice].Memory));

                    w = std::max<uint32_t>(1U, w >> 1U);
                    h = std::max<uint32_t>(1U, h >> 1U);
                }
            }
        }

        return native;
    }

    void OpenGLGpuDevice::OpenGLGpuDevice::DestroyTexture2DArray(
        GpuTexture2DArrayHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto native = static_cast<OpenGLGpuTexture*>(handle);

        GX_ASSERT(native->m_Target == GL_TEXTURE_2D_ARRAY);

        GPU_GL_VALIDATE(glDeleteTextures(
            1,
            &native->m_Resource));

        delete native;
    }
}

namespace Graphyte::Graphics
{
    GpuTexture3DHandle OpenGLGpuDevice::CreateTexture3D(
        const GpuTextureCreateArgs& args) noexcept
    {
        auto native = new OpenGLGpuTexture();

        GLenum internalFormat{};
        GLenum storageFormat{};
        GLenum storageType{};
        GLboolean compressed{ GL_FALSE };

        OpenGLGpuGetPixelFormat(
            args.DataFormat,
            internalFormat,
            compressed);

        OpenGLGpuGetPixelFormat(
            args.DataFormat,
            storageFormat,
            storageType);

        GPU_GL_VALIDATE(glCreateTextures(
            GL_TEXTURE_3D,
            1,
            &native->m_Resource));

        native->m_Target = GL_TEXTURE_3D;

        GPU_GL_VALIDATE(glTextureStorage3D(
            native->m_Resource,
            static_cast<GLsizei>(args.MipCount),
            internalFormat,
            static_cast<GLsizei>(args.Width),
            static_cast<GLsizei>(args.Height),
            static_cast<GLsizei>(args.Depth)));

        if (args.Data != nullptr)
        {
            uint32_t w = args.Width;
            uint32_t h = args.Height;
            uint32_t d = args.Depth;

            for (uint32_t mip_slice = 0; mip_slice < args.MipCount; ++mip_slice)
            {
                GPU_GL_VALIDATE(glTextureSubImage3D(
                    native->m_Resource,
                    static_cast<GLint>(mip_slice),
                    0,
                    0,
                    0,
                    static_cast<GLsizei>(w),
                    static_cast<GLsizei>(h),
                    static_cast<GLsizei>(d),
                    storageFormat,
                    storageType,
                    args.Data[mip_slice].Memory));

                w = std::max<uint32_t>(1U, w >> 1U);
                h = std::max<uint32_t>(1U, h >> 1U);
                d = std::max<uint32_t>(1U, d >> 1U);
            }
        }

        return native;
    }

    void OpenGLGpuDevice::DestroyTexture3D(
        GpuTexture3DHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto native = static_cast<OpenGLGpuTexture*>(handle);

        GX_ASSERT(native->m_Target == GL_TEXTURE_3D);

        GPU_GL_VALIDATE(glDeleteTextures(
            1,
            &native->m_Resource));

        delete native;
    }
}

namespace Graphyte::Graphics
{
    GpuTextureCubeHandle OpenGLGpuDevice::CreateTextureCube(
        const GpuTextureCreateArgs& args) noexcept
    {
        auto native = new OpenGLGpuTexture();

        GLenum internalFormat{};
        GLenum storageFormat{};
        GLenum storageType{};
        GLboolean compressed{ GL_FALSE };

        OpenGLGpuGetPixelFormat(
            args.DataFormat,
            internalFormat,
            compressed);

        OpenGLGpuGetPixelFormat(
            args.DataFormat,
            storageFormat,
            storageType);

        GX_ASSERTF(args.Depth == 6, "Cube map texture requires exactly 6 faces");

        GPU_GL_VALIDATE(glCreateTextures(
            GL_TEXTURE_CUBE_MAP,
            1,
            &native->m_Resource));

        native->m_Target = GL_TEXTURE_CUBE_MAP;

        GPU_GL_VALIDATE(glTextureStorage3D(
            native->m_Resource,
            static_cast<GLsizei>(args.MipCount),
            internalFormat,
            static_cast<GLsizei>(args.Width),
            static_cast<GLsizei>(args.Height),
            6));

        if (args.Data != nullptr)
        {
            for (uint32_t cube_slice = 0; cube_slice < 6; ++cube_slice)
            {
                uint32_t w = args.Width;
                uint32_t h = args.Height;

                for (uint32_t mip_slice = 0; mip_slice < args.MipCount; ++mip_slice)
                {
                    uint32_t slice = Image::CalcSubresource(
                        mip_slice,
                        cube_slice,
                        args.MipCount);

                    GPU_GL_VALIDATE(glTextureSubImage3D(
                        native->m_Resource,
                        static_cast<GLsizei>(mip_slice),
                        0,
                        0,
                        static_cast<GLsizei>(slice),
                        static_cast<GLsizei>(w),
                        static_cast<GLsizei>(h),
                        1,
                        storageFormat,
                        storageType,
                        args.Data[slice].Memory));

                    /*glCompressedTextureSubImage3D(
                        native->m_Resource,
                        static_cast<GLsizei>(mip_slice),
                        0,
                        0,
                        static_cast<GLsizei>(slice),
                        static_cast<GLsizei>(w),
                        static_cast<GLsizei>(h),
                        1,
                        storageFormat,
                        args.Data->Pitch
                    )*/

                    w = std::max<uint32_t>(1U, w >> 1U);
                    h = std::max<uint32_t>(1U, h >> 1U);
                }
            }
        }

        return native;
    }

    void OpenGLGpuDevice::DestroyTextureCube(
        GpuTextureCubeHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto native = static_cast<OpenGLGpuTexture*>(handle);

        GX_ASSERT(native->m_Target == GL_TEXTURE_CUBE_MAP);

        GPU_GL_VALIDATE(glDeleteTextures(
            1,
            &native->m_Resource));

        delete native;
    }
}
