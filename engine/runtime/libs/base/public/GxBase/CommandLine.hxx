#pragma once
#include <GxBase/Base.module.hxx>

namespace Graphyte::CommandLine::Impl
{
    extern BASE_API auto SplitCommandLineNameValue(
        std::string_view value) noexcept -> std::pair<std::string_view, std::optional<std::string_view>>;
}

namespace Graphyte::CommandLine
{
    class Enumerator final
    {
    private:
        std::span<const char* const> m_Args{};
        std::size_t m_Index{};

    public:
        std::string_view Name{};
        std::optional<std::string_view> Value{};

    public:
        Enumerator(std::span<const char* const> args) noexcept
            : m_Args{ args }
            , m_Index{ 0 }
        {
        }

        bool Next() noexcept
        {
            if (m_Index < m_Args.size())
            {
                std::tie(this->Name, this->Value) = Impl::SplitCommandLineNameValue(
                    std::string_view{ m_Args[m_Index] });

                ++m_Index;
                return true;
            }

            return false;
        }

        void Reset() noexcept
        {
            m_Index = 0;
        }
    };

    extern BASE_API void Initialize(size_t argc, const char** argv) noexcept;

    extern BASE_API void Finalize() noexcept;

    extern BASE_API std::optional<std::string_view> Get(std::string_view name) noexcept;

    extern BASE_API CommandLine::Enumerator GetEnumerator() noexcept;
}
