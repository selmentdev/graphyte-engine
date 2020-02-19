#pragma once
#include <Graphyte/Assets.Shader.module.hxx>

#if GRAPHYTE_PLATFORM_WINDOWS

#include <Graphyte/AssetsPipeline/ShaderProcessor.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Types.hxx>
#include <Graphyte/Graphics/Gpu/GpuDefinitions.hxx>

namespace Graphyte::AssetsPipeline
{
    struct HlslShaderTraits final
    {
        static const char* GetHlslStagePrefix(Graphics::GpuShaderStage stage) noexcept
        {
            switch (stage)
            {
            case Graphics::GpuShaderStage::Pixel:
                return "ps";
            case Graphics::GpuShaderStage::Vertex:
                return "vs";
            case Graphics::GpuShaderStage::Geometry:
                return "gs";
            case Graphics::GpuShaderStage::Hull:
                return "hs";
            case Graphics::GpuShaderStage::Domain:
                return "ds";
            case Graphics::GpuShaderStage::Compute:
                return "cs";
            default:
                break;
            }

            return nullptr;
        }

        static const char* GetHlslProfileSuffix(Graphics::GpuShaderProfile profile) noexcept
        {
            switch (profile)
            {
            case Graphics::GpuShaderProfile::D3DSM_5_0:
                return "5_0";
            case Graphics::GpuShaderProfile::D3DSM_5_1:
                return "5_1";
            case Graphics::GpuShaderProfile::D3DSM_6_0:
                return "6_0";
            case Graphics::GpuShaderProfile::D3DSM_6_1:
                return "6_1";
            default:
                break;
            }

            return nullptr;
        }

        static bool GetHlslEntryPoint(std::string& entry_point, Graphics::GpuShaderStage stage) noexcept
        {
            auto prefix = GetHlslStagePrefix(stage);
            if (prefix != nullptr)
            {
                entry_point = prefix;
                entry_point += "_main";
                return true;
            }

            return false;
        }

        static bool GetHlslEntryPoint(std::wstring& entry_point, Graphics::GpuShaderStage stage) noexcept
        {
            std::string result{};
            if (GetHlslEntryPoint(result, stage))
            {
                entry_point = System::Impl::WidenString(result);
                return true;
            }

            return false;
        }

        static bool GetHlslProfileName(std::string& name, Graphics::GpuShaderStage stage, Graphics::GpuShaderProfile profile) noexcept
        {
            auto prefix = GetHlslStagePrefix(stage);
            auto suffix = GetHlslProfileSuffix(profile);

            if (prefix != nullptr && suffix != nullptr)
            {
                name = prefix;
                name += '_';
                name += suffix;
                return true;
            }

            return false;
        }

        static bool GetHlslProfileName(std::wstring& name, Graphics::GpuShaderStage stage, Graphics::GpuShaderProfile profile) noexcept
        {
            std::string result{};
            if (GetHlslProfileName(result, stage, profile))
            {
                name = System::Impl::WidenString(result);
                return true;
            }

            return false;
        }


        static std::vector<std::pair<std::wstring, std::wstring>> SanitizeMacrosW(const ShaderCompilerInput& input) noexcept
        {
            std::vector<std::pair<std::wstring, std::wstring>> result{};

            for (auto&& item : input.Definitions)
            {
                result.push_back(
                    std::make_pair(
                        System::Impl::WidenString(item.first),
                        System::Impl::WidenString(item.second)
                   )
               );
            }

            return result;
        }

        static std::vector<std::pair<std::string, std::string>> SanitizeMacros(const ShaderCompilerInput& input) noexcept
        {
            std::vector<std::pair<std::string, std::string>> result{};

            for (auto&& item : input.Definitions)
            {
                result.push_back(
                    std::make_pair(
                        item.first,
                        item.second
                    )
                );
            }

            return result;
        }
    };
}

#endif
