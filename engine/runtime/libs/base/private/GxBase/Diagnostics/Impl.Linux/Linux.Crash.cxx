#include <GxBase/Diagnostics.hxx>
#include <GxBase/System.hxx>

namespace Graphyte::Diagnostics
{
    static void LogProcessorContext(ucontext_t* context) noexcept
    {
#if GRAPHYTE_CPU_X86_64

        GX_LOG_ERROR(LogPlatform, "  rax = {:016x}  rbx = {:016x}  rcx = {:016x}  rdx = {:016x}\n", context->uc_mcontext.gregs[REG_RAX], context->uc_mcontext.gregs[REG_RBX], context->uc_mcontext.gregs[REG_RCX], context->uc_mcontext.gregs[REG_RDX]);
        GX_LOG_ERROR(LogPlatform, "  rsp = {:016x}  rbp = {:016x}  rsi = {:016x}  rdi = {:016x}\n", context->uc_mcontext.gregs[REG_RSP], context->uc_mcontext.gregs[REG_RBP], context->uc_mcontext.gregs[REG_RSI], context->uc_mcontext.gregs[REG_RDI]);
        GX_LOG_ERROR(LogPlatform, "   r8 = {:016x}   r9 = {:016x}  r10 = {:016x}  r11 = {:016x}\n", context->uc_mcontext.gregs[REG_R8], context->uc_mcontext.gregs[REG_R9], context->uc_mcontext.gregs[REG_R10], context->uc_mcontext.gregs[REG_R11]);
        GX_LOG_ERROR(LogPlatform, "  r12 = {:016x}  r13 = {:016x}  r14 = {:016x}  r15 = {:016x}\n", context->uc_mcontext.gregs[REG_R12], context->uc_mcontext.gregs[REG_R13], context->uc_mcontext.gregs[REG_R14], context->uc_mcontext.gregs[REG_R15]);
        GX_LOG_ERROR(LogPlatform, "  rfl = {:016x}  rip = {:016x}\n", context->uc_mcontext.gregs[REG_EFL], context->uc_mcontext.gregs[REG_RIP]);

#elif GRAPHYTE_CPU_X86_32

        GX_LOG_ERROR(LogPlatform, "  eax = {:08x}  ebx = {:08x}  ecx = {:08x}  edx = {:08x}\n", context->uc_mcontext.gregs[REG_EAX], context->uc_mcontext.gregs[REG_EBX], context->uc_mcontext.gregs[REG_ECX], context->uc_mcontext.gregs[REG_EDX]);
        GX_LOG_ERROR(LogPlatform, "  esp = {:08x}  ebp = {:08x}  esi = {:08x}  edi = {:08x}\n", context->uc_mcontext.gregs[REG_ESP], context->uc_mcontext.gregs[REG_EBP], context->uc_mcontext.gregs[REG_ESI], context->uc_mcontext.gregs[REG_EDI]);
        GX_LOG_ERROR(LogPlatform, "  efl = {:08x}  eip = {:08x}\n", context->uc_mcontext.gregs[REG_EFL], context->uc_mcontext.gregs[REG_EIP]);

#elif GRAPHYTE_CPU_ARM_64

        GX_LOG_ERROR(LogPlatform, "   x0 = {:016x}   x1 = {:016x}   x2 = {:016x}   x3 = {:016x}\n", context->uc_mcontext.regs[0], context->uc_mcontext.regs[1], context->uc_mcontext.regs[2], context->uc_mcontext.regs[3]);
        GX_LOG_ERROR(LogPlatform, "   x4 = {:016x}   x5 = {:016x}   x6 = {:016x}   x7 = {:016x}\n", context->uc_mcontext.regs[4], context->uc_mcontext.regs[5], context->uc_mcontext.regs[6], context->uc_mcontext.regs[7]);
        GX_LOG_ERROR(LogPlatform, "   x8 = {:016x}   x9 = {:016x}  x10 = {:016x}  x11 = {:016x}\n", context->uc_mcontext.regs[8], context->uc_mcontext.regs[9], context->uc_mcontext.regs[10], context->uc_mcontext.regs[11]);
        GX_LOG_ERROR(LogPlatform, "  x12 = {:016x}  x13 = {:016x}  x14 = {:016x}  x15 = {:016x}\n", context->uc_mcontext.regs[12], context->uc_mcontext.regs[13], context->uc_mcontext.regs[14], context->uc_mcontext.regs[15]);
        GX_LOG_ERROR(LogPlatform, "  x16 = {:016x}  x17 = {:016x}  x18 = {:016x}  x19 = {:016x}\n", context->uc_mcontext.regs[16], context->uc_mcontext.regs[17], context->uc_mcontext.regs[18], context->uc_mcontext.regs[19]);
        GX_LOG_ERROR(LogPlatform, "  x20 = {:016x}  x21 = {:016x}  x22 = {:016x}  x23 = {:016x}\n", context->uc_mcontext.regs[20], context->uc_mcontext.regs[21], context->uc_mcontext.regs[22], context->uc_mcontext.regs[23]);
        GX_LOG_ERROR(LogPlatform, "  x24 = {:016x}  x25 = {:016x}  x26 = {:016x}  x27 = {:016x}\n", context->uc_mcontext.regs[24], context->uc_mcontext.regs[25], context->uc_mcontext.regs[26], context->uc_mcontext.regs[27]);
        GX_LOG_ERROR(LogPlatform, "  x28 = {:016x}   fp = {:016x}   lr = {:016x},  sp = {:016x}\n", context->uc_mcontext.regs[28], context->uc_mcontext.regs[29], context->uc_mcontext.regs[30], context->uc_mcontext.sp);
        GX_LOG_ERROR(LogPlatform, "   pc = {:016x} cpsr = {:016x}\n", context->uc_mcontext.pc, context->uc_mcontext.pstate);

#elif GRAPHYTE_CPU_ARM_32

        GX_LOG_ERROR(LogPlatform, "   r0 = {:08x}   r1 = {:08x}   r2 = {:08x}   r3 = {:08x}\n", context->uc_mcontext.arm_r0, context->uc_mcontext.arm_r1, context->uc_mcontext.arm_r2, context->uc_mcontext.arm_r3);
        GX_LOG_ERROR(LogPlatform, "   r4 = {:08x}   r5 = {:08x}   r6 = {:08x}   r7 = {:08x}\n", context->uc_mcontext.arm_r4, context->uc_mcontext.arm_r5, context->uc_mcontext.arm_r6, context->uc_mcontext.arm_r7);
        GX_LOG_ERROR(LogPlatform, "   r8 = {:08x}   r9 = {:08x}  r10 = {:08x}   fp = {:08x}\n", context->uc_mcontext.arm_r8, context->uc_mcontext.arm_r9, context->uc_mcontext.arm_r10, context->uc_mcontext.arm_fp);
        GX_LOG_ERROR(LogPlatform, "   ip = {:08x}   sp = {:08x}   lr = {:08x}   pc = {:08x}\n", context->uc_mcontext.arm_ip, context->uc_mcontext.arm_sp, context->uc_mcontext.arm_lr, context->uc_mcontext.arm_pc);
        GX_LOG_ERROR(LogPlatform, " cpsr = {:08x}\n", context->uc_mcontext.arm_cpsr);

#else
#error "Not implemented"
#endif
    }

