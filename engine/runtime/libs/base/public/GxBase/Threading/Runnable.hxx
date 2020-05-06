#pragma once
#include <GxBase/Base.module.hxx>

namespace Graphyte::Threading
{
    class IRunnable
    {
    public:
        virtual ~IRunnable() noexcept
        {
        }

        virtual uint32_t OnRun() noexcept = 0;

        virtual bool OnStart() noexcept
        {
            return true;
        }

        virtual void OnStop() noexcept
        {
        }

        virtual void OnExit() noexcept
        {
        }
    };
}
