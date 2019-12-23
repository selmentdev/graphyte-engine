#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Flags.hxx>
#include <Graphyte/Span.hxx>
#include <Graphyte/IntrusiveList.hxx>
#include <Graphyte/Delegate.hxx>
#include <Graphyte/Converter.hxx>


// =================================================================================================
//
// Console interfaces.
//

namespace Graphyte
{
    enum struct ConsoleObjectFlags : uint32_t
    {
        None = 0,
        Cheat = 1 << 0,
        ReadOnly = 1 << 1,
    };
    GX_ENUM_CLASS_FLAGS(ConsoleObjectFlags);

    struct IConsoleObject
    {
        /*!
         * \brief   Gets help string associated with this console object.
         */
        virtual std::string_view GetHelp() const noexcept = 0;

        /*!
         * \brief   Gets name of this console object.
         */
        virtual std::string_view GetName() const noexcept = 0;

        /*!
         * \brief   Gets flags of this console object.
         */
        virtual ConsoleObjectFlags GetFlags() const noexcept = 0;
    };

    struct IConsoleVariable
        : public IConsoleObject
    {
        IntrusiveListNode<IConsoleVariable> ListEntry;

        /*!
         * \brief   Gets store where to put this variable.
         */
        virtual std::string_view GetStore() const noexcept = 0;

        /*!
         * \brief   Sets value of this variable from string.
         *
         * \param   value       Provides value to parse.
         *
         * \return  @c true when succeeded, @c false otherwise.
         */
        virtual bool FromString(
            std::string_view value
        ) noexcept = 0;

        /*!
         * \brief   Gets value of this variable as string.
         *
         * \return  The value converted to string.
         */
        virtual std::string ToString() const noexcept = 0;
    };

    enum struct [[nodiscard]] ConsoleCommandResult : uint32_t
    {
        Success,
        Failed,
        InvalidArgument,
        NotEnoughArguments,
        NotFound,
    };

    struct IConsoleCommand
        : public IConsoleObject
    {
        IntrusiveListNode<IConsoleCommand> ListEntry;

        virtual ConsoleCommandResult Execute(
            notstd::span<std::string_view> params
        ) noexcept = 0;
    };
}


// =================================================================================================
//
// Implementation of console variable.
//

namespace Graphyte
{
    class BASE_API ConsoleVariableBase
        : public IConsoleVariable
    {
    private:
        ConsoleObjectFlags m_Flags;
        std::string_view m_Name;
        std::string_view m_Help;
        std::string_view m_Store;

    public:
        ConsoleVariableBase(
            ConsoleObjectFlags flags,
            std::string_view name,
            std::string_view help,
            std::string_view store
        ) noexcept;

        virtual ~ConsoleVariableBase() noexcept;

        ConsoleVariableBase(const ConsoleVariableBase&) = delete;
        ConsoleVariableBase& operator= (const ConsoleVariableBase&) = delete;

    public:
        virtual std::string_view GetHelp() const noexcept final override
        {
            return m_Help;
        }

        virtual std::string_view GetName() const noexcept final override
        {
            return m_Name;
        }

        virtual ConsoleObjectFlags GetFlags() const noexcept final override
        {
            return m_Flags;
        }

        virtual std::string_view GetStore() const noexcept final override
        {
            return m_Store;
        }
    };

    template <typename T>
    class ConsoleVariable final
        : public ConsoleVariableBase
    {
    public:
        T Value;

    public:
        ConsoleVariable(
            ConsoleObjectFlags flags,
            std::string_view name,
            std::string_view help = {},
            std::string_view store = {}
        ) noexcept
            : ConsoleVariableBase(flags, name, help, store)
            , Value{}
        {
        }

        ConsoleVariable(
            const T& value,
            ConsoleObjectFlags flags,
            std::string_view name,
            std::string_view help = {},
            std::string_view store = {}
        ) noexcept
            : ConsoleVariableBase(flags, name, help, store)
            , Value{ value }
        {
        }

    public:
        virtual bool FromString(
            std::string_view value
        ) noexcept final override
        {
            if constexpr (std::is_same_v<std::string, T>)
            {
                this->Value = value;
                return true;
            }
            else
            {
                return Converter<T>::FromString(this->Value, value);
            }
        }

        virtual std::string ToString() const noexcept final override
        {
            if constexpr (std::is_same_v<std::string, T>)
            {
                return this->Value;
            }
            else
            {
                return Converter<T>::ToString(this->Value);
            }
        }
    };
}


