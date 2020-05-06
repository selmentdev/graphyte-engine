#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Threading/SpinLock.hxx>
#include <GxBase/Bitwise.hxx>
#include <GxBase/Diagnostics.hxx>

namespace Graphyte
{
    /**
     * @brief   This class is base class for all pool containers.
     *
     * @tparam  ElementCount      Number of elements within single pool descriptor.
     */
    template <std::size_t ElementCount>
    class PoolContainerBase
    {
        static_assert((ElementCount % 64) == 0);
        static_assert(IsPowerOf2(ElementCount));

    public:
        /**
         * @brief   Number of elements within pool descriptor.
         */
        static constexpr const std::size_t PoolCapacity = ElementCount;

    private:
        /**
         * @brief   This type represents allocation address.
         */
        enum class Address : std::uintptr_t
        {
            Invalid = ~std::uintptr_t{},
        };

        /**
         * @brief   This type represents pool descriptor index.
         */
        enum class PoolIndex : std::uintptr_t
        {
            Invalid = ~std::uintptr_t{},
        };

        /**
         * @brief   This type represents allocation index within pool descriptor.
         */
        enum class ItemIndex : std::uintptr_t
        {
            Invalid = ~std::uintptr_t{},
        };

        /**
         * @brief   Makes allocation address from pool and item indices.
         * 
         * @param   pool    Provides index of pool descriptor.
         * @param   item    Provides index of item allocation.
         * 
         * @returns The address of specified allocation.
         */
        static constexpr Address MakeAddress(
            PoolIndex pool,
            ItemIndex item
        ) noexcept
        {
            return static_cast<Address>(
                (ElementCount * static_cast<uintptr_t>(pool)) + static_cast<uintptr_t>(item)
            );
        }

        /**
         * @brief   Gets pool descriptor index from address.
         * 
         * @param   address     Provides an address of allocation.
         * 
         * @returns The pool descriptor index.
         */
        static constexpr PoolIndex GetPoolIndex(
            Address address
        ) noexcept
        {
            return static_cast<PoolIndex>(
                static_cast<uintptr_t>(address) / ElementCount
            );
        }

        /**
         * @brief   Gets item allocation index from address.
         * 
         * @param   address     Provides an address of allocation.
         * 
         * @returns The item allocation index.
         */
        static constexpr ItemIndex GetItemIndex(
            Address address
        ) noexcept
        {
            return static_cast<ItemIndex>(
                static_cast<uintptr_t>(address) % ElementCount
            );
        }

    private:
        /**
         * @brief   Represents free item.
         */
        struct FreeItem final
        {
            /**
             * Index of next allocation within current pool descriptor.
             */
            ItemIndex NextFreeItem;
        };

        /**
         * @brief   Represents pool descriptor.
         */
        struct PoolDescriptor final
        {
            /**
             * Allocation masks for allocation items within pool descriptor.
             */
            std::uint64_t Mask[ElementCount / 64];

            /**
             * Pointer to data buffer.
             */
            std::byte* Data;

            /**
             * Number of allocated items within pool descriptor.
             */
            std::size_t Count;

            /**
             * Index of next free item.
             */
            ItemIndex NextFreeItem;

            /**
             * Index of next free pool descriptor.
             */
            PoolIndex NextFreeDescriptor;

            /**
             * @brief   Sets specified item index as allocated.
             * 
             * @param   item    Provides item index.
             */
            void SetAllocated(
                ItemIndex item
            ) noexcept
            {
                const auto base = static_cast<uintptr_t>(item) >> 6;
                const auto bits = static_cast<uintptr_t>(item) & 0b11'1111;
                const uint64_t mask = uint64_t{ 1 } << bits;
                this->Mask[base] |= mask;
            }

            /**
             * @brief   Sets specified item index as unallocated.
             * 
             * @param   item    Provides item index.
             */
            void ClearAllocated(
                ItemIndex item
            ) noexcept
            {
                const auto base = static_cast<uintptr_t>(item) >> 6;
                const auto bits = static_cast<uintptr_t>(item) & 0b11'1111;
                const uint64_t mask = uint64_t{ 1 } << bits;
                this->Mask[base] &= ~mask;
            }

            /**
             * @brief   Checks whether specified item is masked as allocated.
             * 
             * @param   item    Provides item index.
             * 
             * @returns The value indicating whether specified item is allocated.
             */
            bool IsAllocated(
                ItemIndex item
            ) const noexcept
            {
                const auto base = static_cast<uintptr_t>(item) >> 6;
                const auto bits = static_cast<uintptr_t>(item) & 0b11'1111;
                const uint64_t mask = uint64_t{ 1 } << bits;
                return (this->Mask[base] & mask) != 0;
            }
        };

    private:
        std::vector<PoolDescriptor> m_PoolDescriptors;
        std::size_t m_ItemSize;
        std::size_t m_Count;
        PoolIndex m_FreePoolDescriptor;

