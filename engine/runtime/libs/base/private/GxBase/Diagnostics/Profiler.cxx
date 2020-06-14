#include <GxBase/Diagnostics/Profiler.hxx>

#if defined(ENABLE_NSIGHT_PROFILER)
#include <nvToolsExt.h>
#endif


namespace Graphyte::Diagnostics
{
    void Profiler::Initialize() noexcept
    {
    }

    void Profiler::Finalize() noexcept
    {
    }

    void Profiler::ThreadName(
        [[maybe_unused]] const char* name) noexcept
    {
#if defined(ENABLE_NSIGHT_PROFILER)
        nvtxNameOsThreadA(GetCurrentThreadId(), name);
#endif
    }

    void Profiler::PushRange(
        [[maybe_unused]] const char* name) noexcept
    {
#if defined(ENABLE_NSIGHT_PROFILER)
        nvtxRangePushA(name);
#endif
    }

    void Profiler::PushRange(
        [[maybe_unused]] const char* name,
        [[maybe_unused]] uint32_t color) noexcept
    {
#if defined(ENABLE_NSIGHT_PROFILER)
        nvtxEventAttributes_t event_attr{
            .version       = NVTX_VERSION,
            .size          = NVTX_EVENT_ATTRIB_STRUCT_SIZE,
            .colorType     = NVTX_COLOR_ARGB,
            .color         = color,
            .messageType   = NVTX_MESSAGE_TYPE_ASCII,
            .message.ascii = name,
        };

        nvtxRangePushEx(&event_attr);
#endif
    }

    void Profiler::PopRange() noexcept
    {
#if defined(ENABLE_NSIGHT_PROFILER)
        nvtxRangePop();
#endif
    }

    void Profiler::MarkEvent(
        [[maybe_unused]] const char* name) noexcept
    {
#if defined(ENABLE_NSIGHT_PROFILER)
        nvtxMarkA(name);
#endif
    }

    void Profiler::MarkEvent(
        [[maybe_unused]] const char* name,
        [[maybe_unused]] uint32_t color) noexcept
    {
#if defined(ENABLE_NSIGHT_PROFILER)
        nvtxEventAttributes_t event_attr{
            .version       = NVTX_VERSION,
            .size          = NVTX_EVENT_ATTRIB_STRUCT_SIZE,
            .colorType     = NVTX_COLOR_ARGB,
            .color         = color,
            .messageType   = NVTX_MESSAGE_TYPE_ASCII,
            .message.ascii = name,
        };

        nvtxMarkEx(&event_attr);
#endif
    }
}
