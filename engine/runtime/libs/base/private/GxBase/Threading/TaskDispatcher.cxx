#include <GxBase/Threading/TaskDispatcher.hxx>
#include <GxBase/String.hxx>
#include <GxBase/Diagnostics/Profiler.hxx>
#include <GxBase/System.hxx>

namespace Graphyte::Threading
{
    class TaskWorkerThread final : public IRunnable
    {
    private:
        TaskDispatcher& m_TaskManager;

    public:
        TaskWorkerThread(
            TaskDispatcher& task_manager) noexcept
            : m_TaskManager{ task_manager }
        {
        }

        virtual ~TaskWorkerThread() noexcept = default;

        uint32_t OnRun() noexcept final
        {
            for (;;)
            {
                auto task = m_TaskManager.AcquireTask();

                if (task != nullptr)
                {
                    GX_PROFILE_REGION("Task");
                    task->Execute();
                }
                else
                {
                    return 0;
                }
            }
        }
    };
}

namespace Graphyte::Threading
{
    TaskDispatcher::TaskDispatcher() noexcept
        : m_Tasks{}
        , m_Workers{}
        , m_CS{}
        , m_CV{}
        , m_Stop{}
    {
    }

    TaskDispatcher::~TaskDispatcher() noexcept
    {
        Stop();
    }

    TaskDispatcher& TaskDispatcher::GetInstance() noexcept
    {
        static TaskDispatcher instance{};
        return instance;
    }

    void TaskDispatcher::Initialize() noexcept
    {
        TaskDispatcher::GetInstance().Start(
            static_cast<size_t>(System::GetLogicalCores()));
    }

    void TaskDispatcher::Finalize() noexcept
    {
        TaskDispatcher::GetInstance().Stop();
    }

    void TaskDispatcher::Start(
        size_t threads) noexcept
    {
        Stop();
        m_Stop = false;

        m_Workers.resize(threads);

        size_t index{};

        for (auto& worker : m_Workers)
        {
            worker.Runnable = std::make_unique<TaskWorkerThread>(*this);
            worker.Worker.Start(worker.Runnable.get(), fmt::format("worker-{}", index++));
        }
    }

    void TaskDispatcher::Stop() noexcept
    {
        m_Stop = true;
        m_CV.NotifyAll();

        for (auto& worker : m_Workers)
        {
            worker.Worker.Stop(true);
        }

        m_Workers.clear();
    }

    void TaskDispatcher::Dispatch(
        std::unique_ptr<BaseTask> task) noexcept
    {
        {
            ScopedLock<CriticalSection> lock{ m_CS };
            m_Tasks.push_back(std::move(task));
        }

        m_CV.Notify();
    }

    std::unique_ptr<BaseTask> TaskDispatcher::AcquireTask() noexcept
    {
        std::unique_ptr<BaseTask> task{};

        {
            ScopedLock<CriticalSection> lock{ m_CS };

            while (!m_Stop && m_Tasks.empty())
            {
                m_CV.Wait(m_CS);
            }

            if (!m_Stop || !m_Tasks.empty())
            {
                task = std::move(m_Tasks.front());
                m_Tasks.pop_front();
            }
        }

        return task;
    }
}
