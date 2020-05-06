#pragma once
#include <GxBase/Threading/Runnable.hxx>
#include <GxBase/Threading/Sync.hxx>
#include <GxBase/Threading/Thread.hxx>

namespace Graphyte::Threading
{
    class BaseTask
    {
    public:
        BaseTask() noexcept = default;
        virtual ~BaseTask() noexcept = default;

    public:
        virtual void Execute() noexcept = 0;
    };

    class TaskWorkerThread;

    class BASE_API TaskDispatcher final
    {
        friend class TaskWorkerThread;
    private:
        struct WorkerData final
        {
            std::unique_ptr<TaskWorkerThread> Runnable;
            Thread Worker;
        };

    private:
        std::deque<std::unique_ptr<BaseTask>> m_Tasks;
        std::vector<WorkerData> m_Workers;
        CriticalSection m_CS;
        ConditionVariable m_CV;
        bool m_Stop;

    public:
        TaskDispatcher() noexcept;
        ~TaskDispatcher() noexcept;

    public:
        static TaskDispatcher& GetInstance() noexcept;
        static void Initialize() noexcept;
        static void Finalize() noexcept;

    public:
        void Start(size_t threads) noexcept;
        void Stop() noexcept;
        void Dispatch(std::unique_ptr<BaseTask> task) noexcept;

    private:
        std::unique_ptr<BaseTask> AcquireTask() noexcept;
    };

    template <typename TTask>
    class Task final : public BaseTask
    {
    private:
        TTask m_Task;

    public:
        struct TaskConstructor final
        {
            friend class Task;
        public:
            template <typename... TArgs>
            void Dispatch(TArgs&&... args) noexcept
            {
                TaskDispatcher::GetInstance().Dispatch(std::move(std::make_unique<Task>(std::forward<TArgs>(args)...)));
            }
        };

    public:
        static TaskConstructor CreateTask()
        {
            return TaskConstructor{};
        }

        template <typename... TArgs>
        static std::unique_ptr<Task> Make(TArgs&&... args) noexcept
        {
            return std::make_unique<Task>(std::forward<TArgs>(args)...);
        }

    public:
        template <typename... TArgs>
        Task(TArgs&&... args) noexcept
            : m_Task(std::forward<TArgs>(args)...)
        {
        }

        virtual ~Task() noexcept = default;

    public:
        void Execute() noexcept final override
        {
            m_Task.DoTask();
        }
    };
}
