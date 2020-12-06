#include <GxBase/Diagnostics.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/System.hxx>

#include <ErrorRep.h>
#include <CommCtrl.h>

namespace Graphyte::Diagnostics
{
    static void LogProcessorContext(CONTEXT const& context) noexcept
    {
#if GX_CPU_X86_64

        GX_LOG_ERROR(LogPlatform, "  rax = {:016x}  rbx = {:016x}  rcx = {:016x}  rdx = {:016x}\n", context.Rax, context.Rbx, context.Rcx, context.Rdx);
        GX_LOG_ERROR(LogPlatform, "  rsp = {:016x}  rbp = {:016x}  rsi = {:016x}  rdi = {:016x}\n", context.Rsp, context.Rbp, context.Rsi, context.Rdi);
        GX_LOG_ERROR(LogPlatform, "   r8 = {:016x}   r9 = {:016x}  r10 = {:016x}  r11 = {:016x}\n", context.R8, context.R9, context.R10, context.R11);
        GX_LOG_ERROR(LogPlatform, "  r12 = {:016x}  r13 = {:016x}  r14 = {:016x}  r15 = {:016x}\n", context.R12, context.R13, context.R14, context.R15);
        GX_LOG_ERROR(LogPlatform, "  rfl = {:016x}  rip = {:016x}\n", context.EFlags, context.Rip);

#elif GX_CPU_X86_32

        GX_LOG_ERROR(LogPlatform, "  eax = {:08x}  ebx = {:08x}  ecx = {:08x}  edx = {:08x}\n", context.Eax, context.Ebx, context.Ecx, context.Edx);
        GX_LOG_ERROR(LogPlatform, "  esp = {:08x}  ebp = {:08x}  esi = {:08x}  edi = {:08x}\n", context.Esp, context.Ebp, context.Esi, context.Edi);
        GX_LOG_ERROR(LogPlatform, "  efl = {:08x}  eip = {:08x}\n", context.EFlags, context.Eip);

#elif GX_CPU_ARM_64

        GX_LOG_ERROR(LogPlatform, "   x0 = {:016x}   x1 = {:016x}   x2 = {:016x}   x3 = {:016x}\n", context.X0, context.X1, context.X2, context.X3);
        GX_LOG_ERROR(LogPlatform, "   x4 = {:016x}   x5 = {:016x}   x6 = {:016x}   x7 = {:016x}\n", context.X4, context.X5, context.X6, context.X7);
        GX_LOG_ERROR(LogPlatform, "   x8 = {:016x}   x9 = {:016x}  x10 = {:016x}  x11 = {:016x}\n", context.X8, context.X9, context.X10, context.X11);
        GX_LOG_ERROR(LogPlatform, "  x12 = {:016x}  x13 = {:016x}  x14 = {:016x}  x15 = {:016x}\n", context.X12, context.X13, context.X14, context.X15);
        GX_LOG_ERROR(LogPlatform, "  x16 = {:016x}  x17 = {:016x}  x18 = {:016x}  x19 = {:016x}\n", context.X16, context.X17, context.X18, context.X19);
        GX_LOG_ERROR(LogPlatform, "  x20 = {:016x}  x21 = {:016x}  x22 = {:016x}  x23 = {:016x}\n", context.X20, context.X21, context.X22, context.X23);
        GX_LOG_ERROR(LogPlatform, "  x24 = {:016x}  x25 = {:016x}  x26 = {:016x}  x27 = {:016x}\n", context.X24, context.X25, context.X26, context.X27);
        GX_LOG_ERROR(LogPlatform, "  x28 = {:016x}   fp = {:016x}   lr = {:016x},  sp = {:016x}\n", context.X28, context.Fp, context.Lr, context.Sp);
        GX_LOG_ERROR(LogPlatform, "   pc = {:016x} cpsr = {:016x}\n", context.Pc, context.Cpsr);

#elif GX_CPU_ARM_32

        GX_LOG_ERROR(LogPlatform, "   r0 = {:08x}   r1 = {:08x}   r2 = {:08x}   r3 = {:08x}\n", context.R0, context.R1, context.R2, context.R3);
        GX_LOG_ERROR(LogPlatform, "   r4 = {:08x}   r5 = {:08x}   r6 = {:08x}   r7 = {:08x}\n", context.R4, context.R5, context.R6, context.R7);
        GX_LOG_ERROR(LogPlatform, "   r8 = {:08x}   r9 = {:08x}  r10 = {:08x}  r11 = {:08x}\n", context.R8, context.R9, context.R10, context.R11);
        GX_LOG_ERROR(LogPlatform, "  r12 = {:08x}   sp = {:08x}   lr = {:08x}   pc = {:08x}\n", context.R12, context.Sp, context.Lr, context.Pc);
        GX_LOG_ERROR(LogPlatform, " cpsr = {:08x}\n", context.Cpsr);

#else
#error "Not implemented"
#endif
    }

