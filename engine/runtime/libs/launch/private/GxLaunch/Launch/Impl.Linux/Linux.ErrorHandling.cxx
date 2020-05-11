#include <GxBase/Diagnostics.hxx>

#include <sys/types.h>
#include <sys/resource.h>
#include <signal.h>

namespace Graphyte::Launch::Impl::Posix
{
    static struct sigaction GPreviousSIGILL;
    static struct sigaction GPreviousSIGTRAP;
    static struct sigaction GPreviousSIGFPE;
    static struct sigaction GPreviousSIGBUS;
    static struct sigaction GPreviousSIGSEGV;
    static struct sigaction GPreviousSIGINT;
    static struct sigaction GPreviousSIGQUIT;

    using SignalFunction = void (*)(int, siginfo_t *, void *);

    static void SetSignal(int id, SignalFunction function, struct sigaction* previous, int flags = 0, bool skip = false) noexcept
    {
        struct sigaction ac;
        ac.sa_flags = SA_SIGINFO | SA_RESTART | flags;
        ac.sa_handler = nullptr;
        ac.sa_sigaction = function;
        sigemptyset(&ac.sa_mask);

        if (skip)
        {
            if (sigaction(id, nullptr, previous) == -1)
            {
                GX_ABORT("Cannot setup signal handler: {} ({})", errno, strerror(errno));
            }
            else if (previous != nullptr && previous->sa_handler == SIG_IGN)
            {
                return;
            }
        }

        if (sigaction(id, &ac, previous) == -1)
        {
            GX_ABORT("Cannot setup signal handler: {} ({})", errno, strerror(errno));
        }
    }

    static void TerminateHandler() noexcept
    {
        GX_ABORT("Terminate handler");
    }

    static void HandleSignalKill(
        int signal_number,
        siginfo_t* signal_info,
        void* context
    ) noexcept
    {
        (void)signal_number;
        Diagnostics::OnCrash(reinterpret_cast<ucontext_t*>(context), signal_info);
    }

    static void HandleSignalTrap(
        int signal_number,
        siginfo_t* signal_info,
        void* context
    ) noexcept
    {
        (void)signal_number;
        Diagnostics::OnCrash(reinterpret_cast<ucontext_t*>(context), signal_info);
    }

    static void HandleSignalFpe(
        int signal_number,
        siginfo_t* signal_info,
        void* context
    ) noexcept
    {
        (void)signal_number;
        Diagnostics::OnCrash(reinterpret_cast<ucontext_t*>(context), signal_info);
    }

    static void HandleSignalBus(
        int signal_number,
        siginfo_t* signal_info,
        void* context
    ) noexcept
    {
        (void)signal_number;
        Diagnostics::OnCrash(reinterpret_cast<ucontext_t*>(context), signal_info);
    }

    static void HandleSignalSegv(
        int signal_number,
        siginfo_t* signal_info,
        void* context
    ) noexcept
    {
        (void)signal_number;
        Diagnostics::OnCrash(reinterpret_cast<ucontext_t*>(context), signal_info);
    }

    static void HandleSignalInt(
        int signal_number,
        siginfo_t* signal_info,
        void* context
    ) noexcept
    {
        (void)signal_number;
        Diagnostics::OnCrash(reinterpret_cast<ucontext_t*>(context), signal_info);
    }

    static void HandleSignalQuit(
        int signal_number,
        siginfo_t* signal_info,
        void* context
    ) noexcept
    {
        (void)signal_number;
        Diagnostics::OnCrash(reinterpret_cast<ucontext_t*>(context), signal_info);
    }

    static bool SetResourceLimit(int resource, rlim_t value, bool increase) noexcept
    {
        struct rlimit limit{};
        if (getrlimit(resource, &limit) != 0)
        {
            return false;
        }

        if (increase && (limit.rlim_cur == RLIM_INFINITY || limit.rlim_cur >= value))
        {
            return true;
        }

        limit.rlim_cur = value;
        if (setrlimit(resource, &limit) != 0)
        {
            return false;
        }

        return true;
    }

    static void SetupSignalHandlers() noexcept
    {
        SetSignal(SIGILL,  HandleSignalKill, &GPreviousSIGILL);
        SetSignal(SIGTRAP, HandleSignalTrap, &GPreviousSIGTRAP);
        SetSignal(SIGFPE,  HandleSignalFpe, &GPreviousSIGFPE);
        SetSignal(SIGBUS,  HandleSignalBus, &GPreviousSIGBUS);
        SetSignal(SIGSEGV, HandleSignalSegv, &GPreviousSIGSEGV, SA_ONSTACK);
        SetSignal(SIGINT,  HandleSignalInt, &GPreviousSIGINT, 0, true);
        SetSignal(SIGQUIT, HandleSignalQuit, &GPreviousSIGQUIT, 0, true);
    }
}

namespace Graphyte::Launch
{
    void InitializeErrorHandling() noexcept
    {
        std::set_terminate(Impl::Posix::TerminateHandler);
        Impl::Posix::SetupSignalHandlers();
        
        Impl::Posix::SetResourceLimit(RLIMIT_NOFILE, 8192, true);
        Impl::Posix::SetResourceLimit(RLIMIT_CORE, 0, false);
    }
}
