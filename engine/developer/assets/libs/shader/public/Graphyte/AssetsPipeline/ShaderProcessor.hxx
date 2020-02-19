#pragma once
#include <Graphyte/AssetsPipeline/AssetProcessor.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/System.hxx>
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>

namespace Graphyte::AssetsPipeline
{
    GX_DECLARE_LOG_CATEGORY(LogShaderCompilerFrontend, Trace, Trace);

    enum class ShaderOptimizationLevel
    {
        Level0,
        Level1,
        Level2,
        Level3,
        Level4,
    };

    std::string_view ToString(System::PlatformType value) noexcept;
    std::string_view ToString(Graphics::GpuRenderAPI value) noexcept;
    std::string_view ToString(Graphics::GpuShaderProfile value) noexcept;
    std::string_view ToString(Graphics::GpuShaderStage value) noexcept;

    bool FromString(System::PlatformType& result, std::string_view value) noexcept;
    bool FromString(Graphics::GpuRenderAPI& result, std::string_view value) noexcept;
    bool FromString(Graphics::GpuShaderProfile& result, std::string_view value) noexcept;
    bool FromString(Graphics::GpuShaderStage& result, std::string_view value) noexcept;

    class ShaderCompilerInput final
    {
    public:
        std::string Source;
        std::string FileName;
        std::string EntryName;
        std::map<std::string, std::string> Definitions;

        System::PlatformType Platform;
        Graphics::GpuRenderAPI RenderAPI;
        Graphics::GpuShaderProfile Profile;
        Graphics::GpuShaderStage Stage;

        bool EnableAggresiveFlattening = false;
        bool Enable16BitTypes = false;
        bool EnableStrictMode = true;
        bool AvoidFlowControlConstructs = false;
        bool PreferFlowControlConstructs = false;
        bool ForceIEEE = false;
        bool SuppressWarnings = false;
        bool DisableOptimizations = false;
        bool DisableValidation = false;
        bool WarningsAsErrors = false;
        bool EnableDebugInfo = false;

        ShaderOptimizationLevel OptimizationLevel;

        std::string BuildFileName() const noexcept;

        uint64_t GetHash() const noexcept;
    };

    class ShaderCompilerOutput final
    {
    public:
        std::vector<std::byte> Bytecode;
        std::vector<std::string> Log;
        std::string FileName;
        bool Success;
    };

    struct IShaderCompilerBackend
    {
    public:
        virtual ~IShaderCompilerBackend() noexcept;
        virtual bool IsSupported(ShaderCompilerInput& input) const noexcept = 0;
        virtual bool Compile(ShaderCompilerInput& input, ShaderCompilerOutput& output) const noexcept = 0;
    };

    class ShaderProcessor final : public IAssetProcessor
    {
    private:
        std::vector<std::unique_ptr<IShaderCompilerBackend>> m_Backends;

    public:
        ShaderProcessor() noexcept;
        virtual ~ShaderProcessor() noexcept;

        bool Process(const AssetProcessorRequest& request, AssetProcessorResponse& response) noexcept override;
        bool Process() noexcept override;

    public:
        //bool Serialize(Serialization::Writer::Value& value) noexcept override;
        //bool Deserialize(Serialization::Reader::Value& value) noexcept override;
    };
}
