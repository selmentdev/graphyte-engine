#include "Base.pch.hxx"
#include <Graphyte/CommandLine.hxx>
#include <Graphyte/Diagnostics.hxx>

namespace Graphyte
{
    CommandLineEnumerator::CommandLineEnumerator(
        int argc,
        const char** argv
    ) noexcept
        : m_ArgV{ argv }
        , m_ArgC{ argc }
        , m_ArgN{ 1 }
    {
    }

    bool CommandLineEnumerator::Get(
        std::string_view& name,
        std::string_view& value
    ) noexcept
    {
        if (m_ArgN >= m_ArgC)
        {
            name = value = {};
            return false;
        }

        std::string_view item{ m_ArgV[m_ArgN++] };


        //
        // Option name will be either whole item or substring up to '=' character.
        //

        auto offset = item.find_first_of('=');

        // Name is [0..offset]
        name = item.substr(0, offset);

        if (offset != std::string_view::npos)
        {
            // Value is [offset..end]
            value = item.substr(offset + 1);
        }
        else
        {
            value = {};
        }

        return true;
    }
}

namespace Graphyte
{
    int GCommandLineArgC{ 0 };
    const char** GCommandLineArgV{ nullptr };

    void CommandLine::Initialize(
        int argc,
        const char** argv
    ) noexcept
    {
        GX_ASSERT(GCommandLineArgV == nullptr);
        GX_ASSERT(argv != nullptr);

        GCommandLineArgC = argc;
        GCommandLineArgV = argv;
    }

    void CommandLine::Finalize() noexcept
    {
        GX_ASSERT(GCommandLineArgV != nullptr);

        GCommandLineArgC = 0;
        GCommandLineArgV = nullptr;
    }

    bool CommandLine::Get(
        std::string_view name,
        std::string_view& value
    ) noexcept
    {
        for (int i = 0; i < GCommandLineArgC; ++i)
        {
            std::string_view item{ GCommandLineArgV[i] };


            //
            // Option name will be either whole item or substring up to '=' character.
            //

            auto offset = item.find_first_of('=');
            auto parsed_name = item.substr(0, offset);

            if (parsed_name == name)
            {
                //
                // Option name matched.
                //

                if (offset != std::string_view::npos)
                {
                    //
                    // Option value will be everything after option name.
                    //

                    value = item.substr(offset + 1);
                }
                else
                {
                    //
                    // If no '=' character could be found, clear value out.
                    //

                    value = {};
                }

                return true;
            }
        }


        //
        // Cannot find that option in command line.
        //

        value = {};

        return false;
    }

    bool CommandLine::Has(
        std::string_view name
    ) noexcept
    {
        [[maybe_unused]] std::string_view value{};
        return CommandLine::Get(name, value);
    }

    CommandLineEnumerator CommandLine::GetEnumerator() noexcept
    {
        return { GCommandLineArgC, GCommandLineArgV };
    }
}