    //[[noreturn]]
    BASE_API void OnCrash(
        EXCEPTION_POINTERS* exception) noexcept
    {
        GX_LOG_ERROR(LogPlatform, "Application crashed:\n");


        //
        // Log exception information.
        //

        if (exception != nullptr)
        {
            GX_LOG_ERROR(LogPlatform,
                "Exception:\n"
                "    code:     {} ({:08x})\n"
                "    address:  {}\n"
                "Params: {}\n",
                Diagnostics::GeMessageFromtExceptionCode(exception->ExceptionRecord->ExceptionCode),
                exception->ExceptionRecord->ExceptionCode,
                exception->ExceptionRecord->ExceptionAddress,
                exception->ExceptionRecord->NumberParameters);

            for (DWORD i = 0; i < exception->ExceptionRecord->NumberParameters; ++i)
            {
                GX_LOG_ERROR(LogPlatform, "    [{:2}] {}\n",
                    i,
                    reinterpret_cast<void*>(exception->ExceptionRecord->ExceptionInformation[i]));
            }


            //
            // Log processor context.
            //

            if (exception->ContextRecord != nullptr)
            {
                GX_LOG_ERROR(LogPlatform, "Context:\n");

                LogProcessorContext(*exception->ContextRecord);


                //
                // Log stack trace.
                //


                GX_LOG_ERROR(LogPlatform, "Stack Trace:\n");

                std::vector<StackFrame> trace{};

                if (auto const status = GetStackTrace(trace, *exception->ContextRecord); status == Status::Success)
                {
                    for (size_t i = 0; i < trace.size(); ++i)
                    {
                        GX_LOG_ERROR(LogPlatform, "    [{:4}] {}\n",
                            i,
                            ToString(trace[i], StackFrameFormat::Extended));
                    }
                }
                else
                {
                    GX_LOG_ERROR(LogPlatform, "-- no stack trace available --\n");
                }
            }
        }


        //
        // Report crash to user.
        //

        if (GetErrorReporting() == ErrorReporting::Interactive)
        {
            TASKDIALOGCONFIG const config{
                .cbSize             = sizeof(TASKDIALOGCONFIG),
                .hwndParent         = nullptr,
                .hInstance          = System::Impl::g_InstanceHandle,
                .dwCommonButtons    = TDCBF_CLOSE_BUTTON,
                .pszWindowTitle     = L"Graphyte Engine Crashed",
                .pszMainIcon        = TD_ERROR_ICON,
                .pszMainInstruction = L"Application Crashed",
                .pszContent         = L"See logs for detailed information",
            };

            System::RestoreSystemUI();

            TaskDialogIndirect(&config, nullptr, nullptr, nullptr);
        }


        //
        // Report fault to WER
        //

        if (exception != nullptr)
        {
            [[maybe_unused]] auto result = ReportFault(exception, 0);

#if GX_BUILD_TYPE_DEVELOPER

            switch (result)
            {
                case frrvOk:
                case frrvOkManifest:
                case frrvOkQueued:
                case frrvOkHeadless:
                    GX_LOG_ERROR(LogPlatform, "Report fault = OK\n");
                    break;

                case frrvLaunchDebugger:
                    GX_LOG_ERROR(LogPlatform, "Report fault = Launch Debugger\n");
                    break;

                case frrvErr:
                case frrvErrNoDW:
                case frrvErrTimeout:
                case frrvErrAnotherInstance:
                case frrvErrNoMemory:
                case frrvErrDoubleFault:
                    GX_LOG_ERROR(LogPlatform, "Report fault = Error\n");
                    break;
            }

#endif
        }


        //
        // Terminate application.
        //

        Diagnostics::FailFast();
    }
}