    BASE_API void OnCrash(
        ucontext_t* context,
        siginfo_t* signal_info) noexcept
    {
        (void)signal_info;
        (void)context;
        GX_LOG_ERROR(LogPlatform, "Application crashed:\n");

        if (context != nullptr)
        {
            GX_LOG_ERROR(LogPlatform, "Context:\n");

            LogProcessorContext(context);
        }

        if (signal_info != nullptr)
        {
            GX_LOG_ERROR(LogPlatform, "Signal Info:\n");
            GX_LOG_ERROR(LogPlatform, "    signal: {}\n", signal_info->si_signo);
            GX_LOG_ERROR(LogPlatform, "      code: {}\n", signal_info->si_code);
            GX_LOG_ERROR(LogPlatform, "     errno: {}\n", signal_info->si_errno);
            GX_LOG_ERROR(LogPlatform, "      name: {}\n", GetSignalName(signal_info));

            switch (signal_info->si_signo)
            {
                case SIGKILL:
                {
                    GX_LOG_ERROR(LogPlatform, "       pid: {}\n", signal_info->si_pid);
                    GX_LOG_ERROR(LogPlatform, "       uid: {}\n", signal_info->si_uid);
                    break;
                }

                case SIGILL:
                case SIGFPE:
                case SIGSEGV:
                case SIGBUS:
                {
                    GX_LOG_ERROR(LogPlatform, "      addr: {}\n", signal_info->si_addr);
                    GX_LOG_ERROR(LogPlatform, "     lower: {}\n", signal_info->si_lower);
                    GX_LOG_ERROR(LogPlatform, "     upper: {}\n", signal_info->si_upper);
                    GX_LOG_ERROR(LogPlatform, "      pkey: {}\n", signal_info->si_pkey);
                    break;
                }

                default:
                {
                    break;
                }
            }
        }


        //
        // Log stack trace.
        //

        std::vector<Diagnostics::StackFrame> stacktrace{};

        if (Status status = GetStackTrace(stacktrace, context); status == Status::Success)
        {
            GX_LOG_ERROR(LogPlatform, "Stack Trace:\n");

            for (size_t i = 0; i < stacktrace.size(); ++i)
            {
                GX_LOG_ERROR(LogPlatform, "    [{:4}] {}\n", i, ToString(stacktrace[i], StackFrameFormat::Extended));
            }
        }
        else
        {
            GX_LOG_ERROR(LogPlatform, "-- no stack trace --\n");
        }


        //
        // Terminate application.
        //

        Diagnostics::FailFast();
    }
}
