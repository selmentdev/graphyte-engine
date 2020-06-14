#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Diagnostics.hxx>

//
// ref: https://github.com/ThePhD/libreality/blob/master/fixed_vector.h
//

namespace notstd
{
    template <typename Value, std::size_t Count, std::size_t Alignment = std::alignment_of_v<Value>>
    class fixed_vector final
    {
    public:
        using value_type = Value;

        using size_type       = std::size_t;
        using difference_type = std::ptrdiff_t;

        using pointer       = Value*;
        using const_pointer = const Value*;

        using reference       = Value&;
        using const_reference = const Value&;

        using iterator       = Value*;
        using const_iterator = const Value*;

        using reverse_iterator       = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        using storage_type = std::aligned_storage_t<sizeof(value_type) * Count, Alignment>;

    private:
        storage_type m_Data;
        size_type m_Size;

    private:
        [[nodiscard]] constexpr value_type* ptr_at(size_type index) noexcept
        {
            return static_cast<value_type*>(static_cast<void*>(&this->m_Data)) + index;
        }

        [[nodiscard]] constexpr const value_type* ptr_at(size_type index) const noexcept
        {
            return static_cast<const value_type*>(static_cast<const void*>(&this->m_Data)) + index;
        }

        [[nodiscard]] constexpr value_type& ref_at(size_type index) noexcept
        {
            return *this->ptr_at(index);
        }

        [[nodiscard]] constexpr const value_type& ref_at(size_type index) const noexcept
        {
            return *this->ptr_at(index);
        }

    public:
        constexpr fixed_vector()
            : m_Data{}
            , m_Size{}
        {
        }

        constexpr fixed_vector(const fixed_vector& other)
            : m_Data{}
            , m_Size{}
        {
            for (size_type i = 0; i < other.size(); ++i)
            {
                this->push_back(other[i]);
            }
        }

        constexpr fixed_vector(fixed_vector&& other)
            : m_Data{}
            , m_Size{}
        {
            for (size_type i = 0; i < other.size(); ++i)
            {
                this->push_back(std::move(other[i]));
            }

            other.clear();
        }

        constexpr fixed_vector& operator=(fixed_vector&& other)
        {
            this->clear();

            for (size_type i = 0; i < other.size(); ++i)
            {
                this->push_back(std::move(other[i]));
            }

            other.clear();
        }

        constexpr fixed_vector& operator=(const fixed_vector& other)
        {
            this->clear();

            for (size_type i = 0; i < other.size(); ++i)
            {
                this->push_back(other[i]);
            }
        }

        constexpr fixed_vector(size_type size, const value_type& default_value = value_type{})
            : m_Data{}
            , m_Size{ size }
        {
            std::fill_n(this->begin(), size, default_value);
        }

        template <std::size_t N>
        constexpr fixed_vector(const value_type (&array)[N])
            : m_Data{}
            , m_Size{ N }
        {
            static_assert(Count <= N, "Array too large to initialize fixed_vector");

            std::copy(
                std::addressof(array[0]),
                std::addressof(array[N]),
                this->data());
        }

        constexpr fixed_vector(std::initializer_list<value_type> initializer)
            : m_Data{}
            , m_Size{ std::min(Count, initializer.size()) }
        {
            std::copy(
                initializer.begin(),
                initializer.begin() + this->size(),
                this->data());
        }

        template <typename TIterator>
        constexpr fixed_vector(TIterator first, TIterator last)
            : m_Data{}
            , m_Size{}
        {
            for (; (this->size() < this->capacity()) && (first != last); ++first)
            {
                this->emplace_back(*first);
            }
        }

        ~fixed_vector()
        {
            this->clear();
        }

    public:
        [[nodiscard]] constexpr size_type max_size() const noexcept
        {
            return Count;
        }

        [[nodiscard]] constexpr bool empty() const noexcept
        {
            return this->m_Size == 0;
        }

        [[nodiscard]] constexpr bool full() const noexcept
        {
            return this->m_Size >= Count;
        }

        void push_back(const value_type& value)
        {
            GX_ASSERT(this->m_Size < Count);

            new (this->ptr_at(this->m_Size)) value_type(value);
            ++this->m_Size;
        }

        void push_back(value_type&& value)
        {
            GX_ASSERT(this->m_Size < Count);

            new (this->ptr_at(this->m_Size)) value_type(std::move(value));
            ++this->m_Size;
        }

        template <typename... TArgs>
        reference emplace_back(TArgs&&... args)
        {
            auto* item = new (this->ptr_at(this->m_Size)) value_type(std::forward<TArgs>(args)...);
            ++this->m_Size;

            GX_ASSERT(item != nullptr);

            return *item;
        }

        void pop_back()
        {
            GX_ASSERT(this->m_Size != 0);

            auto& item = this->ref_at(this->m_Size - 1);
            item.~value_type();
            --this->m_Size;
        }

        constexpr void clear()
        {
            while (this->m_Size != 0)
            {
                this->pop_back();
            }
        }

        [[nodiscard]] constexpr size_type size() const noexcept
        {
            return this->m_Size;
        }

