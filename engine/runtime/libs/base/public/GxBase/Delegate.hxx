#pragma once
#include <GxBase/Base.module.hxx>

// =================================================================================================
//
// Delegate type implementation.
//

namespace Graphyte
{
    template <typename TInvokable>
    struct DelegateBase;

    template <typename TResult, typename... TArgs>
    struct DelegateBase<TResult(TArgs...)>
    {
        using StubType = TResult (*)(void* objeect, TArgs... args);

        struct Invokable
        {
            void* m_Object  = nullptr;
            StubType m_Stub = nullptr;

            Invokable() noexcept = default;

            Invokable(void* object, StubType stub) noexcept
                : m_Object{ object }
                , m_Stub{ stub }
            {
            }

            void Clone(Invokable& target) const noexcept
            {
                target.m_Object = m_Object;
                target.m_Stub   = m_Stub;
            }

            bool operator==(const Invokable& other) const noexcept
            {
                return m_Object == other.m_Object && m_Stub == other.m_Stub;
            }

            bool operator!=(const Invokable& other) const noexcept
            {
                return m_Object != other.m_Object || m_Stub != other.m_Stub;
            }
        };
    };

    //! \brief This class implements delegate object which can invoke any callable object matching
    //! function signature to TInvokable.
    template <typename TInvokable>
    struct Delegate;

    template <typename TResult, typename... TArgs>
    struct Delegate<TResult(TArgs...)> final : private DelegateBase<TResult(TArgs...)>
    {
    private:
        typename DelegateBase<TResult(TArgs...)>::Invokable m_Invocation;

    public:
        Delegate() noexcept = default;

        Delegate(const Delegate& other) noexcept
            : m_Invocation{}
        {
            other.m_Invocation.Clone(m_Invocation);
        }

        template <typename TLambda>
        Delegate(const TLambda& lambda) noexcept
            : m_Invocation{}
        {
            Assign(const_cast<void*>(reinterpret_cast<void const*>(&lambda)), LambdaStub<TLambda>);
        }

    public:
        Delegate& operator=(const Delegate& other) noexcept
        {
            other.m_Invocation.Clone(m_Invocation);
            return (*this);
        }

        template <typename TLambda>
        Delegate& operator=(const TLambda& lambda) noexcept
        {
            Assign(const_cast<void*>(reinterpret_cast<void const*>(&lambda)), LambdaStub<TLambda>);
            return (*this);
        }

    public:
        bool IsBound() const noexcept
        {
            return m_Invocation.m_Stub == nullptr;
        }

        void Unbind() noexcept
        {
            m_Invocation.m_Object = nullptr;
            m_Invocation.m_Stub   = nullptr;
        }

        bool operator==(void* pointer) const noexcept
        {
            return pointer == nullptr && IsBound();
        }

        bool operator!=(void* pointer) const noexcept
        {
            return pointer != nullptr || !IsBound();
        }

        bool operator==(const Delegate& other) const noexcept
        {
            return m_Invocation == other.m_Invocation;
        }

        bool operator!=(const Delegate& other) const noexcept
        {
            return m_Invocation != other.m_Invocation;
        }

    public:
        //! \brief Makes instance of delegate object from pointer to member function.
        template <typename TClass, TResult (TClass::*TMethod)(TArgs...)>
        static Delegate Make(TClass* instance) noexcept
        {
            return Delegate{ instance, MethodStub<TClass, TMethod> };
        }

        //! \brief Makes instance of delegate object from pointer to member function.
        template <typename TClass, TResult (TClass::*TMethod)(TArgs...) const>
        static Delegate Make(TClass const* instance) noexcept
        {
            return Delegate{ const_cast<TClass*>(instance), ConstMethodStub<TClass, TMethod> };
        }

        //! \brief Makes instance of delegate object from pointer to static / free function.
        template <TResult (*TMethod)(TArgs...)>
        static Delegate Make() noexcept
        {
            return Delegate{ nullptr, FunctionStub<TMethod> };
        }

