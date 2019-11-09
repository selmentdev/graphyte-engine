#include "Base.pch.hxx"
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Status.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>

#include <shellapi.h>
#include <ShlObj.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include <DbgHelp.h>

namespace Graphyte::Diagnostics
{
    BASE_API std::vector<std::string> GetModules() noexcept
    {
        std::vector<std::string> result{};

        //
        // Take snapshot of current process modules list.
        //

        HANDLE snapshot = CreateToolhelp32Snapshot(
            TH32CS_SNAPMODULE,
            0
        );

        if (snapshot != INVALID_HANDLE_VALUE)
        {
            //
            // Iterate over all loaded modules.
            //

            MODULEENTRY32W entry{
                .dwSize = sizeof(entry),
            };

            if (Module32FirstW(snapshot, &entry))
            {
                do
                {
                    result.emplace_back(System::Impl::NarrowString(entry.szModule));
                } while (Module32NextW(snapshot, &entry) != FALSE);
            }

            CloseHandle(snapshot);
        }

        return result;
    }
}
