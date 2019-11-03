#pragma once
#include <Graphyte/Base.module.hxx>

#define FLAT_CONTAINERS_KEY_NOT_FOUND() std::abort()

// -------------------------------------------------------------------------------------------------
//
// Adapted from: https://github.com/BlackMATov/flat.hpp
//
// Synchronized on: 2019-05-16 17:44
//
// -------------------------------------------------------------------------------------------------

/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/flat.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

namespace notstd
{
    template < typename Key
             , typename Compare = std::less<Key>
             , typename Container = std::vector<Key> >
    class flat_set : private Compare {
        using base_type = Compare;
    public:
        using key_type = Key;
        using value_type = Key;

        using size_type = typename Container::size_type;
        using difference_type = typename Container::difference_type;

        using key_compare = Compare;
        using value_compare = Compare;
        using container_type = Container;

        using reference = typename Container::reference;
        using const_reference = typename Container::const_reference;
        using pointer = typename Container::pointer;
        using const_pointer = typename Container::const_pointer;

        using iterator = typename Container::const_iterator;
        using const_iterator = typename Container::const_iterator;
        using reverse_iterator = typename Container::const_reverse_iterator;
        using const_reverse_iterator = typename Container::const_reverse_iterator;
    public:
        flat_set()
            noexcept(std::is_nothrow_default_constructible_v<base_type>
                && std::is_nothrow_default_constructible_v<container_type>) {}

        explicit flat_set(const Compare& c)
        : base_type(c) {}

        template < typename Allocator >
        explicit flat_set(const Allocator& a)
        : data_(a) {}

        template < typename Allocator >
        flat_set(const Compare& c, const Allocator& a)
        : base_type(c)
        , data_(a) {}

        template < typename InputIter >
        flat_set(InputIter first, InputIter last) {
            insert(first, last);
        }

        template < typename InputIter >
        flat_set(InputIter first, InputIter last, const Compare& c)
        : base_type(c) {
            insert(first, last);
        }

        template < typename InputIter, typename Allocator >
        flat_set(InputIter first, InputIter last, const Allocator& a)
        : data_(a) {
            insert(first, last);
        }

        template < typename InputIter, typename Allocator >
        flat_set(InputIter first, InputIter last, const Compare& c, const Allocator& a)
        : base_type(c)
        , data_(a) {
            insert(first, last);
        }

        flat_set(std::initializer_list<value_type> ilist) {
            insert(ilist);
        }

        flat_set(std::initializer_list<value_type> ilist, const Compare& c)
        : base_type(c) {
            insert(ilist);
        }

        template < typename Allocator >
        flat_set(std::initializer_list<value_type> ilist, const Allocator& a)
        : data_(a) {
            insert(ilist);
        }

        template < typename Allocator >
        flat_set(std::initializer_list<value_type> ilist, const Compare& c, const Allocator& a)
        : base_type(c)
        , data_(a) {
            insert(ilist);
        }

        template < typename Allocator >
        flat_set(flat_set&& other, const Allocator& a)
        : base_type(static_cast<base_type&&>(other))
        , data_(std::move(other.data_), a) {}

        template < typename Allocator >
        flat_set(const flat_set& other, const Allocator& a)
        : base_type(static_cast<const base_type&>(other))
        , data_(other.data_, a) {}

        flat_set(flat_set&& other) = default;
        flat_set(const flat_set& other) = default;

        flat_set& operator=(flat_set&& other) = default;
        flat_set& operator=(const flat_set& other) = default;

        flat_set& operator=(std::initializer_list<value_type> ilist) {
            flat_set(ilist).swap(*this);
            return *this;
        }

        iterator begin()
        noexcept(noexcept(std::declval<container_type&>().begin())) {
            return data_.begin();
        }

        const_iterator begin() const
        noexcept(noexcept(std::declval<const container_type&>().begin())) {
            return data_.begin();
        }

        const_iterator cbegin() const
        noexcept(noexcept(std::declval<const container_type&>().cbegin())) {
            return data_.cbegin();
        }

        iterator end()
        noexcept(noexcept(std::declval<container_type&>().end())) {
            return data_.end();
        }

        const_iterator end() const
        noexcept(noexcept(std::declval<const container_type&>().end())) {
            return data_.end();
        }

        const_iterator cend() const
        noexcept(noexcept(std::declval<const container_type&>().cend())) {
            return data_.cend();
        }

        reverse_iterator rbegin()
        noexcept(noexcept(std::declval<container_type&>().rbegin())) {
            return data_.rbegin();
        }

        const_reverse_iterator rbegin() const
        noexcept(noexcept(std::declval<const container_type&>().rbegin())) {
            return data_.rbegin();
        }

        const_reverse_iterator crbegin() const
        noexcept(noexcept(std::declval<const container_type&>().crbegin())) {
            return data_.crbegin();
        }

        reverse_iterator rend()
        noexcept(noexcept(std::declval<container_type&>().rend())) {
            return data_.rend();
        }

        const_reverse_iterator rend() const
        noexcept(noexcept(std::declval<const container_type&>().rend())) {
            return data_.rend();
        }

        const_reverse_iterator crend() const
        noexcept(noexcept(std::declval<const container_type&>().crend())) {
            return data_.crend();
        }

        bool empty() const
        noexcept(noexcept(std::declval<const container_type&>().empty())) {
            return data_.empty();
        }

        size_type size() const
        noexcept(noexcept(std::declval<const container_type&>().size())) {
            return data_.size();
        }

        size_type max_size() const
        noexcept(noexcept(std::declval<const container_type&>().max_size())) {
            return data_.max_size();
        }

        size_type capacity() const
        noexcept(noexcept(std::declval<const container_type&>().capacity())) {
            return data_.capacity();
        }

        void reserve(size_type ncapacity) {
            data_.reserve(ncapacity);
        }

        void shrink_to_fit() {
            data_.shrink_to_fit();
        }

        std::pair<iterator, bool> insert(value_type&& value) {
            const iterator iter = lower_bound(value);
            return iter == end() || this->operator()(value, *iter)
                ? std::make_pair(data_.insert(iter, std::move(value)), true)
                : std::make_pair(iter, false);
        }