    private:
        /**
         * @brief   Find specified allocation.
         * 
         * @param   pointer     Provides pointer to allocated item.
         * @param   pool        Returns pool descriptor index of allocation.
         * @param   item        Returns item index of allocation.
         * 
         * @returns The value indicating whether provided pointer was found in pool.
         */
        bool FindPool(
            void* pointer,
            PoolIndex& pool,
            ItemIndex& item
        ) const noexcept
        {
            if (pointer != nullptr)
            {
                //
                // Find pool containing this item.
                //

                std::byte* raw = reinterpret_cast<std::byte*>(pointer);

                for (size_t i = 0; i < m_PoolDescriptors.size(); ++i)
                {
                    const PoolDescriptor& descriptor = m_PoolDescriptors[i];

                    //
                    // Check if pool has any data allocated.
                    //

                    if (descriptor.Data != nullptr)
                    {
                        //
                        // Check if provided pointer is within range of this pool.
                        //

                        std::byte* dataBegin = descriptor.Data;
                        std::byte* dataEnd = dataBegin + (m_ItemSize * ElementCount);

                        if (dataBegin <= raw && raw < dataEnd)
                        {
                            //
                            // Return pool and item indices.
                            //

                            pool = static_cast<PoolIndex>(i);
                            item = static_cast<ItemIndex>(
                                static_cast<uintptr_t>(raw - dataBegin) / m_ItemSize
                            );

                            return true;
                        }
                    }
                }
            }

            //
            // Provided pointer is out of this pool.
            //

            return false;
        }

        /**
         * @brief   Gets allocation data.
         * 
         * @param   descriptor  Provides pool descriptor.
         * @param   item        Provides item index of allocation.
         * 
         * @returns The pointer to allocation data.
         */
        std::byte* GetPoolItem(
            PoolDescriptor& descriptor,
            ItemIndex item
        ) const noexcept
        {
            GX_ASSERTF(descriptor.Data != nullptr, "This pool has no data allocated.");
            return descriptor.Data + (static_cast<size_t>(item) * m_ItemSize);
        }

        /**
         * @brief   Gets allocation data.
         * 
         * @param   pool    Provides pool descriptor index.
         * @param   item    Provides allocation item index.
         * 
         * @returns The pointer to allocation data.
         */
        std::byte* GetPoolItem(
            PoolIndex pool,
            ItemIndex item
        ) const noexcept
        {
            GX_ASSERT(static_cast<size_t>(pool) < m_PoolDescriptors.size());
            GX_ASSERT(static_cast<size_t>(item) < ElementCount);

            return m_PoolDescriptors[static_cast<size_t>(pool)].Data + (static_cast<size_t>(item) * m_ItemSize);
        }

        /**
         * @brief   Gets free item for specified pool descriptor allocation item.
         * 
         * @param   descriptor  Provides pool descriptor.
         * @param   item        Provides allocation item index.
         * 
         * @returns The pointer to free item link.
         */
        FreeItem* GetPoolFreeItem(
            PoolDescriptor& descriptor,
            ItemIndex item
        ) const noexcept
        {
            return reinterpret_cast<FreeItem*>(GetPoolItem(descriptor, item));
        }

        /**
         * @brief   Gets allocation data for specified address.
         * 
         * @param   address     Provides address of allocation.
         * 
         * @returns The pointer to allocation data.
         */ 
        std::byte* GetPoolItem(Address address) const noexcept
        {
            return GetPoolItem(
                GetPoolIndex(address),
                GetItemIndex(address)
            );
        }

        /**
         * @brief   Allocates new pool descriptor.
         * 
         * @returns The pool index of newly allocated pool descriptor.
         */
        PoolIndex AllocateDescriptor() noexcept
        {
            PoolIndex pool{ PoolIndex::Invalid };

            //
            // Check already initialized pool descriptors.
            //

            for (size_t i = 0; i < m_PoolDescriptors.size(); ++i)
            {
                if (m_PoolDescriptors[i].Data == nullptr)
                {
                    //
                    // Found free pool descriptor.
                    //

                    pool = static_cast<PoolIndex>(i);
                    break;
                }
            }

            if (pool == PoolIndex::Invalid)
            {
                //
                // All pools are used. Allocate new pool descriptor.
                //

                pool = static_cast<PoolIndex>(m_PoolDescriptors.size());
                m_PoolDescriptors.resize(m_PoolDescriptors.size() + 1);
            }

            //
            // Grab free pool descriptor.
            //

            PoolDescriptor& descriptor = m_PoolDescriptors[static_cast<size_t>(pool)];

            //
            // Allocate buffer.
            //

            std::byte* data = new std::byte[m_ItemSize * ElementCount];
            descriptor.Data = data;

            //
            // Create linked list of free items.
            //

            descriptor.NextFreeItem = ItemIndex{};

            for (size_t i = 0; i < (ElementCount - 1); ++i)
            {
                GetPoolFreeItem(descriptor, static_cast<ItemIndex>(i))->NextFreeItem = static_cast<ItemIndex>(i + 1);
            }

            GetPoolFreeItem(descriptor, static_cast<ItemIndex>(ElementCount - 1))->NextFreeItem = ItemIndex::Invalid;

            //
            // Link descriptor to list of free pool descriptors.
            //

            descriptor.NextFreeDescriptor = m_FreePoolDescriptor;
            m_FreePoolDescriptor = pool;

            return pool;
        }

