#pragma once

namespace Graphyte
{
    struct IModule
    {
        virtual ~IModule() noexcept = default;

        virtual void OnLoad() noexcept
        {
        }

        virtual void OnUnload() noexcept
        {
        }

        virtual void OnInitialize() noexcept
        {
        }

        virtual void OnFinalize() noexcept
        {
        }
    };
}

#define GX_IMPL_OVERRIDE_OPERATORS()

#define GX_IMPLEMENT_MODULE(module_name) \
    GX_IMPL_OVERRIDE_OPERATORS() \
\
    extern "C" GX_LIB_EXPORT Graphyte::IModule* CreateModule() noexcept \
    { \
        return new module_name(); \
    }