        std::pair<iterator, bool> insert(const value_type& value) {
            const iterator iter = lower_bound(value);
            return iter == end() || this->operator()(value, *iter)
                ? std::make_pair(data_.insert(iter, value), true)
                : std::make_pair(iter, false);
        }

        iterator insert(const_iterator hint, value_type&& value) {
            return (hint == begin() || this->operator()(*(hint - 1), value))
                && (hint == end() || this->operator()(value, *hint))
                ? data_.insert(hint, std::move(value))
                : insert(std::move(value)).first;
        }

        iterator insert(const_iterator hint, const value_type& value) {
            return (hint == begin() || this->operator()(*(hint - 1), value))
                && (hint == end() || this->operator()(value, *hint))
                ? data_.insert(hint, value)
                : insert(value).first;
        }

        template < typename InputIter >
        void insert(InputIter first, InputIter last) {
            while ( first != last ) {
                insert(*first++);
            }
        }

        void insert(std::initializer_list<value_type> ilist) {
            insert(ilist.begin(), ilist.end());
        }

        template < typename... Args >
        std::pair<iterator, bool> emplace(Args&&... args) {
            return insert(value_type(std::forward<Args>(args)...));
        }

        template < typename... Args >
        iterator emplace_hint(const_iterator hint, Args&&... args) {
            return insert(hint, value_type(std::forward<Args>(args)...));
        }

        void clear()
        noexcept(noexcept(std::declval<container_type&>().clear())) {
            data_.clear();
        }

        iterator erase(const_iterator iter) {
            return data_.erase(iter);
        }

        iterator erase(const_iterator first, const_iterator last) {
            return data_.erase(first, last);
        }

        size_type erase(const key_type& key) {
            const iterator iter = find(key);
            return iter != end()
                ? (erase(iter), 1)
                : 0;
        }

        void swap(flat_set& other)
            noexcept(std::is_nothrow_swappable_v<base_type>
                && std::is_nothrow_swappable_v<container_type>)
        {
            using std::swap;
            swap(
                static_cast<base_type&>(*this),
                static_cast<base_type&>(other));
            swap(data_, other.data_);
        }

        size_type count(const key_type& key) const {
            const const_iterator iter = find(key);
            return iter != end() ? 1 : 0;
        }

        iterator find(const key_type& key) {
            const iterator iter = lower_bound(key);
            return iter != end() && !this->operator()(key, *iter)
                ? iter
                : end();
        }

        const_iterator find(const key_type& key) const {
            const const_iterator iter = lower_bound(key);
            return iter != end() && !this->operator()(key, *iter)
                ? iter
                : end();
        }

        std::pair<iterator, iterator> equal_range(const key_type& key) {
            return std::equal_range(begin(), end(), key, key_comp());
        }

        std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
            return std::equal_range(begin(), end(), key, key_comp());
        }

        iterator lower_bound(const key_type& key) {
            return std::lower_bound(begin(), end(), key, key_comp());
        }

        const_iterator lower_bound(const key_type& key) const {
            return std::lower_bound(begin(), end(), key, key_comp());
        }

        iterator upper_bound(const key_type& key) {
            return std::upper_bound(begin(), end(), key, key_comp());
        }

        const_iterator upper_bound(const key_type& key) const {
            return std::upper_bound(begin(), end(), key, key_comp());
        }

        key_compare key_comp() const {
            return *this;
        }

        value_compare value_comp() const {
            return value_compare(key_comp());
        }
    private:
        container_type data_;
    };
}

namespace notstd
{
    template < typename Key
             , typename Compare
             , typename Container >
    void swap(
        flat_set<Key, Compare, Container>& l,
        flat_set<Key, Compare, Container>& r)
        noexcept(noexcept(l.swap(r)))
    {
        l.swap(r);
    }

    template < typename Key
             , typename Compare
             , typename Container >
    bool operator==(
        const flat_set<Key, Compare, Container>& l,
        const flat_set<Key, Compare, Container>& r)
    {
        return l.size() == r.size()
            && std::equal(l.begin(), l.end(), r.begin());
    }

    template < typename Key
             , typename Compare
             , typename Container >
    bool operator!=(
        const flat_set<Key, Compare, Container>& l,
        const flat_set<Key, Compare, Container>& r)
    {
        return !(l == r);
    }

    template < typename Key
             , typename Compare
             , typename Container >
    bool operator<(
        const flat_set<Key, Compare, Container>& l,
        const flat_set<Key, Compare, Container>& r)
    {
        return std::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
    }

    template < typename Key
             , typename Compare
             , typename Container >
    bool operator>(
        const flat_set<Key, Compare, Container>& l,
        const flat_set<Key, Compare, Container>& r)
    {
        return r < l;
    }

    template < typename Key
             , typename Compare
             , typename Container >
    bool operator<=(
        const flat_set<Key, Compare, Container>& l,
        const flat_set<Key, Compare, Container>& r)
    {
        return !(r < l);
    }

    template < typename Key
             , typename Compare
             , typename Container >
    bool operator>=(
        const flat_set<Key, Compare, Container>& l,
        const flat_set<Key, Compare, Container>& r)
    {
        return !(l < r);
    }
}

/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/flat.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

namespace notstd
{
    namespace detail
    {
        template < typename Value, typename Compare >
        class flat_map_compare : public Compare {
        public:
            flat_map_compare() = default;

            flat_map_compare(const Compare& compare)
            : Compare(compare) {}

            bool operator()(
                const typename Value::first_type& l,
                const typename Value::first_type& r) const
            {
                return Compare::operator()(l, r);
            }

            bool operator()(
                const typename Value::first_type& l,
                const Value& r) const
            {
                return Compare::operator()(l, r.first);
            }

            bool operator()(
                const Value& l,
                const typename Value::first_type& r) const
            {
                return Compare::operator()(l.first, r);
            }

            bool operator()(const Value& l, const Value& r) const {
                return Compare::operator()(l.first, r.first);
            }
        };
    }

