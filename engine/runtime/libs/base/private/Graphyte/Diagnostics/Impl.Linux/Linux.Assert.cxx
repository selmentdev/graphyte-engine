#include "Base.pch.hxx"
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/System.hxx>

#include "../Diagnostics.Impl.hxx"

#include <SDL2/SDL.h>

#include <sys/types.h>
#include <signal.h>
#include <execinfo.h>


namespace Graphyte::Diagnostics::Impl
{
    AssertResult ReportAssertion(
        std::string_view title,
        std::string_view content,
        std::string_view stacktrace
    ) noexcept
    {
        const SDL_MessageBoxButtonData buttons[] = {
            {
                0,
                static_cast<int>(AssertResult::Abort),
                "Abort"
            },
            {
                SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
                static_cast<int>(AssertResult::Retry),
                "Retry"
            },
            {
                SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
                static_cast<int>(AssertResult::Ignore),
                "Ignore"
            },
            {
                0,
                static_cast<int>(AssertResult::IgnoreAlways),
                "Ignore Always"
            },
        };

        std::string utitle{ title };

        std::string ucontent = "Assert:\n\n";
        ucontent += content;
        ucontent += "\n\nStackTrace:\n";
        ucontent += stacktrace;

        const SDL_MessageBoxData msgbox = {
            SDL_MESSAGEBOX_ERROR,
            nullptr,
            utitle.c_str(),
            ucontent.c_str(),
            SDL_arraysize(buttons),
            buttons,
            nullptr
        };

        int result = 0;

        if (SDL_ShowMessageBox(&msgbox, &result) < 0)
        {
            return AssertResult::Ignore;
        }

        return static_cast<AssertResult>(result);
    }
}
