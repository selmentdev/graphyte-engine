#include "Base.pch.hxx"
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Platform.hxx>

#include "../Diagnostics.Impl.hxx"

#include <SDL2/SDL.h>

#include <sys/types.h>
#include <csignal>
#include <execinfo.h>

namespace Graphyte::Diagnostics::Impl
{
    bool ReportAbort(
        std::string_view title,
        std::string_view content,
        std::string_view stacktrace
    ) noexcept
    {
        std::string umessage = "Abort:\n\n";
        umessage += content;
        umessage += "\n\nStackTrace:\n";
        umessage += stacktrace;

        std::string utitle{ title };

        const SDL_MessageBoxButtonData buttons[] = {
            {
                SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT | SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
                0,
                "OK"
            },
        };

        const SDL_MessageBoxData msgbox = {
            SDL_MESSAGEBOX_ERROR,
            nullptr,
            utitle.c_str(),
            umessage.c_str(),
            SDL_arraysize(buttons),
            buttons,
            nullptr
        };

        [[maybe_unused]] int result = 0;

        SDL_ShowMessageBox(&msgbox, &result);

        return false;
    }
}