    template < typename Key
             , typename Value
             , typename Compare = std::less<Key>
             , typename Container = std::vector<std::pair<Key, Value>> >
    class flat_map
        : private detail::flat_map_compare<
            typename Container::value_type,
            Compare>
    {
        using base_type = detail::flat_map_compare<
            typename Container::value_type,
            Compare>;
    public:
        using key_type = Key;
        using mapped_type = Value;
        using value_type = typename Container::value_type;

        using size_type = typename Container::size_type;
        using difference_type = typename Container::difference_type;

        using key_compare = Compare;
        using container_type = Container;

        using reference = typename Container::reference;
        using const_reference = typename Container::const_reference;
        using pointer = typename Container::pointer;
        using const_pointer = typename Container::const_pointer;

        using iterator = typename Container::iterator;
        using const_iterator = typename Container::const_iterator;
        using reverse_iterator = typename Container::reverse_iterator;
        using const_reverse_iterator = typename Container::const_reverse_iterator;

        class value_compare : private key_compare {
        public:
            bool operator()(const value_type& l, const value_type& r) const {
                return key_compare::operator()(l.first, r.first);
            }
        protected:
            friend class flat_map;
            explicit value_compare(key_compare compare)
            : key_compare(std::move(compare)) {}
        };
    public:
        flat_map()
            noexcept(std::is_nothrow_default_constructible_v<base_type>
                && std::is_nothrow_default_constructible_v<container_type>) {}

        explicit flat_map(const Compare& c)
        : base_type(c) {}

        template < typename Allocator >
        explicit flat_map(const Allocator& a)
        : data_(a) {}

        template < typename Allocator >
        flat_map(const Compare& c, const Allocator& a)
        : base_type(c)
        , data_(a) {}

        template < typename InputIter >
        flat_map(InputIter first, InputIter last) {
            insert(first, last);
        }

        template < typename InputIter >
        flat_map(InputIter first, InputIter last, const Compare& c)
        : base_type(c) {
            insert(first, last);
        }

        template < typename InputIter, typename Allocator >
        flat_map(InputIter first, InputIter last, const Allocator& a)
        : data_(a) {
            insert(first, last);
        }

        template < typename InputIter , typename Allocator >
        flat_map(InputIter first, InputIter last, const Compare& c, const Allocator& a)
        : base_type(c)
        , data_(a) {
            insert(first, last);
        }

        flat_map(std::initializer_list<value_type> ilist) {
            insert(ilist);
        }

        flat_map(std::initializer_list<value_type> ilist, const Compare& c)
        : base_type(c) {
            insert(ilist);
        }

        template < typename Allocator >
        flat_map(std::initializer_list<value_type> ilist, const Allocator& a)
        : data_(a) {
            insert(ilist);
        }

        template < typename Allocator >
        flat_map(std::initializer_list<value_type> ilist, const Compare& c, const Allocator& a)
        : base_type(c)
        , data_(a) {
            insert(ilist);
        }

        template < typename Allocator >
        flat_map(flat_map&& other, const Allocator& a)
        : base_type(static_cast<base_type&&>(other))
        , data_(std::move(other.data_), a) {}

        template < typename Allocator >
        flat_map(const flat_map& other, const Allocator& a)
        : base_type(static_cast<const base_type&>(other))
        , data_(other.data_, a) {}

        flat_map(flat_map&& other) = default;
        flat_map(const flat_map& other) = default;

        flat_map& operator=(flat_map&& other) = default;
        flat_map& operator=(const flat_map& other) = default;

        flat_map& operator=(std::initializer_list<value_type> ilist) {
            flat_map(ilist).swap(*this);
            return *this;
        }

        iterator begin()
        noexcept(noexcept(std::declval<container_type&>().begin())) {
            return data_.begin();
        }

        const_iterator begin() const
        noexcept(noexcept(std::declval<const container_type&>().begin())) {
            return data_.begin();
        }

        const_iterator cbegin() const
        noexcept(noexcept(std::declval<const container_type&>().cbegin())) {
            return data_.cbegin();
        }

        iterator end()
        noexcept(noexcept(std::declval<container_type&>().end())) {
            return data_.end();
        }

        const_iterator end() const
        noexcept(noexcept(std::declval<const container_type&>().end())) {
            return data_.end();
        }

        const_iterator cend() const
        noexcept(noexcept(std::declval<const container_type&>().cend())) {
            return data_.cend();
        }

        reverse_iterator rbegin()
        noexcept(noexcept(std::declval<container_type&>().rbegin())) {
            return data_.rbegin();
        }

        const_reverse_iterator rbegin() const
        noexcept(noexcept(std::declval<const container_type&>().rbegin())) {
            return data_.rbegin();
        }

        const_reverse_iterator crbegin() const
        noexcept(noexcept(std::declval<const container_type&>().crbegin())) {
            return data_.crbegin();
        }

        reverse_iterator rend()
        noexcept(noexcept(std::declval<container_type&>().rend())) {
            return data_.rend();
        }

        const_reverse_iterator rend() const
        noexcept(noexcept(std::declval<const container_type&>().rend())) {
            return data_.rend();
        }

        const_reverse_iterator crend() const
        noexcept(noexcept(std::declval<const container_type&>().crend())) {
            return data_.crend();
        }

        bool empty() const
        noexcept(noexcept(std::declval<const container_type&>().empty())) {
            return data_.empty();
        }

        size_type size() const
        noexcept(noexcept(std::declval<const container_type&>().size())) {
            return data_.size();
        }

        size_type max_size() const
        noexcept(noexcept(std::declval<const container_type&>().max_size())) {
            return data_.max_size();
        }

        size_type capacity() const
        noexcept(noexcept(std::declval<const container_type&>().capacity())) {
            return data_.capacity();
        }

        void reserve(size_type ncapacity) {
            data_.reserve(ncapacity);
        }

        void shrink_to_fit() {
            data_.shrink_to_fit();
        }

        mapped_type& operator[](key_type&& key) {
            const iterator iter = find(key);
            return iter != end()
                ? iter->second
                : emplace(std::move(key), mapped_type()).first->second;
        }

        mapped_type& operator[](const key_type& key) {
            const iterator iter = find(key);
            return iter != end()
                ? iter->second
                : emplace(key, mapped_type()).first->second;
        }

        mapped_type& at(const key_type& key) {
            const iterator iter = find(key);
            if ( iter != end() ) {
                return iter->second;
            }

            FLAT_CONTAINERS_KEY_NOT_FOUND();
        }

        const mapped_type& at(const key_type& key) const {
            const const_iterator iter = find(key);
            if ( iter != end() ) {
                return iter->second;
            }

            FLAT_CONTAINERS_KEY_NOT_FOUND();
        }

        std::pair<iterator, bool> insert(value_type&& value) {
            const iterator iter = lower_bound(value.first);
            return iter == end() || this->operator()(value, *iter)
                ? std::make_pair(data_.insert(iter, std::move(value)), true)
                : std::make_pair(iter, false);
        }

        std::pair<iterator, bool> insert(const value_type& value) {
            const iterator iter = lower_bound(value.first);
            return iter == end() || this->operator()(value, *iter)
                ? std::make_pair(data_.insert(iter, value), true)
                : std::make_pair(iter, false);
        }

        iterator insert(const_iterator hint, value_type&& value) {
            return (hint == begin() || this->operator()(*(hint - 1), value))
                && (hint == end() || this->operator()(value, *hint))
                ? data_.insert(hint, std::move(value))
                : insert(std::move(value)).first;
        }

        iterator insert(const_iterator hint, const value_type& value) {
            return (hint == begin() || this->operator()(*(hint - 1), value))
                && (hint == end() || this->operator()(value, *hint))
                ? data_.insert(hint, value)
                : insert(value).first;
        }

        template < typename InputIter >
        void insert(InputIter first, InputIter last) {
            while ( first != last ) {
                insert(*first++);
            }
        }

        void insert(std::initializer_list<value_type> ilist) {
            insert(ilist.begin(), ilist.end());
        }

        template < typename... Args >
        std::pair<iterator, bool> emplace(Args&&... args) {
            return insert(value_type(std::forward<Args>(args)...));
        }

        template < typename... Args >
        iterator emplace_hint(const_iterator hint, Args&&... args) {
            return insert(hint, value_type(std::forward<Args>(args)...));
        }

        void clear()
        noexcept(noexcept(std::declval<container_type&>().clear())) {
            data_.clear();
        }

        iterator erase(const_iterator iter) {
            return data_.erase(iter);
        }

        iterator erase(const_iterator first, const_iterator last) {
            return data_.erase(first, last);
        }

        size_type erase(const key_type& key) {
            const iterator iter = find(key);
            return iter != end()
                ? (erase(iter), 1)
                : 0;
        }

        void swap(flat_map& other)
            noexcept(std::is_nothrow_swappable_v<base_type>
                && std::is_nothrow_swappable_v<container_type>)
        {
            using std::swap;
            swap(
                static_cast<base_type&>(*this),
                static_cast<base_type&>(other));
            swap(data_, other.data_);
        }

        size_type count(const key_type& key) const {
            const const_iterator iter = find(key);
            return iter != end() ? 1 : 0;
        }

        iterator find(const key_type& key) {
            const iterator iter = lower_bound(key);
            return iter != end() && !this->operator()(key, iter->first)
                ? iter
                : end();
        }

        const_iterator find(const key_type& key) const {
            const const_iterator iter = lower_bound(key);
            return iter != end() && !this->operator()(key, iter->first)
                ? iter
                : end();
        }

        std::pair<iterator, iterator> equal_range(const key_type& key) {
            const base_type& comp = *this;
            return std::equal_range(begin(), end(), key, comp);
        }

        std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
            const base_type& comp = *this;
            return std::equal_range(begin(), end(), key, comp);
        }

