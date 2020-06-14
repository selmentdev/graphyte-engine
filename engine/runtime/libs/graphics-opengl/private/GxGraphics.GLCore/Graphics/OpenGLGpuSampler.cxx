#include "OpenGLGpuSampler.hxx"
#include "OpenGLGpuTypeMapping.hxx"
#include "OpenGLGpuDevice.hxx"

namespace Graphyte::Graphics
{
    GpuSamplerHandle OpenGLGpuDevice::CreateSampler(
        const GpuSamplerCreateArgs& args) noexcept
    {
        auto native = new OpenGLGpuSampler();

        GPU_GL_VALIDATE(glCreateSamplers(
            1,
            &native->m_Resource));

#if ENABLE_GPU_API_DEBUG
        GPU_GL_VALIDATE(glObjectLabel(
            GL_SAMPLER,
            native->m_Resource,
            static_cast<GLsizei>(strlen("Sampler")),
            "Sampler"));
#endif

        //
        // Min + mip filter.
        //
        {
            auto min_filter = GpuFilterTraits::GetMinFilter(args.Filter);
            auto mip_filter = GpuFilterTraits::GetMipFilter(args.Filter);

            GLint filter_value;

            if (min_filter == GpuFilterType::Linear && mip_filter == GpuFilterType::Linear)
            {
                filter_value = GL_LINEAR_MIPMAP_LINEAR;
            }
            else if (min_filter == GpuFilterType::Linear && mip_filter == GpuFilterType::Point)
            {
                filter_value = GL_LINEAR_MIPMAP_NEAREST;
            }
            else if (min_filter == GpuFilterType::Point && mip_filter == GpuFilterType::Linear)
            {
                filter_value = GL_NEAREST_MIPMAP_LINEAR;
            }
            else if (min_filter == GpuFilterType::Point && mip_filter == GpuFilterType::Point)
            {
                filter_value = GL_NEAREST_MIPMAP_NEAREST;
            }
            else
            {
                GX_ASSERTF(false, "Invalid filter specified");
                filter_value = GL_LINEAR;
            }

            GPU_GL_VALIDATE(glSamplerParameteri(
                native->m_Resource,
                GL_TEXTURE_MIN_FILTER,
                filter_value));
        }

        //
        // Mag filter.
        //
        {
            auto mag_filter = GpuFilterTraits::GetMagFilter(args.Filter);

            GLint filter_value;

            switch (mag_filter)
            {
                case GpuFilterType::Linear:
                {
                    filter_value = GL_LINEAR;
                    break;
                }
                case GpuFilterType::Point:
                {
                    filter_value = GL_NEAREST;
                    break;
                }
                default:
                {
                    filter_value = GL_NEAREST;
                    break;
                }
            }

            GPU_GL_VALIDATE(glSamplerParameteri(
                native->m_Resource,
                GL_TEXTURE_MAG_FILTER,
                filter_value));
        }

        //
        // Comparison mode
        //
        {
            auto reduction = GpuFilterTraits::GetReductionType(args.Filter);

            if (reduction == GpuFilterReductionType::Comparison)
            {
                GPU_GL_VALIDATE(glSamplerParameteri(
                    native->m_Resource,
                    GL_TEXTURE_COMPARE_MODE,
                    GL_COMPARE_REF_TO_TEXTURE));

                GPU_GL_VALIDATE(glSamplerParameteri(
                    native->m_Resource,
                    GL_TEXTURE_COMPARE_FUNC,
                    static_cast<GLint>(OpenGLGpuTypeMapping::ComparizonFunction(args.CompareOp))));
            }
        }

        //
        // LoD
        //
        {
            GPU_GL_VALIDATE(glSamplerParameterf(
                native->m_Resource,
                GL_TEXTURE_MIN_LOD,
                args.MinLod));

            GPU_GL_VALIDATE(glSamplerParameterf(
                native->m_Resource,
                GL_TEXTURE_MAX_LOD,
                args.MaxLod));

            GPU_GL_VALIDATE(glSamplerParameterf(
                native->m_Resource,
                GL_TEXTURE_LOD_BIAS,
                args.MipLodBias));
        }

        //
        // Addressing
        //
        {
            GPU_GL_VALIDATE(glSamplerParameteri(
                native->m_Resource,
                GL_TEXTURE_WRAP_S,
                static_cast<GLint>(OpenGLGpuTypeMapping::TextureAddressMode(args.AddressU))));

            GPU_GL_VALIDATE(glSamplerParameteri(
                native->m_Resource,
                GL_TEXTURE_WRAP_T,
                static_cast<GLint>(OpenGLGpuTypeMapping::TextureAddressMode(args.AddressV))));

            GPU_GL_VALIDATE(glSamplerParameteri(
                native->m_Resource,
                GL_TEXTURE_WRAP_R,
                static_cast<GLint>(OpenGLGpuTypeMapping::TextureAddressMode(args.AddressW))));
        }

        return native;
    }

    void OpenGLGpuDevice::DestroySampler(
        GpuSamplerHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<OpenGLGpuSampler*>(handle);

        GPU_GL_VALIDATE(glDeleteSamplers(
            1,
            &native->m_Resource));

        delete native;
    }
}
