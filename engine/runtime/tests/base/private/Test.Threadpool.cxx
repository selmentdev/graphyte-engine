#include "Test.Base.pch.hxx"
#include <Graphyte/Threading/Thread.hxx>
#include <Graphyte/Threading/Sync.hxx>
#include <Graphyte/String.hxx>
#include <Graphyte/Diagnostics/Stopwatch.hxx>
#include <Graphyte/Diagnostics/Profiler.hxx>

namespace GraphyteX::Threading
{
    using namespace Graphyte::Threading;
    using namespace Graphyte;

    class Threadpool;

    class ThreadpoolWorker final : public IRunnable
    {
    private:
        Threadpool* m_Threadpool;

    public:
        ThreadpoolWorker(Threadpool* threadpool) noexcept;
        virtual ~ThreadpoolWorker() noexcept;
        uint32_t OnRun() noexcept override;
    };

    class Threadpool final
    {
        friend class ThreadpoolWorker;

    private:
        Threading::ConditionVariable m_QueueCV;
        Threading::CriticalSection m_QueueCS;
        std::deque<IRunnable*> m_Queue;
        std::vector<ThreadpoolWorker> m_Workers;
        std::vector<Thread> m_Threads;
        size_t m_ThreadsCount;
        bool m_Stop;

    public:
        Threadpool(size_t workers) noexcept;
        ~Threadpool() noexcept;

        void Stop() noexcept;

    public:
        void Schedule(IRunnable* runnable) noexcept;
    };

    Threadpool::Threadpool(size_t workers) noexcept
        : m_QueueCV{}
        , m_QueueCS{}
        , m_Queue{}
        , m_Workers{}
        , m_Threads{ workers }
        , m_ThreadsCount{ workers }
        , m_Stop{ false }
    {
        (void)m_ThreadsCount;
        m_Workers.reserve(workers);
        for (size_t i = 0; i < m_Threads.size(); ++i)
        {
            m_Workers.emplace_back(this);
            auto* worker = &m_Workers.back();
            m_Threads[i].Start(worker, fmt::format("Threadpool-{}", i).c_str());
        }
    }

    void Threadpool::Stop() noexcept
    {
        m_Stop = true;
        m_QueueCV.NotifyAll();

        for (auto&& thread : m_Threads)
        {
            thread.Stop(true);
        }
    }

    Threadpool::~Threadpool() noexcept
    {
        Stop();
    }

    void Threadpool::Schedule(IRunnable* runnable) noexcept
    {
        assert(runnable != nullptr);
        {
            {
                Threading::ScopedLock<Threading::CriticalSection> lock{ m_QueueCS };
                m_Queue.push_back(runnable);
            }
            m_QueueCV.Notify();
        }

    }

    ThreadpoolWorker::ThreadpoolWorker(Threadpool* threadpool) noexcept
        : m_Threadpool{ threadpool }
    {
    }

    ThreadpoolWorker::~ThreadpoolWorker() noexcept
    {
    }

    uint32_t ThreadpoolWorker::OnRun() noexcept
    {
        GX_PROFILE_REGION("OnRun");
        for (;;)
        {
            IRunnable* task = nullptr;
            {
                Threading::ScopedLock<Threading::CriticalSection> lock{ m_Threadpool->m_QueueCS };

                while (!m_Threadpool->m_Stop && m_Threadpool->m_Queue.empty())
                {
                    m_Threadpool->m_QueueCV.Wait(m_Threadpool->m_QueueCS);
                }

                if (m_Threadpool->m_Stop && m_Threadpool->m_Queue.empty())
                {
                    break;
                }

                task = m_Threadpool->m_Queue.front();
                m_Threadpool->m_Queue.pop_front();
            }

            task->OnStart();
            task->OnRun();
            task->OnStop();
            task->OnExit();
        }

        return 0;
    }
}

#include <Graphyte/Diagnostics.hxx>

GX_DECLARE_LOG_CATEGORY(LogTestThreadpool, Trace, Trace);
GX_DEFINE_LOG_CATEGORY(LogTestThreadpool);

TEST_CASE("Threadpool", "[.][performance]")
{
    SECTION("Spawn workerz")
    {
#define DELAY 200
#define THREADS 8
#define COUNT 8
#define TASKS 128

        struct tazg : public Graphyte::Threading::IRunnable
        {
            uint32_t OnRun() noexcept override
            {
                GX_PROFILE_REGION("Thread pool task");

                for (size_t i = 0; i < COUNT; i++)
                {
                    Graphyte::Threading::SleepThread(DELAY);
                }

                GX_LOG(LogTestThreadpool, Trace, "tazg\n");
                return 0;
            }
        } tazgz[TASKS];
        {
            Graphyte::Diagnostics::Stopwatch watch{};
            {
                GraphyteX::Threading::Threadpool pool{ THREADS };

                {
                    watch.Start();
                    for (auto&& t : tazgz)
                    {
                        pool.Schedule(&t);
                    }
                }
            }
            watch.Stop();

            [[maybe_unused]] double const sequential = static_cast<double>(TASKS * DELAY * COUNT) * 0.001;
            [[maybe_unused]] double const parallel = watch.GetElapsedTime();
            [[maybe_unused]] double const speedup = sequential / parallel;

            //GX_DEBUGF("Expected duration: {}\n", sequential);
            //GX_DEBUGF("Total duration:    {}\n", parallel);
            //GX_DEBUGF("Speedup:           {}\n", speedup);
        }
    }
}
