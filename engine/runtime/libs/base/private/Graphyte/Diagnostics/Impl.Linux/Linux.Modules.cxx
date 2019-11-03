#include "Base.pch.hxx"
#include <Graphyte/Diagnostics.hxx>

#include <link.h>

namespace Graphyte::Diagnostics
{
    BASE_API std::vector<std::string> GetModules() noexcept
    {
        std::vector<std::string> result{};
        dl_iterate_phdr(
            [](struct dl_phdr_info* info, size_t size, void* context) -> int
            {
                auto* modules = reinterpret_cast<std::vector<std::string>*>(context);
                GX_ASSERT(modules != nullptr);
                GX_ASSERT(size != 0);

                modules->emplace_back(info->dlpi_name);
                return 0;
            },
            reinterpret_cast<void*>(&result)
        );

        return result;
    }
}