        iterator lower_bound(const key_type& key) {
            const base_type& comp = *this;
            return std::lower_bound(begin(), end(), key, comp);
        }

        const_iterator lower_bound(const key_type& key) const {
            const base_type& comp = *this;
            return std::lower_bound(begin(), end(), key, comp);
        }

        iterator upper_bound(const key_type& key) {
            const base_type& comp = *this;
            return std::upper_bound(begin(), end(), key, comp);
        }

        const_iterator upper_bound(const key_type& key) const {
            const base_type& comp = *this;
            return std::upper_bound(begin(), end(), key, comp);
        }

        key_compare key_comp() const {
            return *this;
        }

        value_compare value_comp() const {
            return value_compare(key_comp());
        }
    private:
        container_type data_;
    };
}

namespace notstd
{
    template < typename Key
             , typename Value
             , typename Compare
             , typename Container >
    void swap(
        flat_map<Key, Value, Compare, Container>& l,
        flat_map<Key, Value, Compare, Container>& r)
        noexcept(noexcept(l.swap(r)))
    {
        l.swap(r);
    }

    template < typename Key
             , typename Value
             , typename Compare
             , typename Container >
    bool operator==(
        const flat_map<Key, Value, Compare, Container>& l,
        const flat_map<Key, Value, Compare, Container>& r)
    {
        return l.size() == r.size()
            && std::equal(l.begin(), l.end(), r.begin());
    }

    template < typename Key
             , typename Value
             , typename Compare
             , typename Container >
    bool operator!=(
        const flat_map<Key, Value, Compare, Container>& l,
        const flat_map<Key, Value, Compare, Container>& r)
    {
        return !(l == r);
    }

    template < typename Key
             , typename Value
             , typename Compare
             , typename Container >
    bool operator<(
        const flat_map<Key, Value, Compare, Container>& l,
        const flat_map<Key, Value, Compare, Container>& r)
    {
        return std::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
    }

    template < typename Key
             , typename Value
             , typename Compare
             , typename Container >
    bool operator>(
        const flat_map<Key, Value, Compare, Container>& l,
        const flat_map<Key, Value, Compare, Container>& r)
    {
        return r < l;
    }

    template < typename Key
             , typename Value
             , typename Compare
             , typename Container >
    bool operator<=(
        const flat_map<Key, Value, Compare, Container>& l,
        const flat_map<Key, Value, Compare, Container>& r)
    {
        return !(r < l);
    }

