#include <GxBase/Console.hxx>


// =================================================================================================
//
// Console variable implementation.
//

namespace Graphyte
{
    ConsoleVariableBase::ConsoleVariableBase(
        ConsoleObjectFlags flags,
        std::string_view name,
        std::string_view help,
        std::string_view store) noexcept
        : m_Flags{ flags }
        , m_Name{ name }
        , m_Help{ help }
        , m_Store{ store }
    {
        Console::Register(this);
    }

    ConsoleVariableBase::~ConsoleVariableBase() noexcept
    {
        Console::Unregister(this);
    }
}


// =================================================================================================
//
// Console command implementation.
//

namespace Graphyte
{
    ConsoleCommand::ConsoleCommand(
        ConsoleObjectFlags flags,
        std::string_view name,
        ConsoleCommandDelegate action,
        std::string_view help) noexcept
        : m_Flags{ flags }
        , m_Name{ name }
        , m_Help{ help }
        , m_Action{ std::move(action) }
    {
        Console::Register(this);
    }

    ConsoleCommand::~ConsoleCommand() noexcept
    {
        Console::Unregister(this);
    }

    ConsoleCommandResult ConsoleCommand::Execute(
        notstd::span<std::string_view> params) noexcept
    {
        return this->m_Action(params);
    }
}


// =================================================================================================
//
// Console implementation.
//

namespace Graphyte
{
    struct ConsoleDetail final
    {
        IntrusiveList<IConsoleVariable, &IConsoleVariable::ListEntry> Variables;
        IntrusiveList<IConsoleCommand, &IConsoleCommand::ListEntry> Commands;
    } g_ConsoleDetail;

    void Console::Initialize() noexcept
    {
    }

    void Console::Finalize() noexcept
    {
    }

    void Console::Register(
        ConsoleVariableBase* variable) noexcept
    {
        g_ConsoleDetail.Variables.InsertTail(variable);
    }

    void Console::Unregister(
        ConsoleVariableBase* variable) noexcept
    {
        g_ConsoleDetail.Variables.Remove(variable);
    }

    void Console::Register(
        ConsoleCommand* command) noexcept
    {
        g_ConsoleDetail.Commands.InsertTail(command);
    }

    void Console::Unregister(
        ConsoleCommand* command) noexcept
    {
        g_ConsoleDetail.Commands.Remove(command);
    }

    bool Console::SetValue(
        std::string_view name,
        std::string_view value) noexcept
    {
        if (auto* variable = FindVariable(name); variable != nullptr)
        {
            return variable->FromString(value);
        }

        return false;
    }

    bool Console::GetValue(
        std::string& out_result,
        std::string_view name) noexcept
    {
        if (auto* variable = FindVariable(name); variable != nullptr)
        {
            out_result = variable->ToString();
            return true;
        }

        return false;
    }

    ConsoleCommandResult Console::Execute(
        std::string_view command,
        std::string_view params) noexcept
    {
        notstd::span<std::string_view> params_view{ &params, 1 };

        return Execute(command, params_view);
    }

    ConsoleCommandResult Console::Execute(
        std::string_view command,
        notstd::span<std::string_view> params) noexcept
    {
        if (auto item = FindCommand(command); item != nullptr)
        {
            return item->Execute(params);
        }

        return ConsoleCommandResult::NotFound;
    }

    BASE_API void Console::EnumerateVariables(
        std::vector<std::string_view>& variables) noexcept
    {
        variables.clear();

        auto& list = g_ConsoleDetail.Variables;

        for (IConsoleVariable* item = list.GetHead(); item != nullptr; item = list.Next(item))
        {
            variables.push_back(item->GetName());
        }
    }

    BASE_API void Console::EnumerateCommands(
        std::vector<std::string_view>& commands) noexcept
    {
        commands.clear();

        auto& list = g_ConsoleDetail.Commands;

        for (IConsoleCommand* item = list.GetHead(); item != nullptr; item = list.Next(item))
        {
            commands.push_back(item->GetName());
        }
    }

    IConsoleVariable* Console::FindVariable(
        std::string_view name) noexcept
    {
        auto& list = g_ConsoleDetail.Variables;

        for (IConsoleVariable* item = list.GetHead(); item != nullptr; item = list.Next(item))
        {
            if (item->GetName() == name)
            {
                return item;
            }
        }

        return nullptr;
    }

    IConsoleCommand* Console::FindCommand(
        std::string_view name) noexcept
    {
        auto& list = g_ConsoleDetail.Commands;

        for (IConsoleCommand* item = list.GetHead(); item != nullptr; item = list.Next(item))
        {
            if (item->GetName() == name)
            {
                return item;
            }
        }

        return nullptr;
    }
}


// =================================================================================================
//
// ConsoleCommandResult util functions.
//

namespace Graphyte
{
    BASE_API std::string_view Converter<ConsoleCommandResult>::ToString(ConsoleCommandResult value) noexcept
    {
        switch (value)
        {
            case ConsoleCommandResult::Success:
                return "Success";
            case ConsoleCommandResult::Failed:
                return "Failed";
            case ConsoleCommandResult::InvalidArgument:
                return "InvalidArgument";
            case ConsoleCommandResult::NotEnoughArguments:
                return "NotEnoughArguments";
            case ConsoleCommandResult::NotFound:
                return "NotFound";
        }

        return {};
    }
}
