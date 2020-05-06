#pragma once
#include <GxBase/Base.module.hxx>

namespace Graphyte
{
    struct BASE_API CommandLineEnumerator final
    {
    private:
        const char** m_ArgV{};
        int m_ArgC{};
        int m_ArgN{};

    public:
        CommandLineEnumerator(
            int argc,
            const char** argv
        ) noexcept;

    public:
        bool Get(
            std::string_view& name,
            std::string_view& value
        ) noexcept;
    };

    class CommandLine final
    {
    public:
        BASE_API static void Initialize(
            int argc,
            const char** argv
        ) noexcept;

        BASE_API static void Finalize() noexcept;

    public:
        BASE_API static bool Get(
            std::string_view name,
            std::string_view& value
        ) noexcept;

        BASE_API static bool Has(
            std::string_view name
        ) noexcept;

        BASE_API static CommandLineEnumerator GetEnumerator() noexcept;
    };
}
