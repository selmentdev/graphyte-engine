#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Delegate.hxx>

namespace Graphyte::Threading
{
    /*!
     * \brief   Executes specified code in parallel threads for specified amount of items.
     * 
     * \param   count           Provides number of items to run on parallel threads.
     * \param   code            Provides delegate to invoke for each item in parallel.
     * \param   singlethreaded  Specifies whether this loop should be invoked on single thread.
     */
    BASE_API void ParallelFor(
        uint32_t count,
        Delegate<void(uint32_t)> code,
        bool singlethreaded = false
    ) noexcept;

    /*!
     * \brief   Executes specified code in parallel threads for specified amount of items.
     * 
     * \param   count           Provides number of items to run on parallel threads.
     * \param   code            Provides delegate to invoke for each item in parallel.
     * \param   preprocess      Provides delegate to invoke before parallel for runs.
     * \param   singlethreaded  Specifies whether this loop should be invoked on single thread.
     */
    BASE_API void ParallelFor(
        uint32_t count,
        Delegate<void(uint32_t)> code,
        Delegate<void(void)> preprocess,
        bool singlethreaded = false
    ) noexcept;
}
