#include <catch2/catch.hpp>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/Threading/Thread.hxx>
#include <GxBase/Threading/Runnable.hxx>
#include <GxBase/Threading/Sync.hxx>
#include <GxBase/Threading.hxx>
#include <GxBase/Stopwatch.hxx>

TEST_CASE("Threading / Parallel For")
{
    constexpr uint32_t const N = 40'000u;

    // counting in parallel

    std::atomic<uint32_t> counter{};
    std::atomic<uint32_t> multiplier{};

    Graphyte::Threading::ParallelFor(N, [&](uint32_t index) {
        ++counter;
        multiplier += index;
    });

    REQUIRE(multiplier == (N * (N - 1)) / 2);
    REQUIRE(counter == N);
}

TEST_CASE("ReaderWriterLockCase", "[.][performance]")
{
    using namespace Graphyte::Threading;

    class ProducerRunnable : public IRunnable
    {
    private:
        ReaderWriterLock* _lock;
        std::vector<uint32_t>* _data;
        uint32_t _limit;
        uint32_t _id;
        std::atomic<uint32_t>* _total;

    public:
        ProducerRunnable(uint32_t id, ReaderWriterLock* lock, std::vector<uint32_t>* data, uint32_t limit, std::atomic<uint32_t>* total)
            : _lock(lock)
            , _data(data)
            , _limit(limit)
            , _id(id)
            , _total(total)
        {
        }

        virtual ~ProducerRunnable()
        {
        }

    public:
        virtual uint32_t OnRun() noexcept override
        {
            for (uint32_t i = 0; i < _limit; ++i)
            {
                _lock->EnterWriter();
                {
                    *_total += _id * _limit + i;
                    _data->push_back(_id * _limit + i);
                }
                _lock->LeaveWriter();

                SleepThread(100);
            }

            return 0;
        }
    };

    ReaderWriterLock rwlock;
    std::vector<uint32_t> data;
    std::atomic<uint32_t> writer_total = 0;
    std::atomic<uint32_t> reader_total = 0;

    ProducerRunnable r1(0, &rwlock, &data, 100, &writer_total);
    ProducerRunnable r2(1, &rwlock, &data, 100, &writer_total);
    ProducerRunnable r3(2, &rwlock, &data, 100, &writer_total);
    ProducerRunnable r4(3, &rwlock, &data, 100, &writer_total);
    ProducerRunnable r5(4, &rwlock, &data, 100, &writer_total);

    Thread t1{};
    Thread t2{};
    Thread t3{};
    Thread t4{};
    Thread t5{};

    t1.Start(&r1, "R1");
    t2.Start(&r2, "R2");
    t3.Start(&r3, "R3");
    t4.Start(&r4, "R4");
    t5.Start(&r5, "R5");

    for (size_t i = 0; i < (100 * 5); ++i)
    {
        SleepThread(100);

        uint32_t v;
        rwlock.EnterReader();
        {
            v = data.back();
            data.pop_back();
        }
        rwlock.LeaveReader();

        reader_total += v;
    }

    t1.Stop(true);
    t2.Stop(true);
    t3.Stop(true);
    t4.Stop(true);
    t5.Stop(true);

    REQUIRE(writer_total == 124750);
    REQUIRE(reader_total == 124750);
}

TEST_CASE("IncrementInterlockedCase", "[.][performance]")
{
    using namespace Graphyte::Threading;

    std::atomic<uint32_t> count = 0;

    class Incrementer : public IRunnable
    {
    private:
        std::atomic<uint32_t>* _count;
        size_t _reps;

    public:
        Incrementer(size_t reps, std::atomic<uint32_t>* count)
            : _count(count)
            , _reps(reps)
        {
        }

        virtual ~Incrementer()
        {
        }

        virtual uint32_t OnRun() noexcept override
        {
            for (size_t i = 0; i < _reps; ++i)
            {
                ++*_count;
            }

            return 0;
        }
    };

    Incrementer r0(10000, &count);
    Incrementer r1(10000, &count);
    Incrementer r2(10000, &count);
    Incrementer r3(10000, &count);
    Incrementer r4(10000, &count);
    Incrementer r5(10000, &count);
    Incrementer r6(10000, &count);
    Incrementer r7(10000, &count);
    Incrementer r8(10000, &count);
    Incrementer r9(10000, &count);

    Thread t0{};
    Thread t1{};
    Thread t2{};
    Thread t3{};
    Thread t4{};
    Thread t5{};
    Thread t6{};
    Thread t7{};
    Thread t8{};
    Thread t9{};

    t0.Start(&r0, "R0");
    t1.Start(&r1, "R1");
    t2.Start(&r2, "R2");
    t3.Start(&r3, "R3");
    t4.Start(&r4, "R4");
    t5.Start(&r5, "R5");
    t6.Start(&r6, "R6");
    t7.Start(&r7, "R7");
    t8.Start(&r8, "R8");
    t9.Start(&r9, "R9");

    t0.Stop(true);
    t1.Stop(true);
    t2.Stop(true);
    t3.Stop(true);
    t4.Stop(true);
    t5.Stop(true);
    t6.Stop(true);
    t7.Stop(true);
    t8.Stop(true);
    t9.Stop(true);

    REQUIRE(count == (10000 * 10));
}

