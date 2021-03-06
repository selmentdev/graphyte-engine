#pragma once
#include <GxBase/Base.module.hxx>

namespace Graphyte
{
    /// @brief Generic status code.
    ///
    /// @details This type represents status code used with function interfacing native OS APIs.
    ///
    ///          To simply check whether specific function returned valid value, check it against
    ///          `Status::Success`.
    ///
    ///          In order to get more information, check returned value for specific status code.
    enum class [[nodiscard]] Status : uint32_t{
        Success = 0,
        Failure,
        InvalidArgument,
        InvalidPath,
        InvalidFile,
        InvalidDirectory,
        InvalidFormat,
        NotInitialized,
        NotImplemented,
        NotSupported,
        NotFound,
        NotEnoughMemory,
        AccessDenied,
        SharingViolation,
        DirectoryNotEmpty,
        AlreadyExists,
        Timeout,
        TryAgain,
        ReadFault,
        WriteFault,
        FileExists,
        EndOfStream,
        Breakpoint,
        StackOverflow,
        InvalidInstruction,
        FloatingPointError,
    };
}