        //! \brief Makes instance of delegate object from lambda object.
        template <typename TLambda>
        static Delegate Make(const TLambda& lambda) noexcept
        {
            return Delegate{ reinterpret_cast<void*>(&lambda), LambdaStub<TLambda> };
        }

    public:
        TResult operator()(TArgs... args) const noexcept
        {
            return (*m_Invocation.m_Stub)(m_Invocation.m_Object, std::forward<TArgs>(args)...);
        }
        TResult Invoke(TArgs... args) const noexcept
        {
            return (*m_Invocation.m_Stub)(m_Invocation.m_Object, std::forward<TArgs>(args)...);
        }

    private:
        Delegate(void* object, typename DelegateBase<TResult(TArgs...)>::StubType stub) noexcept
        {
            m_Invocation.m_Object = object;
            m_Invocation.m_Stub   = stub;
        }

        void Assign(void* object, typename DelegateBase<TResult(TArgs...)>::StubType stub) noexcept
        {
            m_Invocation.m_Object = object;
            m_Invocation.m_Stub   = stub;
        }

    private:
        template <typename TClass, TResult (TClass::*TMethod)(TArgs...)>
        static TResult MethodStub(void* self, TArgs... args) noexcept
        {
            TClass* target = static_cast<TClass*>(self);
            return (target->*TMethod)(std::forward<TArgs>(args)...);
        }

        template <typename TClass, TResult (TClass::*TMethod)(TArgs...) const>
        static TResult ConstMethodStub(void* self, TArgs... args) noexcept
        {
            TClass const* target = static_cast<TClass*>(self);
            return (target->*TMethod)(std::forward<TArgs>(args)...);
        }

        template <TResult (*TMethod)(TArgs...)>
        static TResult FunctionStub(void* self, TArgs... args) noexcept
        {
            (void)self;
            return (TMethod)(std::forward<TArgs>(args)...);
        }

        template <typename TLambda>
        static TResult LambdaStub(void* self, TArgs... args) noexcept
        {
            TLambda* target = static_cast<TLambda*>(self);
            return (target->operator())(std::forward<TArgs>(args)...);
        }
    };

    template <typename TInvokable>
    struct EventBase;

    template <typename TResult, typename... TArgs>
    struct EventBase<TResult(TArgs...)>
    {
        using DelegateType = Delegate<TResult(TArgs...)>;

        std::vector<DelegateType> m_Items;

        void operator+=(const DelegateType& invokable) noexcept
        {
            auto const& it = std::find(m_Items.cbegin(), m_Items.cend(), invokable);
            if (it == m_Items.cend())
            {
                m_Items.push_back(invokable);
            }
        }

        void operator-=(const DelegateType& invokable) noexcept
        {
            m_Items.erase(std::remove(m_Items.begin(), m_Items.end(), invokable));
        }
    };

    /*
     * \brief   Provides event object for aggregating delegates and calling them all at once.
     */
    template <typename TInvokable>
    struct Event;

    template <typename TResult, typename... TArgs>
    struct Event<TResult(TArgs...)> final : public EventBase<TResult(TArgs...)>
    {
        TResult Invoke(TArgs... args) const noexcept
        {
            TResult result{};

            for (auto const& item : this->m_Items)
            {
                result = item.Invoke(std::forward<TArgs>(args)...);
            }

            return result;
        }

        TResult operator()(TArgs... args) const noexcept
        {
            return this->Invoke(std::forward<TArgs>(args)...);
        }
    };

    template <typename... TArgs>
    struct Event<void(TArgs...)> final : public EventBase<void(TArgs...)>
    {
        void Invoke(TArgs... args) const noexcept
        {
            for (auto const& item : this->m_Items)
            {
                item.Invoke(std::forward<TArgs>(args)...);
            }
        }

        void operator()(TArgs... args) const noexcept
        {
            this->Invoke(std::forward<TArgs>(args)...);
        }
    };
}