        /**
         * @brief   Deallocates pool descriptor for specified pool index.
         * 
         * @param   pool    Provides pool descriptor index to deallocate.
         */
        void DeallocateDescriptor(PoolIndex pool) noexcept
        {
            GX_ASSERT(static_cast<size_t>(pool) < m_PoolDescriptors.size());

            //
            // Get pool descriptor.
            //

            PoolDescriptor& descriptor = m_PoolDescriptors[static_cast<size_t>(pool)];
            GX_ASSERT(descriptor.Count == 0);

            //
            // Free buffer.
            //

            delete[] descriptor.Data;
            descriptor.Data = nullptr;

            //
            // Mark it as free.
            //

            descriptor.NextFreeItem = ItemIndex::Invalid;

            //
            // Unlink pool descriptors.
            //
            // Note:
            //      Because list of free pool descriptors is singly linked, we reiterate over all
            //      descriptor pools and link those, which has allocated buffers. This will allow
            //      to reuse empty pool descriptor when we need to allocate new data buffer.
            //

            PoolIndex* freePool = &m_FreePoolDescriptor;

            for (size_t i = 0; i < m_PoolDescriptors.size(); ++i)
            {
                PoolDescriptor& current = m_PoolDescriptors[i];

                if (current.NextFreeItem != ItemIndex::Invalid)
                {
                    *freePool = static_cast<PoolIndex>(i);
                    freePool = &current.NextFreeDescriptor;
                }
            }

            *freePool = PoolIndex::Invalid;
        }

        /**
         * @brief   Deallocates single item from specified pool.
         * 
         * @param   pool    Provides pool index.
         * @param   item    Provides item index.
         */
        void DeallocateItem(PoolIndex pool, ItemIndex item) noexcept
        {
            GX_ASSERT(static_cast<size_t>(pool) < m_PoolDescriptors.size());
            GX_ASSERT(static_cast<size_t>(item) < ElementCount);

            //
            // Get pool descriptor.
            //

            PoolDescriptor& descriptor = m_PoolDescriptors[static_cast<size_t>(pool)];
            GX_ASSERT(descriptor.IsAllocated(item));
            GX_ASSERT(descriptor.Count != 0);

            //
            // Update allocation info.
            //

            --m_Count;
            descriptor.ClearAllocated(item);

            if (--descriptor.Count != 0)
            {
                //
                // Descriptor has allocated items.
                //

                if (descriptor.Count == (ElementCount - 1))
                {
                    //
                    // This pool descriptor was full. Link it back into list of free pool descriptors.
                    //

                    descriptor.NextFreeDescriptor = m_FreePoolDescriptor;
                    m_FreePoolDescriptor = pool;
                }

                //
                // Link deallocated item into free list.
                //

                FreeItem* link = GetPoolFreeItem(descriptor, item);
                link->NextFreeItem = descriptor.NextFreeItem;
                descriptor.NextFreeItem = item;
            }
            else
            {
                //
                // Descriptor is now empty. Deallocate it.
                //

                DeallocateDescriptor(pool);
            }
        }

    public:
        /**
         * @brief   Allocates new item from pool.
         * 
         * @returns The address of newly allocated item.
         */
        Address AllocateItem() noexcept
        {
            if (m_FreePoolDescriptor == PoolIndex::Invalid)
            {
                //
                // Expand pool by another descriptor.
                //

                AllocateDescriptor();
            }

            //
            // Get free pool descriptor.
            //

            PoolIndex freePool = m_FreePoolDescriptor;
            GX_ASSERT(freePool != PoolIndex::Invalid);

            PoolDescriptor& descriptor = m_PoolDescriptors[static_cast<size_t>(freePool)];

            //
            // Grab free item from pool.
            //

            ItemIndex freeIndex = descriptor.NextFreeItem;
            GX_ASSERT(!descriptor.IsAllocated(freeIndex));

            //
            // Allocate item.
            //

            FreeItem* freeItem = GetPoolFreeItem(descriptor, freeIndex);
            descriptor.SetAllocated(freeIndex);
            descriptor.NextFreeItem = freeItem->NextFreeItem;
            ++descriptor.Count;

            if (descriptor.NextFreeItem == ItemIndex::Invalid)
            {
                //
                // Pool was exhausted. Unlink this pool from free list.
                //

                m_FreePoolDescriptor = descriptor.NextFreeDescriptor;

                //
                // Next pool must contain free item.
                //

                GX_ASSERT(
                    m_FreePoolDescriptor == PoolIndex::Invalid ||
                    m_PoolDescriptors[static_cast<size_t>(m_FreePoolDescriptor)].NextFreeItem != ItemIndex::Invalid
                );
            }

            //
            // Update total allocations counter.
            //

            ++m_Count;

            //
            // Return address of allocated item.
            //

            return MakeAddress(freePool, freeIndex);
        }

