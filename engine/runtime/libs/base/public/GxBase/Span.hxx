#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Diagnostics.hxx>

namespace notstd
{
    template <typename T>
    class span final
    {
    public:
        using element_type = T;
        using value_type = std::remove_cv_t<T>;

        using difference_type = std::ptrdiff_t;
        using size_type = size_t;
        using index_type = std::ptrdiff_t;

        using pointer = T*;
        using const_pointer = const T*;

        using reference = T&;
        using const_reference = const T&;

        using iterator = T*;
        using const_iterator = const T*;

        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    private:
        pointer m_Data;
        size_type m_Size;

    public:
        constexpr span() noexcept
            : m_Data{}
            , m_Size{}
        {
        }

        constexpr span(pointer data, size_type length) noexcept
            : m_Data{ data }
            , m_Size{ length }
        {
        }

        constexpr span(pointer first, pointer last) noexcept
            : span(first, last - first)
        {
        }

        template <size_type N>
        constexpr span(value_type(&array)[N]) noexcept
            : m_Data{ array }
            , m_Size{ N }
        {
        }

        constexpr span(const span& other) noexcept
            : m_Data{ other.m_Data }
            , m_Size{ other.m_Size }
        {
        }

        template <typename U, typename = typename std::enable_if<std::is_convertible<U(*)[], T(*)[]>::value>::type>
        constexpr span(const span<U>& other) noexcept
            : span(other.data(), other.size())
        {
        }

        template <size_type N>
        constexpr span(std::array<value_type, N>& other) noexcept
            : span(other.data(), N)
        {
        }

        template <size_type N>
        constexpr span(const std::array<value_type, N>& other) noexcept
            : span(other.data(), N)
        {
        }

        template <typename Container>
        constexpr span(Container& other) noexcept
            : span(other.data(), other.size())
        {
        }

        template <typename Container>
        constexpr span(const Container& other) noexcept
            : span(other.data(), other.size())
        {
        }

        constexpr span& operator= (const span& rhs) noexcept
        {
            m_Data = rhs.m_Data;
            m_Size = rhs.m_Size;
            return (*this);
        }

        [[nodiscard]]
        constexpr iterator begin() const noexcept
        {
            return m_Data;
        }

        [[nodiscard]]
        constexpr iterator end() const noexcept
        {
            return m_Data + m_Size;
        }

        [[nodiscard]]
        constexpr const_iterator cbegin() const noexcept
        {
            return m_Data;
        }

        [[nodiscard]]
        constexpr const_iterator cend() const noexcept
        {
            return m_Data + m_Size;
        }

        [[nodiscard]]
        constexpr reverse_iterator rbegin() const noexcept
        {
            return reverse_iterator(end());
        }

        [[nodiscard]]
        constexpr reverse_iterator rend() const noexcept
        {
            return reverse_iterator(begin());
        }

        [[nodiscard]]
        constexpr const_reverse_iterator crbegin() const noexcept
        {
            return const_reverse_iterator(cend());
        }

        [[nodiscard]]
        constexpr const_reverse_iterator crend() const noexcept
        {
            return const_reverse_iterator(cbegin());
        }

        [[nodiscard]]
        constexpr size_type size() const noexcept
        {
            return m_Size;
        }

        [[nodiscard]]
        constexpr size_type length() const noexcept
        {
            return m_Size;
        }

        [[nodiscard]]
        constexpr size_type max_length() const noexcept
        {
            return std::numeric_limits<size_type>::max();
        }

        [[nodiscard]]
        constexpr size_type size_bytes() const noexcept
        {
            return m_Size * sizeof(value_type);
        }

        [[nodiscard]]
        constexpr bool empty() const noexcept
        {
            return m_Size == 0;
        }

        [[nodiscard]]
        constexpr pointer data() const noexcept
        {
            return m_Data;
        }

        [[nodiscard]]
        constexpr const_reference operator[](size_type position) const noexcept
        {
            assert(position < this->length());
            return m_Data[position];
        }

        [[nodiscard]]
        constexpr reference operator[] (size_type position) noexcept
        {
            assert(position < this->length());
            return m_Data[position];
        }

        [[nodiscard]]
        constexpr const_reference front() const noexcept
        {
            assert(!this->empty());
            return m_Data[0];
        }

        [[nodiscard]]
        constexpr reference front() noexcept
        {
            assert(!this->empty());
            return m_Data[0];
        }

        [[nodiscard]]
        constexpr const_reference back() const noexcept
        {
            assert(!this->empty());
            return m_Data[m_Size - 1];
        }

        [[nodiscard]]
        constexpr reference back() noexcept
        {
            assert(!this->empty());
            return m_Data[m_Size - 1];
        }

        constexpr void clear() noexcept
        {
            m_Data = nullptr;
            m_Size = 0;
        }

        constexpr void remove_prefix(size_type count) noexcept
        {
            assert(count <= length());
            m_Data += count;
            m_Size -= count;
        }

        constexpr void remove_suffix(size_type count) noexcept
        {
            assert(count <= length());
            m_Size -= count;
        }

        constexpr void swap(span& other) noexcept
        {
            std::swap(m_Data, other.m_Data);
            std::swap(m_Size, other.m_Size);
        }

        [[nodiscard]]
        constexpr span first(difference_type count) const noexcept
        {
            assert(static_cast<size_type>(count) < m_Size);
            return span{ m_Data, static_cast<size_type>(count) };
        }

        template <difference_type Length>
        [[nodiscard]]
        constexpr span first() const noexcept
        {
            assert(static_cast<size_type>(Length) < m_Size);
            return span{ m_Data, static_cast<size_type>(Length) };
        };

        [[nodiscard]]
        constexpr span last(difference_type count) const noexcept
        {
            assert(static_cast<size_type>(count) < m_Size);
            return span{ m_Data + m_Size - count, static_cast<size_type>(count) };
        }

        template <difference_type Length>
        [[nodiscard]]
        constexpr span last() const noexcept
        {
            assert(static_cast<size_type>(Length) < m_Size);
            return span{ m_Data + m_Size - Length, static_cast<size_type>(Length) };
        }

        template <difference_type Offset, difference_type Length>
        [[nodiscard]]
        constexpr span subspan() const noexcept
        {
            assert(static_cast<size_type>(Offset + Length) <= m_Size);
            return span{ m_Data + Offset, static_cast<size_type>(Length) };
        }

        [[nodiscard]]
        constexpr span subspan(difference_type offset, difference_type count) const noexcept
        {
            assert(static_cast<size_type>(offset + count) <= m_Size);
            return span{ m_Data + offset, static_cast<size_type>(count) };
        };
    };

    template <typename T>
    [[nodiscard]]
    constexpr span<const std::byte> as_bytes(span<T> other) noexcept
    {
        return span<const std::byte>{ reinterpret_cast<const std::byte*>(other.data()), other.size_bytes() };
    };

    template <typename T, typename = std::enable_if_t<!std::is_const<T>::value>>
    [[nodiscard]]
    constexpr span<std::byte> as_writable_bytes(span<T> other) noexcept
    {
        return span<std::byte>{ reinterpret_cast<std::byte*>(other.data()), other.size_bytes() };
    };
}