    template < typename Key
             , typename Value
             , typename Compare
             , typename Container >
    bool operator>=(
        const flat_map<Key, Value, Compare, Container>& l,
        const flat_map<Key, Value, Compare, Container>& r)
    {
        return !(l < r);
    }
}

/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/flat.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

namespace notstd
{
    template < typename Key
             , typename Compare = std::less<Key>
             , typename Container = std::vector<Key> >
    class flat_multiset : private Compare {
        using base_type = Compare;
    public:
        using key_type = Key;
        using value_type = Key;

        using size_type = typename Container::size_type;
        using difference_type = typename Container::difference_type;

        using key_compare = Compare;
        using value_compare = Compare;
        using container_type = Container;

        using reference = typename Container::reference;
        using const_reference = typename Container::const_reference;
        using pointer = typename Container::pointer;
        using const_pointer = typename Container::const_pointer;

        using iterator = typename Container::const_iterator;
        using const_iterator = typename Container::const_iterator;
        using reverse_iterator = typename Container::const_reverse_iterator;
        using const_reverse_iterator = typename Container::const_reverse_iterator;
    public:
        flat_multiset()
            noexcept(std::is_nothrow_default_constructible_v<base_type>
                && std::is_nothrow_default_constructible_v<container_type>) {}

        explicit flat_multiset(const Compare& c)
        : base_type(c) {}

        template < typename Allocator >
        explicit flat_multiset(const Allocator& a)
        : data_(a) {}

        template < typename Allocator >
        flat_multiset(const Compare& c, const Allocator& a)
        : base_type(c)
        , data_(a) {}

        template < typename InputIter >
        flat_multiset(InputIter first, InputIter last) {
            insert(first, last);
        }

        template < typename InputIter >
        flat_multiset(InputIter first, InputIter last, const Compare& c)
        : base_type(c) {
            insert(first, last);
        }

        template < typename InputIter, typename Allocator >
        flat_multiset(InputIter first, InputIter last, const Allocator& a)
        : data_(a) {
            insert(first, last);
        }

        template < typename InputIter, typename Allocator >
        flat_multiset(InputIter first, InputIter last, const Compare& c, const Allocator& a)
        : base_type(c)
        , data_(a) {
            insert(first, last);
        }

        flat_multiset(std::initializer_list<value_type> ilist) {
            insert(ilist);
        }

        flat_multiset(std::initializer_list<value_type> ilist, const Compare& c)
        : base_type(c) {
            insert(ilist);
        }

        template < typename Allocator >
        flat_multiset(std::initializer_list<value_type> ilist, const Allocator& a)
        : data_(a) {
            insert(ilist);
        }

        template < typename Allocator >
        flat_multiset(std::initializer_list<value_type> ilist, const Compare& c, const Allocator& a)
        : base_type(c)
        , data_(a) {
            insert(ilist);
        }

        template < typename Allocator >
        flat_multiset(flat_multiset&& other, const Allocator& a)
        : base_type(static_cast<base_type&&>(other))
        , data_(std::move(other.data_), a) {}

        template < typename Allocator >
        flat_multiset(const flat_multiset& other, const Allocator& a)
        : base_type(static_cast<const base_type&>(other))
        , data_(other.data_, a) {}

        flat_multiset(flat_multiset&& other) = default;
        flat_multiset(const flat_multiset& other) = default;

        flat_multiset& operator=(flat_multiset&& other) = default;
        flat_multiset& operator=(const flat_multiset& other) = default;

        flat_multiset& operator=(std::initializer_list<value_type> ilist) {
            flat_multiset(ilist).swap(*this);
            return *this;
        }

        iterator begin()
        noexcept(noexcept(std::declval<container_type&>().begin())) {
            return data_.begin();
        }

        const_iterator begin() const
        noexcept(noexcept(std::declval<const container_type&>().begin())) {
            return data_.begin();
        }

        const_iterator cbegin() const
        noexcept(noexcept(std::declval<const container_type&>().cbegin())) {
            return data_.cbegin();
        }

        iterator end()
        noexcept(noexcept(std::declval<container_type&>().end())) {
            return data_.end();
        }

        const_iterator end() const
        noexcept(noexcept(std::declval<const container_type&>().end())) {
            return data_.end();
        }

        const_iterator cend() const
        noexcept(noexcept(std::declval<const container_type&>().cend())) {
            return data_.cend();
        }

        reverse_iterator rbegin()
        noexcept(noexcept(std::declval<container_type&>().rbegin())) {
            return data_.rbegin();
        }

        const_reverse_iterator rbegin() const
        noexcept(noexcept(std::declval<const container_type&>().rbegin())) {
            return data_.rbegin();
        }

        const_reverse_iterator crbegin() const
        noexcept(noexcept(std::declval<const container_type&>().crbegin())) {
            return data_.crbegin();
        }

        reverse_iterator rend()
        noexcept(noexcept(std::declval<container_type&>().rend())) {
            return data_.rend();
        }

        const_reverse_iterator rend() const
        noexcept(noexcept(std::declval<const container_type&>().rend())) {
            return data_.rend();
        }

        const_reverse_iterator crend() const
        noexcept(noexcept(std::declval<const container_type&>().crend())) {
            return data_.crend();
        }

        bool empty() const
        noexcept(noexcept(std::declval<const container_type&>().empty())) {
            return data_.empty();
        }

        size_type size() const
        noexcept(noexcept(std::declval<const container_type&>().size())) {
            return data_.size();
        }

        size_type max_size() const
        noexcept(noexcept(std::declval<const container_type&>().max_size())) {
            return data_.max_size();
        }

        size_type capacity() const
        noexcept(noexcept(std::declval<const container_type&>().capacity())) {
            return data_.capacity();
        }

        void reserve(size_type ncapacity) {
            data_.reserve(ncapacity);
        }

        void shrink_to_fit() {
            data_.shrink_to_fit();
        }

        iterator insert(value_type&& value) {
            const iterator iter = upper_bound(value);
            return data_.insert(iter, std::move(value));
        }

        iterator insert(const value_type& value) {
            const iterator iter = upper_bound(value);
            return data_.insert(iter, value);
        }