        /**
         * @brief   Deallocates item from pool.
         * 
         * @param   address     Provides address of allocation to deallocate.
         */
        void DeallocateItem(Address address) noexcept
        {
            PoolIndex pool = GetPoolIndex(address);
            ItemIndex item = GetItemIndex(address);

            DeallocateItem(pool, item);
        }

    public:
        /**
         * @brief   Initializes new instance of PoolContainerBase for specified item size.
         * 
         * @param   size    Provides size of item in pool.
         */
        PoolContainerBase(std::size_t size) noexcept
            : m_PoolDescriptors{}
            , m_ItemSize{ std::max(size, sizeof(void*)) }
            , m_Count{}
            , m_FreePoolDescriptor{ PoolIndex::Invalid }
        {
        }

        ~PoolContainerBase() noexcept
        {
            for (auto& pool : m_PoolDescriptors)
            {
                delete[] pool.Data;
            }
        }

        /**
         * @brief   Allocates new item in pool.
         * 
         * @returns The pointer to newly allocated item.
         */
        void* DoAllocate() noexcept
        {
            //
            // Allocate item from pool.
            //

            auto address = this->AllocateItem();

            //
            // Convert address to pointer.
            //

            return GetPoolItem(address);
        }

        /**
         * @brief   Deallocates item from pool.
         * 
         * @param   pointer     Provides pointer to item to deallocate.
         */
        void DoDeallocate(void* pointer) noexcept
        {
            PoolIndex pool;
            ItemIndex item;

            if (pointer != nullptr && this->FindPool(pointer, pool, item))
            {
                //
                // Check if this pool has valid indices.
                //

                GX_ASSERT(static_cast<size_t>(pool) < m_PoolDescriptors.size());
                GX_ASSERT(static_cast<size_t>(item) < ElementCount);

                //
                // Forward call.
                //

                this->DeallocateItem(pool, item);
            }
            else
            {
                GX_ASSERTF(false, "Provided pointer isn't in pool");
            }
        }

        /**
         * @brief   Checks whether provided pointer is allocated.
         * 
         * @param   pointer     Provides pointer to allocation.
         * 
         * @returns The value indicating whether pointer is allocated.
         */
        bool IsAllocated(void* pointer) const noexcept
        {
            PoolIndex pool;
            ItemIndex item;

            if (this->FindPool(pointer, pool, item))
            {
                //
                // Check if this pool has valid indices.
                //

                GX_ASSERT(static_cast<size_t>(pool) < m_PoolDescriptors.size());
                GX_ASSERT(static_cast<size_t>(item) < ElementCount);

                //
                // Forward call to specific pool descriptor.
                //

                return (static_cast<size_t>(pool) < m_PoolDescriptors.size())
                    && (m_PoolDescriptors[static_cast<size_t>(pool)].IsAllocated(item));
            }

            return false;
        }

        /**
         * @brief   Gets item size.
         */
        std::size_t GetItemSize() const noexcept
        {
            return m_ItemSize;
        }

        /**
         * @brief   Gets number of elements within pool.
         */
        std::size_t GetCount() const noexcept
        {
            return m_Count;
        }

        /**
         * @brief   Gets capacity of pool collection.
         */
        std::size_t GetCapacity() const noexcept
        {
            return m_PoolDescriptors.size() * ElementCount;
        }

    };

    /**
     * @brief   This class provides generic pool interface.
     * 
     * @tparam  TType   Provides type of element in pool.
     * @tparam  ElementCount  Number of elements within single pool descriptor.
     */
    template <typename TType, size_t ElementCount>
    class PoolContainer final : public PoolContainerBase<ElementCount>
    {
    public:
        PoolContainer() noexcept
            : PoolContainerBase<ElementCount>{ sizeof(TType) }
        {
        }

        TType* Allocate() noexcept
        {
            TType* result = reinterpret_cast<TType*>(this->DoAllocate());
            new (result) TType();
            return result;
        }

        void Deallocate(TType* pointer) noexcept
        {
            if (pointer != nullptr)
            {
                pointer->~TType();
                this->DoDeallocate(pointer);
            }
        }
    };
}
