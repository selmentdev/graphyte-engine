#include <GxAssetsBase/AssetsPipeline/AssetProcessorFactory.hxx>

namespace Graphyte::AssetsPipeline
{
    AssetProcessorFactory& AssetProcessorFactory::Get() noexcept
    {
        static AssetProcessorFactory instance{};
        return instance;
    }

    bool AssetProcessorFactory::Register(std::string_view key, ActivateInstanceDelegate activateInstance) noexcept
    {
        auto result = m_Registry.insert(std::make_pair(std::string{ key }, activateInstance));
        return result.second;
    }

    bool AssetProcessorFactory::Unregister(std::string_view key) noexcept
    {
        auto count = m_Registry.erase(std::string{ key });
        return count > 0;
    }

    std::vector<std::string> AssetProcessorFactory::GetNames() const noexcept
    {
        std::vector<std::string> result{};

        for (const auto& item : m_Registry)
        {
            result.push_back(item.first);
        }

        return result;
    }

    std::unique_ptr<IAssetProcessor> AssetProcessorFactory::ActivateInstance(std::string_view key) noexcept
    {
        auto it = m_Registry.find(std::string{ key });

        if (it != m_Registry.end())
        {
            return it->second.Invoke();
        }

        return nullptr;
    }
}
