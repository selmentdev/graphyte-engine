#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/System.hxx>

namespace Graphyte::Diagnostics
{
    class Stopwatch final
    {
    private:
        int64_t m_Elapsed;
        int64_t m_Start;
        int64_t m_Resolution;
        bool m_IsRunning;

    public:
        Stopwatch() noexcept
            : m_Elapsed{}
            , m_Start{}
            , m_Resolution{ static_cast<int64_t>(System::GetTimestampResolution()) }
            , m_IsRunning{}
        {
        }

    public:
        bool IsRunning() const noexcept
        {
            return this->m_IsRunning;
        }

        int64_t GetFrequency() const noexcept
        {
            return m_Resolution;
        }

        int64_t GetElapsedTicks() const noexcept
        {
            return this->m_Elapsed;
        }

        double GetElapsedTime() const noexcept
        {
            return
                static_cast<double>(this->m_Elapsed)
                /
                static_cast<double>(m_Resolution);
        }

    public:
        void Start() noexcept
        {
            if (!this->m_IsRunning)
            {
                this->m_Start = static_cast<int64_t>(System::GetTimestamp());
                this->m_IsRunning = true;
            }
        }

        void Stop() noexcept
        {
            if (this->m_IsRunning)
            {
                int64_t const end = static_cast<int64_t>(System::GetTimestamp());
                int64_t const elapsed = end - this->m_Start;

                this->m_Elapsed += elapsed;

                if (this->m_Elapsed < 0)
                {
                    this->m_Elapsed = 0;
                }
            }
        }

        void Reset() noexcept
        {
            this->m_Elapsed = 0;
            this->m_Start = 0;
            this->m_IsRunning = false;
        }

        void Restart() noexcept
        {
            this->m_Elapsed = 0;
            this->m_Start = static_cast<int64_t>(System::GetTimestamp());
            this->m_IsRunning = true;
        }
    };
}
