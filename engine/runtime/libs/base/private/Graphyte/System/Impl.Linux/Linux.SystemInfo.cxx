#include <Graphyte/System.hxx>
#include <Graphyte/Storage/Path.hxx>
#include <Graphyte/Diagnostics.hxx>

#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <sys/resource.h>
#include <limits.h>
#include <stdio.h>
#include <pwd.h>
#include <fstream>

namespace Graphyte::System
{
    BASE_API std::string GetUserDirectory() noexcept
    {
        std::string result{};
        const char* value = secure_getenv("HOME");

        if (value != nullptr)
        {
            result.assign(value);
        }
        else
        {
            struct passwd* userinfo = getpwuid(geteuid());

            if (userinfo != nullptr && userinfo->pw_dir != nullptr)
            {
                result.assign(userinfo->pw_dir);
            }
        }

        Storage::Path::AddDirectorySeparator(result);

        return result;
    }

    BASE_API std::string GetUserDocumentsDirectory() noexcept
    {
        static std::string result{};

        if (result.empty())
        {
            FILE* file = popen("xdg-user-dir DOCUMENTS", "r");
            
            if (file != nullptr)
            {
                std::array<char, PATH_MAX> path{};
                if (fgets(path.data(), path.size(), file) != nullptr)
                {
                    std::string_view path_view{ path.data() };
                    path_view.remove_suffix(1);
                    result.assign(path_view);
                    Storage::Path::AddDirectorySeparator(result);
                }
                pclose(file);
            }
        }

        if (result.empty())
        {
            if (GetEnvironmentVariable(result, "HOME") == Status::Success)
            {
                Storage::Path::Append(result, "/Documents/");
            }
        }

        Storage::Path::AddDirectorySeparator(result);

        return result;
    }

    BASE_API std::string GetUserTemporaryDirectory() noexcept
    {
        const char* value = secure_getenv("TMPDIR");

        if (value == nullptr)
        {
            value = secure_getenv("TMP");
        }

        if (value == nullptr)
        {
            value = secure_getenv("TEMP");
        }

        if (value == nullptr)
        {
            value = secure_getenv("TEMPDIR");
        }

        if (value == nullptr)
        {
            value = "/tmp/";
        }

        return value;
    }

    BASE_API std::string GetUserSettingsDirectory() noexcept
    {
        std::string result = GetUserDirectory();
        Storage::Path::Append(result, ".config/");
        return result;
    }

    BASE_API std::string GetApplicationCommonDataDirectory() noexcept
    {
        std::string result = GetUserDirectory();
        Storage::Path::Append(result, ".config/");
        return result;
    }

    BASE_API std::string GetUserDomain() noexcept
    {
        struct utsname name {};

        std::string result{};

        std::array<char, HOST_NAME_MAX> hostname{};

        if (uname(&name) == 0)
        {
            result.assign(name.nodename);
        }
        else if (gethostname(hostname.data(), hostname.size()) == 0)
        {
            result.assign(hostname.data());
        }
        else
        {
            result.assign("Linux Machine");
        }

        return result;
    }

    BASE_API std::string GetUserName() noexcept
    {
        if constexpr (false)
        {
            std::string result{};
            std::array<char, LOGIN_NAME_MAX> userid{};

            if (getlogin_r(userid.data(), userid.size()) == 0)
            {
                result.assign(userid.data());
                GX_ABORT("boi\n");
            }
            else
            {
                GX_ABORT("fug: {} {}\n", strerror(errno), errno);
            }

            return result;
        }
        else
        {
            uid_t uid = geteuid();
            struct passwd* pw = getpwuid(uid);

            if (pw != nullptr)
            {
                return pw->pw_name;
            }

            return {};
        }
    }

    BASE_API std::string GetSystemVersion() noexcept
    {
        // TODO: add parsing `/etc/lsb-release` if available
        
        std::string result{};

        struct utsname utsname {};
        if (uname(&utsname) != -1)
        {
            result = fmt::format("{}-{}-{}", utsname.sysname, utsname.release, utsname.version);
        }

        return result;
    }

    BASE_API std::string GetSystemId() noexcept
    {
        std::array<char, 64> buffer{};

        int fd = open("/etc/machine-id", O_RDONLY);

        if (fd != -1)
        {
            ssize_t processed = read(fd, buffer.data(), buffer.size() - 1);

            if (processed > 0)
            {
                buffer[static_cast<size_t>(processed)] = 0;
            }

            close(fd);
        }

        return buffer.data();
    }

    BASE_API std::string GetDefaultLocale() noexcept
    {
        return "en-us";
    }

    BASE_API std::string GetDefaultLanguage() noexcept
    {
        return "en";
    }

    BASE_API std::string GetLocalCurrencyCode() noexcept
    {
        return {};
    }

    BASE_API std::string GetLocalCurrencySymbol() noexcept
    {
        return {};
    }

    BASE_API bool HasActiveWifiConnection() noexcept
    {
        return true;
    }

    BASE_API bool Is64BitOperatingSystem() noexcept
    {
#if GRAPHYTE_ARCH_64BIT
        return true;
#else
        return false;
#endif
    }

    BASE_API bool Is64BitProcess() noexcept
    {
#if GRAPHYTE_ARCH_64BIT
        return true;
#else
        return false;
#endif
    }

    BASE_API bool IsMousePresent() noexcept
    {
        return true;
    }

    BASE_API bool IsMouseWheelPresent() noexcept
    {
        return true;
    }

    BASE_API bool IsLittleEndian() noexcept
    {
#if GRAPHYTE_ENDIAN_LITTLE
        return true;
#else
        return false;
#endif
    }

    BASE_API void* GetHardwareWindow() noexcept
    {
        return nullptr;
    }
}
