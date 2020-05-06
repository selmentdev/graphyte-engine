#include <GxBase/Threading/TimerDispatcher.hxx>

namespace Graphyte::Threading
{
    TimerDispatcher::TimerDispatcher() noexcept
        : m_ActiveTimers{}
        , m_PausedTimers{}
        , m_PendingTimers{}
    {
    }

    TimerDispatcher::~TimerDispatcher() noexcept = default;
}