        [[nodiscard]] constexpr size_type capacity() const noexcept
        {
            return Count;
        }

        void resize(size_type size)
        {
            //
            // cap new size of collection to max supported items count.
            //

            size_type new_size = std::min(size, Count);


            //
            // Try to trim vector size first.
            //

            while (new_size < this->m_Size)
            {
                this->pop_back();
            }


            //
            // Try to emplace empty value at end.
            //

            while (new_size > this->m_Size)
            {
                this->emplace_back();
            }
        }

    public:
        [[nodiscard]] pointer data() noexcept
        {
            return this->ptr_at(0);
        }

        [[nodiscard]] const_pointer data() const noexcept
        {
            return this->ptr_at(0);
        }

        [[nodiscard]] reference at(size_type index) noexcept
        {
            return this->ref_at(index);
        }

        [[nodiscard]] const_reference at(size_type index) const noexcept
        {
            return this->ref_at(index);
        }

        [[nodiscard]] reference operator[](size_type index) noexcept
        {
            return this->ref_at(index);
        }

        [[nodiscard]] const_reference operator[](size_type index) const noexcept
        {
            return this->ref_at(index);
        }

        [[nodiscard]] reference front() noexcept
        {
            GX_ASSERT(this->m_Size != 0);

            return this->ref_at(0);
        }

        [[nodiscard]] const_reference front() const noexcept
        {
            GX_ASSERT(this->m_Size != 0);

            return this->ref_at(0);
        }

        [[nodiscard]] reference back() noexcept
        {
            GX_ASSERT(this->m_Size != 0);

            return this->ref_at(this->m_Size - 1);
        }

        [[nodiscard]] const_reference back() const noexcept
        {
            GX_ASSERT(this->m_Size != 0);

            return this->ref_at(this->m_Size - 1);
        }

    public:
        [[nodiscard]] iterator begin() noexcept
        {
            return this->data();
        }

        [[nodiscard]] const_iterator begin() const noexcept
        {
            return this->data();
        }

        [[nodiscard]] const_iterator cbegin() const noexcept
        {
            return this->data();
        }

    public:
        [[nodiscard]] iterator end() noexcept
        {
            return this->data() + this->size();
        }

        [[nodiscard]] const_iterator end() const noexcept
        {
            return this->data() + this->size();
        }

        [[nodiscard]] const_iterator cend() const noexcept
        {
            return this->data() + this->size();
        }

    public:
        [[nodiscard]] reverse_iterator rbegin() noexcept
        {
            return reverse_iterator{ this->end() };
        }

        [[nodiscard]] const_reverse_iterator rbegin() const noexcept
        {
            return const_reverse_iterator{ this->end() };
        }

        [[nodiscard]] const_reverse_iterator crbegin() const noexcept
        {
            return const_reverse_iterator{ this->end() };
        }

    public:
        [[nodiscard]] reverse_iterator rend() noexcept
        {
            return reverse_iterator{ this->begin() };
        }

        [[nodiscard]] const_reverse_iterator rend() const noexcept
        {
            return const_reverse_iterator{ this->begin() };
        }

        [[nodiscard]] const_reverse_iterator crend() const noexcept
        {
            return const_reverse_iterator{ this->begin() };
        }
    };

    template <typename Value, std::size_t Count, std::size_t Alignment = std::alignment_of_v<Value>>
    [[nodiscard]] bool operator==(
        const fixed_vector<Value, Count, Alignment>& lhs,
        const fixed_vector<Value, Count, Alignment>& rhs) noexcept
    {
        return (lhs.size() == rhs.size()) && std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <typename Value, std::size_t Count, std::size_t Alignment = std::alignment_of_v<Value>>
    [[nodiscard]] bool operator!=(
        const fixed_vector<Value, Count, Alignment>& lhs,
        const fixed_vector<Value, Count, Alignment>& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template <typename Value, std::size_t Count, std::size_t Alignment = std::alignment_of_v<Value>>
    [[nodiscard]] bool operator<(
        const fixed_vector<Value, Count, Alignment>& lhs,
        const fixed_vector<Value, Count, Alignment>& rhs) noexcept
    {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <typename Value, std::size_t Count, std::size_t Alignment = std::alignment_of_v<Value>>
    [[nodiscard]] bool operator>(
        const fixed_vector<Value, Count, Alignment>& lhs,
        const fixed_vector<Value, Count, Alignment>& rhs) noexcept
    {
        return (rhs < lhs);
    }

    template <typename Value, std::size_t Count, std::size_t Alignment = std::alignment_of_v<Value>>
    [[nodiscard]] bool operator<=(
        const fixed_vector<Value, Count, Alignment>& lhs,
        const fixed_vector<Value, Count, Alignment>& rhs) noexcept
    {
        return !(rhs < lhs);
    }

    template <typename Value, std::size_t Count, std::size_t Alignment = std::alignment_of_v<Value>>
    [[nodiscard]] bool operator>=(
        const fixed_vector<Value, Count, Alignment>& lhs,
        const fixed_vector<Value, Count, Alignment>& rhs) noexcept
    {
        return !(lhs < rhs);
    }
}
