#include <GxBase/Diagnostics.hxx>

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverloaded-virtual"
#endif

#define UNW_LOCAL_ONLY
#include <cxxabi.h>
#include <libunwind.h>

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

namespace Graphyte::Diagnostics::Impl
{
    static Status GetLibUnwindStackTrace(
        std::vector<StackFrame>& frames,
        unw_context_t* context) noexcept
    {
        unw_cursor_t cursor{};
        unw_init_local(&cursor, context);

        while (unw_step(&cursor) > 0)
        {
            unw_word_t offset{};
            unw_word_t pc{};

            unw_get_reg(&cursor, UNW_REG_IP, &pc);

            if (pc == 0)
            {
                break;
            }

            StackFrame frame{};
            frame.Address = static_cast<std::uintptr_t>(pc);

            char symbolName[256];
            if (unw_get_proc_name(&cursor, symbolName, std::size(symbolName), &offset) == 0)
            {
                char* name = symbolName;

                int status{};
                char* demangled = abi::__cxa_demangle(symbolName, nullptr, nullptr, &status);
                if (status == 0)
                {
                    name = demangled;
                }

                frame.Function.assign(name);
                std::free(demangled);
            }
            else
            {
                frame.Function.assign("<unknown>");
            }

            frames.push_back(frame);
        }

        return Status::Success;
    }
}

namespace Graphyte::Diagnostics
{
    BASE_API Status GetStackTrace(
        std::vector<StackFrame>& frames) noexcept
    {
        unw_context_t context{};
        unw_getcontext(&context);

        return Impl::GetLibUnwindStackTrace(
            frames,
            &context);
    }

    BASE_API Status GetStackTrace(
        std::vector<StackFrame>& frames,
        [[maybe_unused]] ucontext_t* context) noexcept
    {
        return GetStackTrace(frames);
    }
}