        iterator insert(const_iterator hint, value_type&& value) {
            return (hint == begin() || !this->operator()(value, *(hint - 1)))
                && (hint == end() || !this->operator()(*hint, value))
                ? data_.insert(hint, std::move(value))
                : insert(std::move(value));
        }

        iterator insert(const_iterator hint, const value_type& value) {
            return (hint == begin() || !this->operator()(value, *(hint - 1)))
                && (hint == end() || !this->operator()(*hint, value))
                ? data_.insert(hint, value)
                : insert(value);
        }

        template < typename InputIter >
        void insert(InputIter first, InputIter last) {
            while ( first != last ) {
                insert(*first++);
            }
        }

        void insert(std::initializer_list<value_type> ilist) {
            insert(ilist.begin(), ilist.end());
        }

        template < typename... Args >
        iterator emplace(Args&&... args) {
            return insert(value_type(std::forward<Args>(args)...));
        }

        template < typename... Args >
        iterator emplace_hint(const_iterator hint, Args&&... args) {
            return insert(hint, value_type(std::forward<Args>(args)...));
        }

        void clear()
        noexcept(noexcept(std::declval<container_type&>().clear())) {
            data_.clear();
        }

        iterator erase(const_iterator iter) {
            return data_.erase(iter);
        }

        iterator erase(const_iterator first, const_iterator last) {
            return data_.erase(first, last);
        }

        size_type erase(const key_type& key) {
            const auto p = equal_range(key);
            size_type r = std::distance(p.first, p.second);
            erase(p.first, p.second);
            return r;
        }

        void swap(flat_multiset& other)
            noexcept(std::is_nothrow_swappable_v<base_type>
                && std::is_nothrow_swappable_v<container_type>)
        {
            using std::swap;
            swap(
                static_cast<base_type&>(*this),
                static_cast<base_type&>(other));
            swap(data_, other.data_);
        }

        size_type count(const key_type& key) const {
            const auto p = equal_range(key);
            return std::distance(p.first, p.second);
        }

        iterator find(const key_type& key) {
            const iterator iter = lower_bound(key);
            return iter != end() && !this->operator()(key, *iter)
                ? iter
                : end();
        }

        const_iterator find(const key_type& key) const {
            const const_iterator iter = lower_bound(key);
            return iter != end() && !this->operator()(key, *iter)
                ? iter
                : end();
        }

        std::pair<iterator, iterator> equal_range(const key_type& key) {
            return std::equal_range(begin(), end(), key, key_comp());
        }

        std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
            return std::equal_range(begin(), end(), key, key_comp());
        }

        iterator lower_bound(const key_type& key) {
            return std::lower_bound(begin(), end(), key, key_comp());
        }

        const_iterator lower_bound(const key_type& key) const {
            return std::lower_bound(begin(), end(), key, key_comp());
        }

        iterator upper_bound(const key_type& key) {
            return std::upper_bound(begin(), end(), key, key_comp());
        }

        const_iterator upper_bound(const key_type& key) const {
            return std::upper_bound(begin(), end(), key, key_comp());
        }

        key_compare key_comp() const {
            return *this;
        }

        value_compare value_comp() const {
            return value_compare(key_comp());
        }
    private:
        container_type data_;
    };
}

namespace notstd
{
    template < typename Key
             , typename Compare
             , typename Container >
    void swap(
        flat_multiset<Key, Compare, Container>& l,
        flat_multiset<Key, Compare, Container>& r)
        noexcept(noexcept(l.swap(r)))
    {
        l.swap(r);
    }

    template < typename Key
             , typename Compare
             , typename Container >
    bool operator==(
        const flat_multiset<Key, Compare, Container>& l,
        const flat_multiset<Key, Compare, Container>& r)
    {
        return l.size() == r.size()
            && std::equal(l.begin(), l.end(), r.begin());
    }

    template < typename Key
             , typename Compare
             , typename Container >
    bool operator!=(
        const flat_multiset<Key, Compare, Container>& l,
        const flat_multiset<Key, Compare, Container>& r)
    {
        return !(l == r);
    }

    template < typename Key
             , typename Compare
             , typename Container >
    bool operator<(
        const flat_multiset<Key, Compare, Container>& l,
        const flat_multiset<Key, Compare, Container>& r)
    {
        return std::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
    }

    template < typename Key
             , typename Compare
             , typename Container >
    bool operator>(
        const flat_multiset<Key, Compare, Container>& l,
        const flat_multiset<Key, Compare, Container>& r)
    {
        return r < l;
    }

    template < typename Key
             , typename Compare
             , typename Container >
    bool operator<=(
        const flat_multiset<Key, Compare, Container>& l,
        const flat_multiset<Key, Compare, Container>& r)
    {
        return !(r < l);
    }

    template < typename Key
             , typename Compare
             , typename Container >
    bool operator>=(
        const flat_multiset<Key, Compare, Container>& l,
        const flat_multiset<Key, Compare, Container>& r)
    {
        return !(l < r);
    }
}

/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/flat.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

namespace notstd
{
    namespace detail
    {
        template < typename Value, typename Compare >
        class flat_multimap_compare : public Compare {
        public:
            flat_multimap_compare() = default;

            flat_multimap_compare(const Compare& compare)
            : Compare(compare) {}

            bool operator()(
                const typename Value::first_type& l,
                const typename Value::first_type& r) const
            {
                return Compare::operator()(l, r);
            }

            bool operator()(
                const typename Value::first_type& l,
                const Value& r) const
            {
                return Compare::operator()(l, r.first);
            }

            bool operator()(
                const Value& l,
                const typename Value::first_type& r) const
            {
                return Compare::operator()(l.first, r);
            }

            bool operator()(const Value& l, const Value& r) const {
                return Compare::operator()(l.first, r.first);
            }
        };
    }

