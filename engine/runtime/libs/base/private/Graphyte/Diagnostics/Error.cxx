#include "Base.pch.hxx"
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/System.hxx>
#include <Graphyte/Status.hxx>

namespace Graphyte::Diagnostics
{
    BASE_API Status GetStatusFromErrno(
        int error
    ) noexcept
    {
        switch (error)
        {
            case 0:
                return Status::Success;

            case E2BIG:
            case EBADF:
            case EISDIR:
            case EINVAL:
            case EDOM:
            case ERANGE:
            case EILSEQ:
            case EOVERFLOW:
                return Status::InvalidArgument;

            case ENOEXEC:
#if GRAPHYTE_PLATFORM_POSIX
            case ENOTBLK:
#endif
                return Status::NotSupported;

            case ENOENT:
            case ESRCH:
            case ENXIO:
            case ECHILD:
            case ENODEV:
                return Status::NotFound;

            case ENOMEM:
                return Status::NotEnoughMemory;

            case EPERM:
            case EACCES:
                return Status::AccessDenied;

            case EEXIST:
                return Status::AlreadyExists;

            case EBUSY:
            case ETXTBSY:
            case ETIME:
            case ETIMEDOUT:
                return Status::Timeout;

            case EINTR:
            case EAGAIN:
                return Status::TryAgain;

            default:
                GX_LOG(LogPlatform, Error, "Unmapped errno: {} -> {}\n",
                    error,
                    GetMessageFromErrno(error)
                );
                break;
        }

        return Status::Failure;
    }

    BASE_API std::string GetMessageFromErrno(
        int error
    ) noexcept
    {
#if GRAPHYTE_PLATFORM_POSIX

        std::array<char, 128> buffer{};
        
        char* result = strerror_r(
            error,
            std::data(buffer),
            std::size(buffer)
        );

        return { result };

#elif GRAPHYTE_PLATFORM_WINDOWS

        char buffer[128];
        strerror_s(buffer, error);
        buffer[std::size(buffer) - 1] = '\0';

        return { buffer };

#else
#   error "Not implemented"
#endif
    }

    BASE_API std::string_view GetMessageFromStatus(
        Status value
    ) noexcept
    {
        switch (value)
        {
            case Status::Success:               return "Success";
            case Status::Failure:               return "Failure";
            case Status::InvalidArgument:       return "InvalidArgument";
            case Status::InvalidPath:           return "InvalidPath";
            case Status::InvalidFile:           return "InvalidFile";
            case Status::InvalidDirectory:      return "InvalidDirectory";
            case Status::InvalidFormat:         return "InvalidFormat";
            case Status::NotInitialized:        return "NotInitialized";
            case Status::NotImplemented:        return "NotImplemented";
            case Status::NotSupported:          return "NotSupported";
            case Status::NotFound:              return "NotFound";
            case Status::NotEnoughMemory:       return "NotEnoughMemory";
            case Status::AccessDenied:          return "AccessDenied";
            case Status::SharingViolation:      return "SharingViolation";
            case Status::DirectoryNotEmpty:     return "DirectoryNotEmpty";
            case Status::AlreadyExists:         return "AlreadyExists";
            case Status::Timeout:               return "Timeout";
            case Status::TryAgain:              return "TryAgain";
            case Status::ReadFault:             return "ReadFault";
            case Status::WriteFault:            return "WriteFault";
            case Status::FileExists:            return "FileExists";
            case Status::EndOfStream:           return "EndOfStream";
            case Status::Breakpoint:            return "Breakpoint";
            case Status::StackOverflow:         return "StackOverflow";
            case Status::InvalidInstruction:    return "InvalidInstruction";
            case Status::FloatingPointError:    return "FloatingPointError";
        }

        return "<unknown>";
    }
}
