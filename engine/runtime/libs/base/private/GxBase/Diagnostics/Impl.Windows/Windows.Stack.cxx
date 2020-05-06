#include <GxBase/Diagnostics.hxx>
#include <GxBase/Span.hxx>

#include "../Diagnostics.Impl.hxx"

#include <Windows.h>

#if GRAPHYTE_ENABLE_STACKTRACE_SYMBOLS
#include <DbgHelp.h>
#endif

#include <crtdbg.h>
#include <exception>

#if GRAPHYTE_ENABLE_STACKTRACE_SYMBOLS

namespace Graphyte::Diagnostics::Impl
{
    static DWORD GetMachineType() noexcept
    {
#if GRAPHYTE_CPU_X86_64
        return IMAGE_FILE_MACHINE_AMD64;
#elif GRAPHYTE_CPU_X86_32
        return IMAGE_FILE_MACHINE_I386;
#elif GRAPHYTE_CPU_ARM_64
        return IMAGE_FILE_MACHINE_ARM64;
#elif GRAPHYTE_CPU_ARM_32
        return IMAGE_FILE_MACHINE_ARM;
#else
#error Not supported architecture
#endif
    }

    static STACKFRAME64 GetStackFrameFromContext(
        const CONTEXT& context
    ) noexcept
    {
        STACKFRAME64 frame = {
            .AddrPC = {
                .Mode = AddrModeFlat,
            },
            .AddrFrame = {
                .Mode = AddrModeFlat,
            },
            .AddrStack = {
                .Mode = AddrModeFlat
            }
        };


#if GRAPHYTE_CPU_X86_64

        frame.AddrPC.Offset = context.Rip;
        frame.AddrFrame.Offset = context.Rbp;
        frame.AddrStack.Offset = context.Rsp;

#elif GRAPHYTE_CPU_X86_32

        frame.AddrPC.Offset = context.Eip;
        frame.AddrFrame.Offset = context.Ebp;
        frame.AddrStack.Offset = context.Esp;

#elif GRAPHYTE_CPU_ARM_64

        frame.AddrPC.Offset = context.Pc;
        frame.AddrFrame.Offset = context.Fp;
        frame.AddrStack.Offset = context.Sp;

#elif GRAPHYTE_CPU_ARM_32

        frame.AddrPC.Offset = context.Pc;
        frame.AddrFrame.Offset = context.R11;
        frame.AddrStack.Offset = context.Sp;

#else
#error "Not supported"
#endif

        return frame;
    }

    void FillSymbolMetadataForAddress(
        StackFrame& frame,
        DWORD64 address,
        HANDLE process
    ) noexcept
    {
        frame.Address = address;

#if GRAPHYTE_ENABLE_STACKTRACE_SYMBOLS

        if (Impl::GStackTraceSymbolInfo)
        {
            //
            // Get module name.
            //

            HMODULE handle = reinterpret_cast<HMODULE>(SymGetModuleBase64(process, address));

            if (handle != nullptr)
            {
                CHAR name[MAX_PATH];

                DWORD length = GetModuleFileNameA(
                    handle,
                    name,
                    MAX_PATH
                );

                frame.Module = std::string_view{ name, length };
            }
            else
            {
                fmt::print("error: {}\n", Diagnostics::GetMessageFromSystemError());
            }


            //
            // Get symbol information for given PC.
            //

            union SymbolInfo
            {
                SYMBOL_INFO Header;
                CHAR Buffer[512];
            };

            SymbolInfo symbol = {
                .Header = {
                    .SizeOfStruct = sizeof(symbol.Header),
                    .MaxNameLen = sizeof(symbol) - sizeof(symbol.Header),
                },
            };

            if (SymFromAddr(process, address, nullptr, &symbol.Header) != FALSE)
            {
                frame.Function = std::string_view{
                    symbol.Header.Name,
                    symbol.Header.NameLen
                };
            }


            //
            // Get location of this symbol in source file.
            //

            IMAGEHLP_LINE64 line{
                .SizeOfStruct = sizeof(line),
            };

            DWORD displacement{};
            if (SymGetLineFromAddr64(process, address, &displacement, &line) != FALSE)
            {
                frame.File = line.FileName;
                frame.Line = line.LineNumber;
            }

        }
#endif
    }
}

#endif

namespace Graphyte::Diagnostics
{
    BASE_API Status GetStackTrace(
        std::vector<StackFrame>& frames
    ) noexcept
    {
#if GRAPHYTE_ENABLE_STACKTRACE_SYMBOLS

#if GRAPHYTE_ENABLE_STACKTRACE_FAST
        {
            constexpr const DWORD MaxFramesCount = 128;

            PVOID backtrace[MaxFramesCount];

            WORD captured = RtlCaptureStackBackTrace(
                0,
                MaxFramesCount,
                backtrace,
                nullptr
            );

            HANDLE process = GetCurrentProcess();

            frames.reserve(captured);

            for (size_t i = 0; i < captured; ++i)
            {
                StackFrame& frame = frames.emplace_back();
                Impl::FillSymbolMetadataForAddress(
                    frame,
                    static_cast<DWORD64>(reinterpret_cast<UINT_PTR>(backtrace[i])),
                    process
                );
            }

            return Status::Success;
        }
#else
        {
            CONTEXT context;
            RtlCaptureContext(&context);

            return GetStackTrace(frames, context);
        }
#endif // GRAPHYTE_ENABLE_STACKTRACE_FAST

#else

        frames.clear();
        return Status::NotSupported;

#endif // GRAPHYTE_ENABLE_STACKTRACE_SYMBOLS
    }

    BASE_API Status GetStackTrace(
        std::vector<StackFrame>& frames,
        [[maybe_unused]] const CONTEXT& context
    ) noexcept
    {
#if GRAPHYTE_ENABLE_STACKTRACE_SYMBOLS

        HANDLE process = GetCurrentProcess();

        HANDLE thread = GetCurrentThread();

        DWORD machine = Impl::GetMachineType();
        STACKFRAME64 base_frame = Impl::GetStackFrameFromContext(context);

        bool success = true;

        CONTEXT working_context = context;

        while (success)
        {
            success = !!StackWalk64(
                machine,
                process,
                thread,
                &base_frame,
                &working_context,
                nullptr,
                SymFunctionTableAccess64,
                SymGetModuleBase64,
                nullptr
            );

            if (success)
            {
                StackFrame& frame = frames.emplace_back();
                Impl::FillSymbolMetadataForAddress(
                    frame,
                    base_frame.AddrPC.Offset,
                    process
                );
            }
            else
            {
                // TODO: Check whether this is a valid situation to report this error here
                //return Diagnostics::GetStatusFromSystemError();
            }
        }

        return Status::Success;

#else

        frames.clear();
        return Status::NotSupported;

#endif

    }
}