TEST_CASE("IncrementCriticalSectionCase", "[.][performance]")
{
    using namespace Graphyte::Threading;

    CriticalSection cs;
    uint32_t count = 0;

    class Incrementer : public IRunnable
    {
    private:
        uint32_t* _count;
        size_t _reps;
        CriticalSection* _cs;

    public:
        Incrementer(size_t reps, uint32_t* count, CriticalSection* cs)
            : _count(count)
            , _reps(reps)
            , _cs(cs)
        {
        }

        virtual ~Incrementer()
        {
        }

        virtual uint32_t OnRun() noexcept override
        {
            for (size_t i = 0; i < _reps; ++i)
            {
                _cs->Enter();
                ++(*_count);
                _cs->Leave();
            }

            return 0;
        }
    };

    Incrementer r0(10000, &count, &cs);
    Incrementer r1(10000, &count, &cs);
    Incrementer r2(10000, &count, &cs);
    Incrementer r3(10000, &count, &cs);
    Incrementer r4(10000, &count, &cs);
    Incrementer r5(10000, &count, &cs);
    Incrementer r6(10000, &count, &cs);
    Incrementer r7(10000, &count, &cs);
    Incrementer r8(10000, &count, &cs);
    Incrementer r9(10000, &count, &cs);

    Thread t0{};
    Thread t1{};
    Thread t2{};
    Thread t3{};
    Thread t4{};
    Thread t5{};
    Thread t6{};
    Thread t7{};
    Thread t8{};
    Thread t9{};

    t0.Start(&r0, "R0");
    t1.Start(&r1, "R1");
    t2.Start(&r2, "R2");
    t3.Start(&r3, "R3");
    t4.Start(&r4, "R4");
    t5.Start(&r5, "R5");
    t6.Start(&r6, "R6");
    t7.Start(&r7, "R7");
    t8.Start(&r8, "R8");
    t9.Start(&r9, "R9");

    t0.Stop(true);
    t1.Stop(true);
    t2.Stop(true);
    t3.Stop(true);
    t4.Stop(true);
    t5.Stop(true);
    t6.Stop(true);
    t7.Stop(true);
    t8.Stop(true);
    t9.Stop(true);

    REQUIRE(count == (10000 * 10));
}

TEST_CASE("IncrementReaderWriterLockCase", "[.][performance]")
{
    using namespace Graphyte::Threading;

    ReaderWriterLock cs;
    uint32_t count = 0;

    class Incrementer : public IRunnable
    {
    private:
        uint32_t* _count;
        size_t _reps;
        ReaderWriterLock* _rwl;

    public:
        Incrementer(size_t reps, uint32_t* count, ReaderWriterLock* rwl)
            : _count(count)
            , _reps(reps)
            , _rwl(rwl)
        {
        }

        virtual ~Incrementer()
        {
        }

        virtual uint32_t OnRun() noexcept override
        {
            for (size_t i = 0; i < _reps; ++i)
            {
                _rwl->EnterWriter();
                ++(*_count);
                _rwl->LeaveWriter();
            }

            return 0;
        }
    };

    Incrementer r0(10000, &count, &cs);
    Incrementer r1(10000, &count, &cs);
    Incrementer r2(10000, &count, &cs);
    Incrementer r3(10000, &count, &cs);
    Incrementer r4(10000, &count, &cs);
    Incrementer r5(10000, &count, &cs);
    Incrementer r6(10000, &count, &cs);
    Incrementer r7(10000, &count, &cs);
    Incrementer r8(10000, &count, &cs);
    Incrementer r9(10000, &count, &cs);


    Thread t0{};
    Thread t1{};
    Thread t2{};
    Thread t3{};
    Thread t4{};
    Thread t5{};
    Thread t6{};
    Thread t7{};
    Thread t8{};
    Thread t9{};

    t0.Start(&r0, "R0");
    t1.Start(&r1, "R1");
    t2.Start(&r2, "R2");
    t3.Start(&r3, "R3");
    t4.Start(&r4, "R4");
    t5.Start(&r5, "R5");
    t6.Start(&r6, "R6");
    t7.Start(&r7, "R7");
    t8.Start(&r8, "R8");
    t9.Start(&r9, "R9");

    t0.Stop(true);
    t1.Stop(true);
    t2.Stop(true);
    t3.Stop(true);
    t4.Stop(true);
    t5.Stop(true);
    t6.Stop(true);
    t7.Stop(true);
    t8.Stop(true);
    t9.Stop(true);

    REQUIRE(count == (10000 * 10));
}

