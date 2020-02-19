#pragma once
#include <Graphyte/Delegate.hxx>
#include <Graphyte/AssetsPipeline/AssetProcessor.hxx>

namespace Graphyte::AssetsPipeline
{
    class ASSETS_BASE_API AssetProcessorFactory final
    {
    public:
        using ActivateInstanceDelegate = Delegate<std::unique_ptr<IAssetProcessor>(void)>;

    private:
        std::map<std::string, ActivateInstanceDelegate> m_Registry;

    public:
        static AssetProcessorFactory& Get() noexcept;

    public:
        bool Register(std::string_view key, ActivateInstanceDelegate activateInstance) noexcept;
        bool Unregister(std::string_view key) noexcept;
        std::vector<std::string> GetNames() const noexcept;

        std::unique_ptr<IAssetProcessor> ActivateInstance(std::string_view key) noexcept;
    };
}
