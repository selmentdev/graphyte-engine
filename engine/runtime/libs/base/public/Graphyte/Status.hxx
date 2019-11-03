#pragma once
#include <Graphyte/Base.module.hxx>

namespace Graphyte
{
    /*!
     * \brief   Generic status code.
     *
     * \details This type represents status code used with function interfacing native OS APIs.
     *
     *          To simply check whether specific function returned valid value, check it against
     *          `Status::Success`.
     *
     *          In order to get more information, check returned value for specific status code.
     *
     * \remarks Note that status codes other than `Success` may represent actual successful
     *          operation.
     *
     *          For example, trying to create file in file system may return both `Status::Success`
     *          and `Status::AlreadyExists`, where `AlreadyExists` may represent both:
     *
     *          - failure (cannot create new file),
     *          - success (file already exists).
     */
    enum struct [[nodiscard]] Status : uint32_t
    {
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
