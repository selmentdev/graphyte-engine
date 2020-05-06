#include <GxBase/Diagnostics/Profiler.hxx>
#include <GxBase/Threading.hxx>
#include <GxBase/Threading/Sync.hxx>
#include <GxBase/Threading/TaskDispatcher.hxx>
#include <GxBase/System.hxx>

namespace Graphyte::Threading
{
    struct ParallelForData final
    {
    public:
        std::function<void(uint32_t)> Code;
        Threading::Event Sync;
        std::atomic<uint32_t> Index;
        std::atomic<uint32_t> Completed;
        uint32_t Count;
        uint32_t BlockSize;
        uint32_t BlockOverhead;
        bool Exited;
        bool Triggered;
        bool LastBlockForMaster;

    public:
        ParallelForData(
            uint32_t count,
            uint32_t threads,
            bool last_block_for_master,
            std::function<void(uint32_t)> code
        ) noexcept
            : Code{ code }
            , Sync{ false, Threading::EventType::ManualReset }
            , Index{}
            , Completed{}
            , Count{ count }
            , BlockSize{}
            , BlockOverhead{}
            , Exited{ false }
            , Triggered{ false }
            , LastBlockForMaster{ last_block_for_master }
        {
            GX_ASSERTF(count >= threads, "Too many threads for tasks");

            for (uint32_t div = 6; div != 0; --div)
            {
                BlockSize = count / (threads * div);

                if (BlockSize != 0)
                {
                    Count = count / BlockSize;
                    if (Count >= (threads + !!last_block_for_master))
                    {
                        break;
                    }
                }
            }

            GX_ASSERT(BlockSize != 0 && Count != 0);
            BlockOverhead = (count - Count * BlockSize);
            //GX_ASSERT(BlockOverhead >= 0);
        }

        ~ParallelForData() noexcept
        {
            GX_ASSERT(Index.load() >= Count);
            GX_ASSERT(Completed.load() == Count);
            GX_ASSERT(Exited == true);
        }

        bool Process(
            uint32_t tasks_to_spawn,
            const std::shared_ptr<ParallelForData>& data,
            bool master
        ) noexcept;
    };

    struct ParallelForTask final
    {
    public:
        std::shared_ptr<ParallelForData> Data;
        uint32_t TasksToSpawn;

    public:
        ParallelForTask(
            const std::shared_ptr<ParallelForData>& data,
            uint32_t tasks_to_spawn = 0
        ) noexcept
            : Data{ data }
            , TasksToSpawn{ tasks_to_spawn }
        {
        }

        void DoTask() noexcept
        {
            if (Data->Process(TasksToSpawn, Data, false))
            {
                GX_ASSERT(Data->Triggered == false);
                Data->Triggered = true;
                Data->Sync.Set();
            }
        }
    };


    bool ParallelForData::Process(
        uint32_t tasks_to_spawn,
        const std::shared_ptr<ParallelForData>& data,
        bool master
    ) noexcept
    {
        GX_PROFILE_REGION("parallel-for-process");

        uint32_t maybe_tasks_left = Count - Index.load();

        if (tasks_to_spawn && maybe_tasks_left != 0)
        {
            tasks_to_spawn = std::min<uint32_t>(tasks_to_spawn, maybe_tasks_left);

            Task<ParallelForTask>::CreateTask().Dispatch(data, tasks_to_spawn - 1);
        }

        uint32_t local_block_size = BlockSize;
        uint32_t local_count = Count;
        bool local_last_block_for_master = LastBlockForMaster;

        std::function<void(uint32_t)> local_code{ Code };

        for (;;)
        {
            uint32_t my_index = ++Index - 1;

            if (local_last_block_for_master)
            {
                if (!master && my_index >= (local_count - 1))
                {
                    break;
                }
                else if (master && my_index > (local_count - 1))
                {
                    my_index = local_count - 1;
                }
            }

            if (my_index < local_count)
            {
                uint32_t this_block_size = local_block_size;

                if (my_index == local_count - 1)
                {
                    this_block_size += BlockOverhead;
                }

                {
                    GX_PROFILE_REGION(fmt::format("{}-tasks", this_block_size).c_str());
                    for (uint32_t local_index = 0; local_index < this_block_size; ++local_index)
                    {
                        local_code(my_index * local_block_size + local_index);
                    }
                }
                GX_ASSERT(!Exited);

                uint32_t local_count_completed = ++Completed;

                if (local_count_completed == local_count)
                {
                    return true;
                }

                GX_ASSERT(local_count_completed < local_count);
            }

            if (my_index >= (local_count - 1))
            {
                break;
            }
        }

        return false;
    }

    void ParallelFor(
        uint32_t count,
        std::function<void(uint32_t)> code,
        bool singlethreaded
    ) noexcept
    {
        GX_PROFILE_REGION("parallel-for");

        uint32_t threads = 0;

        if (count > 1 && !singlethreaded)
        {
            threads = std::min<uint32_t>(
                static_cast<uint32_t>(System::GetWorkerThreads()),
                count - 1
            );
        }

        if (threads == 0)
        {
            for (uint32_t index = 0; index < count; ++index)
            {
                code(index);
            }
            return;
        }

        GX_ASSERT(count != 0);

        auto data = std::make_shared<ParallelForData>(count, threads + 1, count > (threads + 1), std::move(code));

        Task<ParallelForTask>::CreateTask().Dispatch(data, threads - 1);

        if (!data->Process(0, data, true))
        {
            GX_PROFILE_REGION("parallel-for-waiting");
            data->Sync.Wait();
            GX_ASSERT(data->Triggered == true);
        }
        else
        {
            GX_ASSERT(data->Triggered == false);
        }

        GX_ASSERT(data->Completed.load() == data->Count);
        data->Exited = true;
    }

    void ParallelFor(
        uint32_t count,
        std::function<void(uint32_t)> code,
        std::function<void(void)> preprocess,
        bool singlethreaded
    ) noexcept
    {
        GX_PROFILE_REGION("parallel-for");

        uint32_t threads = 0;
        if (count > 1 && !singlethreaded)
        {
            threads = std::min<uint32_t>(static_cast<uint32_t>(System::GetWorkerThreads()), count - 1);
        }

        if (threads == 0)
        {
            preprocess();

            for (uint32_t index = 0; index < count; ++index)
            {
                code(index);
            }
            return;
        }

        GX_ASSERT(count != 0);

        auto data = std::make_shared<ParallelForData>(count, threads, false, std::move(code));

        preprocess();

        Task<ParallelForTask>::CreateTask().Dispatch(data, threads - 1);

        if (!data->Process(0, data, true))
        {
            GX_PROFILE_REGION("parallel-for-waiting");
            data->Sync.Wait();
            GX_ASSERT(data->Triggered == true);
        }
        else
        {
            GX_ASSERT(data->Triggered == false);
        }

        GX_ASSERT(data->Completed.load() == data->Count);
        data->Exited = true;
    }
}
