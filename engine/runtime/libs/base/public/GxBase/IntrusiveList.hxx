#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Diagnostics.hxx>

namespace Graphyte
{
    template <typename T>
    struct IntrusiveListNode final
    {
        T* Next{ nullptr };
        T* Prev{ nullptr };
    };

    template <typename T, IntrusiveListNode<T> T::*Node>
    struct IntrusiveList final
    {
    private:
        T* Head{ nullptr };
        T* Tail{ nullptr };

    public:
        IntrusiveList() noexcept = default;

        IntrusiveList(const IntrusiveList&) noexcept = delete;

        IntrusiveList& operator=(const IntrusiveList&) noexcept = delete;

        IntrusiveList(IntrusiveList&&) noexcept = default;

        IntrusiveList& operator=(IntrusiveList&&) noexcept = default;

    public:
        void InsertHead(T* element) noexcept
        {
            GX_ASSERT(element != nullptr);

            IntrusiveListNode<T>* node = &(element->*Node);

            GX_ASSERT(node->Next == nullptr);
            GX_ASSERT(node->Prev == nullptr);

            node->Prev = nullptr;
            node->Next = this->Head;

            if (this->Head != nullptr)
            {
                IntrusiveListNode<T>* lastHead = &(this->Head->*Node);
                lastHead->Prev                 = element;
            }

            this->Head = element;

            if (this->Tail == nullptr)
            {
                this->Tail = this->Head;
            }
        }

        void InsertTail(T* element) noexcept
        {
            GX_ASSERT(element != nullptr);

            if (this->Tail == nullptr)
            {
                this->InsertHead(element);
            }
            else
            {
                IntrusiveListNode<T>* tailNode    = &(this->Tail->*Node);
                IntrusiveListNode<T>* elementNode = &(element->*Node);

                GX_ASSERT(elementNode->Next == nullptr);
                GX_ASSERT(elementNode->Prev == nullptr);

                tailNode->Next    = element;
                elementNode->Prev = this->Tail;
                elementNode->Next = nullptr;
                this->Tail        = element;
            }
        }

        void InsertAfter(T* element, T* relative) noexcept
        {
            GX_ASSERT(element != nullptr);
            GX_ASSERT(relative != nullptr);

            IntrusiveListNode<T>* elementNode  = &(element->*Node);
            IntrusiveListNode<T>* relativeNode = &(relative->*Node);

            if (relativeNode->Next != nullptr)
            {
                IntrusiveListNode<T>* nextNode = &(relativeNode->Next->*Node);
                nextNode->Prev                 = element;
            }

            elementNode->Next  = relativeNode->Next;
            elementNode->Prev  = relative;
            relativeNode->Next = element;

            if (relative == this->Tail)
            {
                this->Tail = element;
            }
        }

        void InsertBefore(T* element, T* relative) noexcept
        {
            GX_ASSERT(element != nullptr);
            GX_ASSERT(relative != nullptr);

            IntrusiveListNode<T>* elementNode  = &(element->*Node);
            IntrusiveListNode<T>* relativeNode = &(relative->*Node);

            if (relativeNode->Prev != nullptr)
            {
                IntrusiveListNode<T>* prevNode = &(relativeNode->Prev->*Node);
                prevNode->Next                 = element;
            }

            elementNode->Next  = relative;
            elementNode->Prev  = relativeNode->Prev;
            relativeNode->Prev = element;

            if (relative == this->Head)
            {
                this->Head = element;
            }
        }

        T* RemoveHead() noexcept
        {
            GX_ASSERT(this->Head != nullptr);

            T* result = this->Head;
            Remove(result);
            return result;
        }

        T* RemoveTail() noexcept
        {
            GX_ASSERT(this->Tail != nullptr);

            T* result = this->Tail;
            Remove(result);
            return result;
        }

        T* Remove(T* element) noexcept
        {
            GX_ASSERT(element != nullptr);

            IntrusiveListNode<T>* elementNode = &(element->*Node);

            T* next = elementNode->Next;
            T* prev = elementNode->Prev;

            IntrusiveListNode<T>* nextNode = &(next->*Node);
            IntrusiveListNode<T>* prevNode = &(prev->*Node);

            if (element == this->Head)
            {
                this->Head = next;
            }

            if (element == this->Tail)
            {
                this->Tail = prev;
            }

            if (prev != nullptr)
            {
                prevNode->Next = next;
            }

            if (next != nullptr)
            {
                nextNode->Prev = prev;
            }

            elementNode->Next = nullptr;
            elementNode->Prev = nullptr;

            return next;
        }

        T* GetHead() const noexcept
        {
            return this->Head;
        }

        T* GetTail() const noexcept
        {
            return this->Tail;
        }

        T* Next(T* element) const noexcept
        {
            GX_ASSERT(element != nullptr);

            IntrusiveListNode<T>* elementNode = &(element->*Node);
            return elementNode->Next;
        }

        const T* Next(const T* element) const noexcept
        {
            GX_ASSERT(element != nullptr);

            const IntrusiveListNode<T>* elementNode = &(element->*Node);
            return elementNode->Next;
        }

        T* Prev(T* element) const noexcept
        {
            GX_ASSERT(element != nullptr);

            IntrusiveListNode<T>* elementNode = &(element->*Node);
            return elementNode->Prev;
        }

        const T* Prev(const T* element) const noexcept
        {
            GX_ASSERT(element != nullptr);

            const IntrusiveListNode<T>* elementNode = &(element->*Node);
            return elementNode->Prev;
        }

        void Clear() noexcept
        {
            while (!IsEmpty())
            {
                Remove(this->Head);
            }
        }

        bool IsEmpty() const noexcept
        {
            return this->Head == nullptr;
        }

        size_t GetLength() const noexcept
        {
            size_t length{};

            for (T* element = this->Head; element != nullptr; element = this->Next(element))
            {
                ++length;
            }

            return length;
        }

        bool Contains(T* element) noexcept
        {
            for (T* current = this->Head; current != element; current = this->Next(current))
            {
                if (current == element)
                {
                    return true;
                }
            }

            return false;
        }

        bool Contains(const T* element) const noexcept
        {
            for (T* current = this->Head; current != element; current = this->Next(current))
            {
                if (current == element)
                {
                    return true;
                }
            }

            return false;
        }
    };
}
