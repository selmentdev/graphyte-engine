#include <GxBase/System.hxx>
#include "../Platform.impl.hxx"

#include <SDL2/SDL.h>

namespace Graphyte::System::Impl
{
    const std::array<const SDL_MessageBoxButtonData, 1> MessageDialogButtons_Ok = {
        {
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
                static_cast<int>(MessageDialogResult::Ok),
                "OK" },
        }
    };

    const std::array<const SDL_MessageBoxButtonData, 2> MessageDialogButtons_OkCancel = {
        {
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
                static_cast<int>(MessageDialogResult::Ok),
                "OK" },
            { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
                static_cast<int>(MessageDialogResult::Cancel),
                "Cancel" },
        }
    };

    const std::array<const SDL_MessageBoxButtonData, 2> MessageDialogButtons_YesNo = {
        {
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
                static_cast<int>(MessageDialogResult::Yes),
                "Yes" },
            { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
                static_cast<int>(MessageDialogResult::No),
                "No" },
        }
    };

    const std::array<const SDL_MessageBoxButtonData, 3> MessageDialogButtons_YesNoCancel = {
        {
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
                static_cast<int>(MessageDialogResult::Yes),
                "Yes" },
            { 0,
                static_cast<int>(MessageDialogResult::No),
                "No" },
            { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
                static_cast<int>(MessageDialogResult::Cancel),
                "Cancel" },
        }
    };

    const std::array<const SDL_MessageBoxButtonData, 3> MessageDialogButtons_CancelTryContinue = {
        {
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT | SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
                static_cast<int>(MessageDialogResult::Cancel),
                "Cancel" },
            { 0,
                static_cast<int>(MessageDialogResult::Try),
                "Try" },
            { 0,
                static_cast<int>(MessageDialogResult::Continue),
                "Continue" },
        }
    };

    static std::span<const SDL_MessageBoxButtonData> GetMessageButtons(
        MessageDialogType type) noexcept
    {
        switch (type)
        {
            case MessageDialogType::Ok:
            {
                return { Impl::MessageDialogButtons_Ok };
            }
            case MessageDialogType::OkCancel:
            {
                return { Impl::MessageDialogButtons_OkCancel };
            }
            case MessageDialogType::YesNo:
            {
                return { Impl::MessageDialogButtons_YesNo };
            }
            case MessageDialogType::YesNoCancel:
            {
                return { Impl::MessageDialogButtons_YesNoCancel };
            }
            case MessageDialogType::CancelTryContinue:
            {
                return { Impl::MessageDialogButtons_CancelTryContinue };
            }
            default:
            {
                break;
            }
        }

        return {};
    }
}

namespace Graphyte::System
{
    BASE_API MessageDialogResult ShowMessageDialog(
        std::string_view title,
        std::string_view message,
        MessageDialogType type,
        MessageDialogImage image) noexcept
    {
        std::string szTitle{ std::data(title), std::size(title) };
        std::string szMessage{ std::data(message), std::size(message) };

        auto&& buttons = Impl::GetMessageButtons(type);

        uint32_t icon{};

        switch (image)
        {
            case MessageDialogImage::None:
            {
                break;
            }

            case MessageDialogImage::Information:
            {
                icon = SDL_MESSAGEBOX_INFORMATION;
                break;
            }

            case MessageDialogImage::Warning:
            {
                icon = SDL_MESSAGEBOX_WARNING;
                break;
            }

            case MessageDialogImage::Error:
            {
                icon = SDL_MESSAGEBOX_ERROR;
                break;
            }
        }

        const SDL_MessageBoxData msgbox = {
            icon,
            nullptr,
            szTitle.c_str(),
            szMessage.c_str(),
            static_cast<int>(buttons.size()),
            buttons.data(),
            nullptr
        };

        int result{};
        int status = SDL_ShowMessageBox(&msgbox, &result);

        GX_ASSERT(status >= 0);
        if (status >= 0)
        {
            return static_cast<MessageDialogResult>(result);
        }

        return MessageDialogResult::None;
    }
}
