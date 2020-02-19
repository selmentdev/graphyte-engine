#include <Graphyte/System.hxx>
#include <Graphyte/Storage/IFileSystem.hxx>
#include <Graphyte/Storage/Path.hxx>

#include "../Platform.impl.hxx"

#include <SDL2/SDL.h>

namespace Graphyte::System
{
    BASE_API Status GetClipboardContent(
        std::string& content
    ) noexcept
    {
        auto* text = SDL_GetClipboardText();

        auto result = text != nullptr;

        GX_ASSERTF(result, "Getting clipboard content failed: `{}`", SDL_GetError());

        if (result)
        {
            content.assign(text);
        }
        else
        {
            content.clear();
        }

        SDL_free(text);

        if (result)
        {
            return Status::Success;
        }

        return Status::Failure;
    }

    BASE_API Status SetClipboardContent(
        std::string_view content
    ) noexcept
    {
        std::string str{ content };

        auto result = SDL_SetClipboardText(str.c_str()) == 0;
        GX_ASSERTF(result, "Cannot set clipboard content: `{}`", SDL_GetError());

        if (result)
        {
            return Status::Success;
        }

        return Status::Failure;
    }

    BASE_API Status GetEnvironmentVariable(
        std::string& result,
        const char* name
    ) noexcept
    {
        GX_ASSERT(name != nullptr);

        auto const* variable = secure_getenv(name);
        auto const has_variable = (variable != nullptr);

        if (has_variable)
        {
            result.assign(variable);
            return Status::Success;
        }

        return Status::Failure;
    }

    BASE_API Status SetEnvironmentVariable(
        const char* name,
        const char* value
    ) noexcept
    {
        GX_ASSERT(name != nullptr);

        bool result;

        if (value == nullptr || value[0] == '\0')
        {
            result = unsetenv(name) == 0;
        }
        else
        {
            result = setenv(name, value, 1) == 0;
        }

        return result
            ? Status::Success
            : Status::Failure;
    }

    BASE_API Status RemoveEnvironmentVariable(
        const char* name
    ) noexcept
    {
        GX_ASSERT(name != nullptr);

        bool result = unsetenv(name) == 0;

        return result
            ? Status::Success
            : Status::Failure;
    }

    BASE_API Status SetCurrentDirectory(
        [[maybe_unused]] const std::string& value
    ) noexcept
    {
        if (chdir(value.c_str()) == 0)
        {
            return Status::Success;
        }

        return Diagnostics::GetStatusFromErrno(errno);
    }

    BASE_API Status GetCurrentDirectory(
        std::string& result
    ) noexcept
    {
        std::array<char, PATH_MAX> path{};
        auto cwd = getcwd(path.data(), path.size());
        
        GX_ASSERT(cwd != nullptr);
        
        if (cwd != nullptr)
        {
            result.assign(cwd);
            Storage::Path::AddDirectorySeparator(result);

            return Status::Success;
        }

        return Status::Failure;
    }

    BASE_API std::string GetExecutablePath() noexcept
    {
        std::array<char, PATH_MAX> procpath{};
        std::array<char, PATH_MAX> execpath{};

        pid_t pid = getpid();
        snprintf(std::data(procpath), std::size(procpath), "/proc/%d/exe", pid);
        ssize_t length = readlink(procpath.data(), execpath.data(), execpath.size());
        GX_ASSERT(length >= 0);
        length = std::max<ssize_t>(0, length);

        return std::string{ execpath.data(), static_cast<size_t>(length) };
    }

    BASE_API std::string GetExecutableName() noexcept
    {
        std::array<char, PATH_MAX> procpath{};
        std::array<char, PATH_MAX> execpath{};

        pid_t pid = getpid();
        snprintf(std::data(procpath), std::size(procpath), "/proc/%d/exe", pid);
        ssize_t length = readlink(procpath.data(), execpath.data(), execpath.size());
        GX_ASSERT(length >= 0);
        length = std::max<ssize_t>(0, length);

        return Storage::Path::GetBaseFilename({ execpath.data(), static_cast<size_t>(length) });
    }

    BASE_API std::string GetBaseDirectory() noexcept
    {
        std::array<char, PATH_MAX> procpath{};
        std::array<char, PATH_MAX> execpath{};

        pid_t pid = getpid();
        snprintf(std::data(procpath), std::size(procpath), "/proc/%d/exe", pid);
        ssize_t length = readlink(procpath.data(), execpath.data(), execpath.size());
        GX_ASSERT(length >= 0);
        length = std::max<ssize_t>(0, length);

        return Storage::Path::GetPath({ execpath.data(), static_cast<size_t>(length) });
    }


    BASE_API Status Execute(
        const char* type,
        const char* command,
        const char* params
    ) noexcept
    {
        (void)type;
        (void)command;
        (void)params;
        return Status::NotImplemented;
    }

    BASE_API Status Explore(
        const char* path
    ) noexcept
    {
        (void)path;
        return Status::NotImplemented;
    }
}