    template < typename Key
             , typename Value
             , typename Compare = std::less<Key>
             , typename Container = std::vector<std::pair<Key, Value>> >
    class flat_multimap
        : private detail::flat_multimap_compare<
            typename Container::value_type,
            Compare>
    {
        using base_type = detail::flat_multimap_compare<
            typename Container::value_type,
            Compare>;
    public:
        using key_type = Key;
        using mapped_type = Value;
        using value_type = typename Container::value_type;

        using size_type = typename Container::size_type;
        using difference_type = typename Container::difference_type;

        using key_compare = Compare;
        using container_type = Container;

        using reference = typename Container::reference;
        using const_reference = typename Container::const_reference;
        using pointer = typename Container::pointer;
        using const_pointer = typename Container::const_pointer;

        using iterator = typename Container::iterator;
        using const_iterator = typename Container::const_iterator;
        using reverse_iterator = typename Container::reverse_iterator;
        using const_reverse_iterator = typename Container::const_reverse_iterator;

        class value_compare : private key_compare {
        public:
            bool operator()(const value_type& l, const value_type& r) const {
                return key_compare::operator()(l.first, r.first);
            }
        protected:
            friend class flat_multimap;
            explicit value_compare(key_compare compare)
            : key_compare(std::move(compare)) {}
        };
    public:
        flat_multimap()
            noexcept(std::is_nothrow_default_constructible_v<base_type>
                && std::is_nothrow_default_constructible_v<container_type>) {}

        explicit flat_multimap(const Compare& c)
        : base_type(c) {}

        template < typename Allocator >
        explicit flat_multimap(const Allocator& a)
        : data_(a) {}

        template < typename Allocator >
        flat_multimap(const Compare& c, const Allocator& a)
        : base_type(c)
        , data_(a) {}

        template < typename InputIter >
        flat_multimap(InputIter first, InputIter last) {
            insert(first, last);
        }

        template < typename InputIter >
        flat_multimap(InputIter first, InputIter last, const Compare& c)
        : base_type(c) {
            insert(first, last);
        }

        template < typename InputIter, typename Allocator >
        flat_multimap(InputIter first, InputIter last, const Allocator& a)
        : data_(a) {
            insert(first, last);
        }

        template < typename InputIter , typename Allocator >
        flat_multimap(InputIter first, InputIter last, const Compare& c, const Allocator& a)
        : base_type(c)
        , data_(a) {
            insert(first, last);
        }

        flat_multimap(std::initializer_list<value_type> ilist) {
            insert(ilist);
        }

        flat_multimap(std::initializer_list<value_type> ilist, const Compare& c)
        : base_type(c) {
            insert(ilist);
        }

        template < typename Allocator >
        flat_multimap(std::initializer_list<value_type> ilist, const Allocator& a)
        : data_(a) {
            insert(ilist);
        }

        template < typename Allocator >
        flat_multimap(std::initializer_list<value_type> ilist, const Compare& c, const Allocator& a)
        : base_type(c)
        , data_(a) {
            insert(ilist);
        }

        template < typename Allocator >
        flat_multimap(flat_multimap&& other, const Allocator& a)
        : base_type(static_cast<base_type&&>(other))
        , data_(std::move(other.data_), a) {}

        template < typename Allocator >
        flat_multimap(const flat_multimap& other, const Allocator& a)
        : base_type(static_cast<const base_type&>(other))
        , data_(other.data_, a) {}

        flat_multimap(flat_multimap&& other) = default;
        flat_multimap(const flat_multimap& other) = default;

        flat_multimap& operator=(flat_multimap&& other) = default;
        flat_multimap& operator=(const flat_multimap& other) = default;

        flat_multimap& operator=(std::initializer_list<value_type> ilist) {
            flat_multimap(ilist).swap(*this);
            return *this;
        }

        iterator begin()
        noexcept(noexcept(std::declval<container_type&>().begin())) {
            return data_.begin();
        }

        const_iterator begin() const
        noexcept(noexcept(std::declval<const container_type&>().begin())) {
            return data_.begin();
        }

        const_iterator cbegin() const
        noexcept(noexcept(std::declval<const container_type&>().cbegin())) {
            return data_.cbegin();
        }

        iterator end()
        noexcept(noexcept(std::declval<container_type&>().end())) {
            return data_.end();
        }

        const_iterator end() const
        noexcept(noexcept(std::declval<const container_type&>().end())) {
            return data_.end();
        }

        const_iterator cend() const
        noexcept(noexcept(std::declval<const container_type&>().cend())) {
            return data_.cend();
        }

        reverse_iterator rbegin()
        noexcept(noexcept(std::declval<container_type&>().rbegin())) {
            return data_.rbegin();
        }

        const_reverse_iterator rbegin() const
        noexcept(noexcept(std::declval<const container_type&>().rbegin())) {
            return data_.rbegin();
        }

        const_reverse_iterator crbegin() const
        noexcept(noexcept(std::declval<const container_type&>().crbegin())) {
            return data_.crbegin();
        }

        reverse_iterator rend()
        noexcept(noexcept(std::declval<container_type&>().rend())) {
            return data_.rend();
        }

        const_reverse_iterator rend() const
        noexcept(noexcept(std::declval<const container_type&>().rend())) {
            return data_.rend();
        }

        const_reverse_iterator crend() const
        noexcept(noexcept(std::declval<const container_type&>().crend())) {
            return data_.crend();
        }

        bool empty() const
        noexcept(noexcept(std::declval<const container_type&>().empty())) {
            return data_.empty();
        }

        size_type size() const
        noexcept(noexcept(std::declval<const container_type&>().size())) {
            return data_.size();
        }

        size_type max_size() const
        noexcept(noexcept(std::declval<const container_type&>().max_size())) {
            return data_.max_size();
        }

        size_type capacity() const
        noexcept(noexcept(std::declval<const container_type&>().capacity())) {
            return data_.capacity();
        }

        void reserve(size_type ncapacity) {
            data_.reserve(ncapacity);
        }

        void shrink_to_fit() {
            data_.shrink_to_fit();
        }

        mapped_type& operator[](key_type&& key) {
            const iterator iter = find(key);
            return iter != end()
                ? iter->second
                : emplace(std::move(key), mapped_type())->second;
        }

        mapped_type& operator[](const key_type& key) {
            const iterator iter = find(key);
            return iter != end()
                ? iter->second
                : emplace(key, mapped_type())->second;
        }

        mapped_type& at(const key_type& key) {
            const iterator iter = find(key);
            if ( iter != end() ) {
                return iter->second;
            }

            FLAT_CONTAINERS_KEY_NOT_FOUND();
        }

        const mapped_type& at(const key_type& key) const {
            const const_iterator iter = find(key);
            if ( iter != end() ) {
                return iter->second;
            }

            FLAT_CONTAINERS_KEY_NOT_FOUND();
        }

        iterator insert(value_type&& value) {
            const iterator iter = upper_bound(value.first);
            return data_.insert(iter, std::move(value));
        }

        iterator insert(const value_type& value) {
            const iterator iter = upper_bound(value.first);
            return data_.insert(iter, value);
        }

        iterator insert(const_iterator hint, value_type&& value) {
            return (hint == begin() || !this->operator()(value, *(hint - 1)))
                && (hint == end() || !this->operator()(*hint, value))
                ? data_.insert(hint, std::move(value))
                : insert(std::move(value));
        }

        iterator insert(const_iterator hint, const value_type& value) {
            return (hint == begin() || !this->operator()(value, *(hint - 1)))
                && (hint == end() || !this->operator()(*hint, value))
                ? data_.insert(hint, value)
                : insert(value);
        }

        template < typename InputIter >
        void insert(InputIter first, InputIter last) {
            while ( first != last ) {
                insert(*first++);
            }
        }

        void insert(std::initializer_list<value_type> ilist) {
            insert(ilist.begin(), ilist.end());
        }

        template < typename... Args >
        iterator emplace(Args&&... args) {
            return insert(value_type(std::forward<Args>(args)...));
        }

        template < typename... Args >
        iterator emplace_hint(const_iterator hint, Args&&... args) {
            return insert(hint, value_type(std::forward<Args>(args)...));
        }

        void clear()
        noexcept(noexcept(std::declval<container_type&>().clear())) {
            data_.clear();
        }

        iterator erase(const_iterator iter) {
            return data_.erase(iter);
        }

        iterator erase(const_iterator first, const_iterator last) {
            return data_.erase(first, last);
        }

        size_type erase(const key_type& key) {
            const auto p = equal_range(key);
            size_type r = std::distance(p.first, p.second);
            erase(p.first, p.second);
            return r;
        }

        void swap(flat_multimap& other)
            noexcept(std::is_nothrow_swappable_v<base_type>
                && std::is_nothrow_swappable_v<container_type>)
        {
            using std::swap;
            swap(
                static_cast<base_type&>(*this),
                static_cast<base_type&>(other));
            swap(data_, other.data_);
        }

        size_type count(const key_type& key) const {
            const auto p = equal_range(key);
            return std::distance(p.first, p.second);
        }

        iterator find(const key_type& key) {
            const iterator iter = lower_bound(key);
            return iter != end() && !this->operator()(key, iter->first)
                ? iter
                : end();
        }

        const_iterator find(const key_type& key) const {
            const const_iterator iter = lower_bound(key);
            return iter != end() && !this->operator()(key, iter->first)
                ? iter
                : end();
        }

        std::pair<iterator, iterator> equal_range(const key_type& key) {
            const base_type& comp = *this;
            return std::equal_range(begin(), end(), key, comp);
        }

        std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
            const base_type& comp = *this;
            return std::equal_range(begin(), end(), key, comp);
        }