TEST_CASE("BarrierCase", "[.][performance]")
{
    using namespace Graphyte::Threading;


    class ThreadBarrier : public IRunnable
    {
    private:
        Barrier* _barrier;

    public:
        ThreadBarrier(Barrier* barrier)
            : _barrier(barrier)
        {
        }

    public:
        virtual uint32_t OnRun() noexcept override
        {
            {
                _barrier->Wait();
            }

            for (size_t i = 0; i < 10; ++i)
            {
                SleepThread(static_cast<uint32_t>(static_cast<float>(i) * 1.125F));
            }

            {
                _barrier->Wait();
            }

            return 0;
        }
    };

    Barrier barrier(3);

    ThreadBarrier r1(&barrier);
    ThreadBarrier r2(&barrier);
    ThreadBarrier r3(&barrier);

    Thread t1{};
    Thread t2{};
    Thread t3{};

    t1.Start(&r1, "R1");
    t2.Start(&r2, "R2");
    t3.Start(&r3, "R3");

    t1.Stop(true);
    t2.Stop(true);
    t3.Stop(true);
}

TEST_CASE("ProducerConsumerCase", "[.][performance]")
{
    using namespace Graphyte::Threading;

    constexpr size_t BUFFER_SIZE            = 10;
    constexpr size_t PRODUCER_SLEEP_TIME_MS = 50;
    constexpr size_t CONSUMER_SLEEP_TIME_MS = 200;

    struct Context
    {
        int32_t Buffer[BUFFER_SIZE];
        std::atomic<int32_t> LastItemProduced;
        uint32_t QueueSize;
        uint32_t QueueStartOffset;
        uint32_t TotalItemsProduced;
        uint32_t TotalItemsConsumed;
        ConditionVariable BufferNotEmpty;
        ConditionVariable BufferNotFull;
        CriticalSection BufferLock;
        bool StopRequested;
    };

    class Producer : public IRunnable
    {
    private:
        Context* _context;
        uint32_t _id;

    public:
        Producer(Context* context, uint32_t id)
            : _context(context)
            , _id(id)
        {
        }

    public:
        virtual uint32_t OnRun() noexcept override
        {
            for (;;)
            {
                SleepThread(static_cast<uint32_t>(static_cast<size_t>(rand()) % PRODUCER_SLEEP_TIME_MS));

                int32_t Item = ++_context->LastItemProduced;

                _context->BufferLock.Enter();

                while (_context->QueueSize == BUFFER_SIZE && _context->StopRequested == false)
                {
                    _context->BufferNotFull.Wait(_context->BufferLock);
                }

                if (_context->StopRequested == true)
                {
                    _context->BufferLock.Leave();
                    break;
                }

                _context->Buffer[(_context->QueueStartOffset + _context->QueueSize) % BUFFER_SIZE] = Item;
                ++_context->QueueSize;
                ++_context->TotalItemsProduced;

                _context->BufferLock.Leave();

                _context->BufferNotEmpty.Notify();
            }

            return 0;
        }

        uint32_t GetId() const noexcept
        {
            return _id;
        }
    };

    class Consumer : public IRunnable
    {
    private:
        Context* _context;
        uint32_t _id;

    public:
        Consumer(Context* context, uint32_t id)
            : _context(context)
            , _id(id)
        {
        }

    public:
        virtual uint32_t OnRun() noexcept override
        {
            for (;;)
            {
                _context->BufferLock.Enter();

                while (_context->QueueSize == 0 && _context->StopRequested == false)
                {
                    _context->BufferNotEmpty.Wait(_context->BufferLock);
                }

                if (_context->StopRequested == true && _context->QueueSize == 0)
                {
                    _context->BufferLock.Leave();
                    break;
                }

                --_context->QueueSize;
                ++_context->QueueStartOffset;
                ++_context->TotalItemsConsumed;

                if (_context->QueueStartOffset == BUFFER_SIZE)
                {
                    _context->QueueStartOffset = 0;
                }

                _context->BufferLock.Leave();

                _context->BufferNotFull.Notify();

                SleepThread(static_cast<uint32_t>(static_cast<size_t>(rand()) % CONSUMER_SLEEP_TIME_MS));
            }

            return 0;
        }

        uint32_t GetId() const
        {
            return _id;
        }
    };

    Context context;

    context.QueueSize          = 0;
    context.QueueStartOffset   = 0;
    context.TotalItemsConsumed = 0;
    context.TotalItemsProduced = 0;
    context.LastItemProduced   = 0;
    context.StopRequested      = false;

    Producer producer(&context, 0);
    Consumer consumer1(&context, 1);
    Consumer consumer2(&context, 2);

    Thread tproducer{};
    Thread tconsumer1{};
    Thread tconsumer2{};

    tproducer.Start(&producer, "Producer");
    tconsumer1.Start(&consumer1, "Consumer 1");
    tconsumer2.Start(&consumer2, "Consumer 2");

    SleepThread(6000);

    context.BufferLock.Enter();
    context.StopRequested = true;
    context.BufferLock.Leave();

    context.BufferNotFull.NotifyAll();
    context.BufferNotEmpty.NotifyAll();

    tproducer.Stop(true);
    tconsumer1.Stop(true);
    tconsumer2.Stop(true);
}

