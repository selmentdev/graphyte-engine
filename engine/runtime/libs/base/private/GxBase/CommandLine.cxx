#include <GxBase/CommandLine.hxx>
#include <GxBase/Diagnostics.hxx>

namespace Graphyte::CommandLine::Impl
{
    static notstd::span<const char*> GCommandLineArgs;

    auto SplitCommandLineNameValue(
        std::string_view value
    ) noexcept->std::pair<std::string_view, std::optional<std::string_view>>
    {
        std::size_t const separator = value.find_first_not_of('=');
        std::string_view const name = value.substr(0, separator);

        bool const has_value = (separator != std::string_view::npos);

        return {
            name,
            has_value
                ? std::make_optional(value.substr(separator + 1))
                : std::nullopt
        };
    }
}

namespace Graphyte::CommandLine
{
    extern BASE_API void Initialize(int argc, const char** argv) noexcept
    {
        GX_ASSERT(argv != nullptr);
        GX_ASSERT(Impl::GCommandLineArgs.empty());

        Impl::GCommandLineArgs = notstd::span<const char*>(argv, argc);
    }

    extern BASE_API void Finalize() noexcept
    {
        GX_ASSERT(!Impl::GCommandLineArgs.empty());

        Impl::GCommandLineArgs = {};
    }

    extern BASE_API std::optional<std::string_view> Get(std::string_view name) noexcept
    {
        for (auto const item : Impl::GCommandLineArgs)
        {
            std::string_view line = item;

            if (auto [parsed_name, value] = Impl::SplitCommandLineNameValue(line); parsed_name == name)
            {
                return value;
            }
        }

        return std::nullopt;
    }

    extern BASE_API CommandLine::Enumerator GetEnumerator() noexcept
    {
        return Enumerator{ Impl::GCommandLineArgs };
    }
}
