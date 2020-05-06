#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/System.hxx>

namespace Graphyte::Diagnostics
{
    BASE_API std::string_view GetSignalName(
        const siginfo_t* signal_info
    ) noexcept
    {
        switch (signal_info->si_signo)
        {
        case SIGHUP:
            {
                return "SIGHUP";
            }

        case SIGQUIT:
            {
                return "SIGQUIT";
            }

        case SIGTRAP:
            {
                switch (signal_info->si_code)
                {
                case SI_KERNEL:
                    return "SIGTRAP.KERNEL";
                case SI_USER:
                    return "SIGTRAP.USER";
                case TRAP_BRKPT:
                    return "SIGTRAP.BRKPT";
                case TRAP_TRACE:
                    return "SIGTRAP.TRACE";

                default:
                    break;
                }

                break;
            }

        case SIGILL:
            {
                switch (signal_info->si_code)
                {
                case ILL_ILLOPC:
                    return "SIGILL.ILLOPC";
                case ILL_ILLOPN:
                    return "SIGILL.ILLOPN";
                case ILL_ILLADR:
                    return "SIGILL.ILLADR";
                case ILL_ILLTRP:
                    return "SIGILL.ILLTRP";
                case ILL_COPROC:
                    return "SIGILL.COPROC";
                case ILL_PRVOPC:
                    return "SIGILL.PRVOPC";
                case ILL_PRVREG:
                    return "SIGILL.PRVREG";
                case ILL_BADSTK:
                    return "SIGILL.BADSTK";
                default:
                    break;
                }

                break;
            }

        case SIGBUS:
            {
                switch (signal_info->si_code)
                {
                case BUS_ADRALN:
                    return "SIGBUS.ADRALN";
                case BUS_ADRERR:
                    return "SIGBUS.ADRERR";
                case BUS_OBJERR:
                    return "SIGBUS.OBJERR";
                default:
                    break;
                }

                break;
            }

        case SIGSYS:
            {
                return "SIGSYS";
            }

        case SIGPIPE:
            {
                return "SIGPIPE";
            }

        case SIGALRM:
            {
                return "SIGALRM";
            }

        case SIGFPE:
            {
                switch (signal_info->si_code)
                {
                case FPE_INTDIV:
                    return "SIGFPE.INTDIV";
                case FPE_INTOVF:
                    return "SIGFPE.INTOVF";
                case FPE_FLTDIV:
                    return "SIGFPE.FLTDIV";
                case FPE_FLTOVF:
                    return "SIGFPE.FLTOVF";
                case FPE_FLTUND:
                    return "SIGFPE.FLTUND";
                case FPE_FLTRES:
                    return "SIGFPE.FLTRES";
                case FPE_FLTINV:
                    return "SIGFPE.FLTINV";
                case FPE_FLTSUB:
                    return "SIGFPE.FLTSUB";
                default:
                    break;
                }

                break;
            }

        case SIGSEGV:
            {
                switch (signal_info->si_code)
                {
                case SI_USER:
                    return "SIGSEGV.USER";
                case SEGV_MAPERR:
                    return "SIGSEGV.MAPERR";
                case SEGV_ACCERR:
                    return "SIGSEGV.ACCERR";
                case SI_KERNEL:
                    return "SIGSEGV.KERNEL";
                default:
                    break;
                }

                break;
            }

        default:
            break;
        }

        return "(unknown)";
    }

    BASE_API Status GetStatusFromSiginfo(
        const siginfo_t* signal_info
    ) noexcept
    {
        switch (signal_info->si_signo)
        {
        case SIGILL:
            {
                switch (signal_info->si_code)
                {
                case ILL_ILLOPC:
                case ILL_ILLOPN:
                case ILL_ILLADR:
                case ILL_ILLTRP:
                case ILL_COPROC:
                    return Status::InvalidInstruction;

                case ILL_PRVOPC:
                case ILL_PRVREG:
                    return Status::SharingViolation;

                case ILL_BADSTK:
                    return Status::StackOverflow;

                default:
                    break;
                }

                break;
            }

        case SIGFPE:
            {
                switch (signal_info->si_code)
                {
                case FPE_INTDIV:
                case FPE_INTOVF:
                case FPE_FLTDIV:
                case FPE_FLTOVF:
                case FPE_FLTUND:
                case FPE_FLTRES:
                case FPE_FLTINV:
                case FPE_FLTSUB:
                    return Status::FloatingPointError;

                default:
                    break;
                }

                break;
            }

        case SIGSEGV:
            {
                switch (signal_info->si_code)
                {
                case SI_USER:
                case SEGV_MAPERR:
                case SEGV_ACCERR:
                case SI_KERNEL:
                    return Status::SharingViolation;

                default:
                    break;
                }

                break;
            }

        case SIGBUS:
            {
                switch (signal_info->si_code)
                {
                case BUS_ADRALN:
                case BUS_ADRERR:
                case BUS_OBJERR:
                    return Status::SharingViolation;

                default:
                    break;
                }

                break;
            }

        case SIGTRAP:
            {
                switch (signal_info->si_code)
                {
                case SI_KERNEL:
                case SI_USER:
                case TRAP_BRKPT:
                case TRAP_TRACE:
                    return Status::Breakpoint;

                default:
                    return Status::InvalidInstruction;
                }

                break;
            }

        default:
            break;
        }

        return Status::InvalidInstruction;
    }
}