TEST_CASE("Non-portable threading test", "[.][performance]")
{
    class MyRunnable : public Graphyte::Threading::IRunnable
    {
    public:
        bool Started = false;
        bool Stopped = false;
        bool Exited  = false;

        virtual uint32_t OnRun() noexcept override
        {
            return 1337;
        }

        virtual bool OnStart() noexcept override
        {
            this->Started = true;
            return true;
        }

        virtual void OnStop() noexcept override
        {
            this->Stopped = true;
        }

        virtual void OnExit() noexcept override
        {
            this->Exited = true;
        }
    };

    SECTION("Sequential threads start & join")
    {
        MyRunnable runnable1{};

        Graphyte::Threading::Thread thread2{};
        thread2.Start(&runnable1, "Some test thread");
        thread2.Join();
        thread2.Stop(true);

        REQUIRE(runnable1.Started == true);
        REQUIRE(runnable1.Stopped == true);
        REQUIRE(runnable1.Exited == true);

        MyRunnable runnable2{};

        thread2.Start(&runnable2, "Some test thread");
        thread2.Join();
        thread2.Stop(true);

        REQUIRE(runnable2.Started == true);
        REQUIRE(runnable2.Stopped == true);
        REQUIRE(runnable2.Exited == true);
    }

    SECTION("Parallel threads start & join")
    {
        MyRunnable runnable1{};
        MyRunnable runnable2{};

        Graphyte::Threading::Thread thread1{};
        Graphyte::Threading::Thread thread2{};
        thread1.Start(&runnable1, "Some test thread");
        thread2.Start(&runnable2, "Some test thread");

        thread1.Join();
        thread2.Join();
        thread1.Stop(true);
        thread2.Stop(true);

        REQUIRE(runnable1.Started == true);
        REQUIRE(runnable1.Stopped == true);
        REQUIRE(runnable1.Exited == true);
        REQUIRE(runnable2.Started == true);
        REQUIRE(runnable2.Stopped == true);
        REQUIRE(runnable2.Exited == true);
    }
}

TEST_CASE("Sleeping threads", "[.][performance]")
{
    struct : public Graphyte::Threading::IRunnable
    {
        virtual uint32_t OnRun() noexcept override
        {
            Graphyte::Threading::SleepThread(1000);
            return 0;
        }
    } runnable{};

    Graphyte::Threading::Thread thread{};
    Graphyte::Diagnostics::Stopwatch watch{};
    watch.Start();
    thread.Start(&runnable, "Runnable");
    thread.Stop(true);
    watch.Stop();
    double const elapsed = watch.GetElapsedTime<double>();
    REQUIRE(elapsed >= 1.0);
}