        iterator lower_bound(const key_type& key) {
            const base_type& comp = *this;
            return std::lower_bound(begin(), end(), key, comp);
        }

        const_iterator lower_bound(const key_type& key) const {
            const base_type& comp = *this;
            return std::lower_bound(begin(), end(), key, comp);
        }

        iterator upper_bound(const key_type& key) {
            const base_type& comp = *this;
            return std::upper_bound(begin(), end(), key, comp);
        }

        const_iterator upper_bound(const key_type& key) const {
            const base_type& comp = *this;
            return std::upper_bound(begin(), end(), key, comp);
        }

        key_compare key_comp() const {
            return *this;
        }

        value_compare value_comp() const {
            return value_compare(key_comp());
        }
    private:
        container_type data_;
    };
}

namespace notstd
{
    template < typename Key
             , typename Value
             , typename Compare
             , typename Container >
    void swap(
        flat_multimap<Key, Value, Compare, Container>& l,
        flat_multimap<Key, Value, Compare, Container>& r)
        noexcept(noexcept(l.swap(r)))
    {
        l.swap(r);
    }

    template < typename Key
             , typename Value
             , typename Compare
             , typename Container >
    bool operator==(
        const flat_multimap<Key, Value, Compare, Container>& l,
        const flat_multimap<Key, Value, Compare, Container>& r)
    {
        return l.size() == r.size()
            && std::equal(l.begin(), l.end(), r.begin());
    }

    template < typename Key
             , typename Value
             , typename Compare
             , typename Container >
    bool operator!=(
        const flat_multimap<Key, Value, Compare, Container>& l,
        const flat_multimap<Key, Value, Compare, Container>& r)
    {
        return !(l == r);
    }

    template < typename Key
             , typename Value
             , typename Compare
             , typename Container >
    bool operator<(
        const flat_multimap<Key, Value, Compare, Container>& l,
        const flat_multimap<Key, Value, Compare, Container>& r)
    {
        return std::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
    }

    template < typename Key
             , typename Value
             , typename Compare
             , typename Container >
    bool operator>(
        const flat_multimap<Key, Value, Compare, Container>& l,
        const flat_multimap<Key, Value, Compare, Container>& r)
    {
        return r < l;
    }

    template < typename Key
             , typename Value
             , typename Compare
             , typename Container >
    bool operator<=(
        const flat_multimap<Key, Value, Compare, Container>& l,
        const flat_multimap<Key, Value, Compare, Container>& r)
    {
        return !(r < l);
    }

    template < typename Key
             , typename Value
             , typename Compare
             , typename Container >
    bool operator>=(
        const flat_multimap<Key, Value, Compare, Container>& l,
        const flat_multimap<Key, Value, Compare, Container>& r)
    {
        return !(l < r);
    }
}