// =================================================================================================
//
// Console command implementation.
//

namespace Graphyte
{
    /*!
     * \brief   Represents delegate callback to execute when console command is invoked.
     *
     * \param   params      Provides command params.
     *
     * \return  The command execution status.
     */
    using ConsoleCommandDelegate = std::function<ConsoleCommandResult(
        notstd::span<std::string_view> params
    )>;

    class BASE_API ConsoleCommand final : public IConsoleCommand
    {
    private:
        ConsoleObjectFlags m_Flags;
        std::string_view m_Name;
        std::string_view m_Help;
        ConsoleCommandDelegate m_Action;

    public:
        ConsoleCommand(
            ConsoleObjectFlags flags,
            std::string_view name,
            ConsoleCommandDelegate action,
            std::string_view help = {}
        ) noexcept;

        virtual ~ConsoleCommand() noexcept;

        ConsoleCommand(const ConsoleCommand&) = delete;
        ConsoleCommand& operator= (const ConsoleCommand&) = delete;

    public:
        virtual std::string_view GetHelp() const noexcept final override
        {
            return m_Help;
        }

        virtual std::string_view GetName() const noexcept final override
        {
            return m_Name;
        }

        virtual ConsoleObjectFlags GetFlags() const noexcept final override
        {
            return m_Flags;
        }

        virtual ConsoleCommandResult Execute(
            notstd::span<std::string_view> params
        ) noexcept final override;
    };
}

// =================================================================================================
//
// Console implementation.
//

namespace Graphyte
{
    class Console final
    {
    public:
        BASE_API static void Initialize() noexcept;

        BASE_API static void Finalize() noexcept;

    public:
        BASE_API static void Register(
            ConsoleVariableBase* variable
        ) noexcept;

        BASE_API static void Unregister(
            ConsoleVariableBase* variable
        ) noexcept;

    public:
        BASE_API static void Register(
            ConsoleCommand* command
        ) noexcept;

        BASE_API static void Unregister(
            ConsoleCommand* command
        ) noexcept;

    public:
        BASE_API static bool SetValue(
            std::string_view name,
            std::string_view value
        ) noexcept;

        BASE_API static bool GetValue(
            std::string& out_result,
            std::string_view name
        ) noexcept;

    public:
        BASE_API static ConsoleCommandResult Execute(
            std::string_view command,
            std::string_view params
        ) noexcept;

        BASE_API static ConsoleCommandResult Execute(
            std::string_view command,
            notstd::span<std::string_view> params
        ) noexcept;

    public:
        /*!
         * \brief   Enumerates all registered variables.
         *
         * \param   variables   Returns list of registered variables.
         *
         * \remarks Returned list must not be persisted, because variable instance may be
         *          unloaded.
         */
        BASE_API static void EnumerateVariables(
            std::vector<std::string_view>& variables
        ) noexcept;

        /*!
         * \brief   Enumerates all registered commands.
         *
         * \param   commands    Returns list of registered commands.
         *
         * \remarks Returned list must not be persisted, because variable instance may be
         *          unloaded.
         */
        BASE_API static void EnumerateCommands(
            std::vector<std::string_view>& commands
        ) noexcept;

    private:
        BASE_API static IConsoleVariable* FindVariable(
            std::string_view name
        ) noexcept;

        BASE_API static IConsoleCommand* FindCommand(
            std::string_view name
        ) noexcept;
    };
}

namespace Graphyte
{
    template <>
    struct Converter<ConsoleCommandResult> final
    {
        BASE_API static std::string_view ToString(ConsoleCommandResult value) noexcept;
    };
}

template <>
struct fmt::formatter<Graphyte::ConsoleCommandResult> : fmt::formatter<std::string_view>
{
    template <typename FormatContext>
    auto format(Graphyte::ConsoleCommandResult value, FormatContext& context)
    {
        std::string_view result{ "unknown" };

        switch (value)
        {
            case Graphyte::ConsoleCommandResult::Success:
                result = "Success";
                break;

            case Graphyte::ConsoleCommandResult::Failed:
                result = "Failed";
                break;

            case Graphyte::ConsoleCommandResult::InvalidArgument:
                result = "InvalidArgument";
                break;

            case Graphyte::ConsoleCommandResult::NotEnoughArguments:
                result = "NotEnoughArguments";
                break;

            case Graphyte::ConsoleCommandResult::NotFound:
                result = "NotFound";
                break;
        }

        return fmt::formatter<std::string_view>::format(result, context);
    }
};
