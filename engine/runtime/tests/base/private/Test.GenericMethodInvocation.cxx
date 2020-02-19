#include <catch2/catch.hpp>
#include <Graphyte/Base.module.hxx>

#include <cassert>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <array>
#include <vector>

#ifndef GX_NOINLINE
#ifdef _MSC_VER
#define GX_NOINLINE __declspec(noinline)
#else
#define GX_NOINLINE __attribute__((__noinline__))
#define __forceinline inline
#endif
#endif

#define rtti_function(name)                 static void rtticall_##name(Runtime::Object* $this, Runtime::StackFrame& $frame)
#define rtti_begin_call(count)              [[maybe_unused]] void** $stack = reinterpret_cast<void**>($frame.Stack)
#define rtti_argument(type, name)           type name = *reinterpret_cast<type*>(*$stack++)
#define rtti_end_call()
#define rtti_this                           (static_cast<ThisClass*>($this))
#define rtti_return(type)                   *reinterpret_cast<type*>(*$stack)

#define xtti_function(name)                 static void rtticall_##name(Runtime::Object* $this, Runtime::StackFrame& $frame)
#define xtti_signature(...)                 auto& $params = *reinterpret_cast<std::tuple<__VA_ARGS__>*>($frame.Stack)
#define xtti_call(name)                     std::apply()
#define xtti_arg(index)                     std::get<index>($params)
#define xtti_return                         std::get<std::tuple_size<decltype($params)>::value - 1>($params)
#define xtti_this                           ((ThisClass*)$this)

namespace GenericMethodInvocation
{
    template <typename TFunctionType>
    struct FunctionTypeToSignature;

    namespace Runtime
    {
        class Object
        {
        public: virtual ~Object() noexcept = default;
        };

        enum class FunctionSignature : uint32_t
        {
        };

        enum class FunctionFlags : uint32_t
        {
        };

        template <typename... TArgs>
        struct StackFramePayload;

        template <typename TResult, typename... TArgs>
        struct StackFramePayload<TResult(TArgs...)> final
        {
            std::tuple<TArgs..., TResult> Values;

            StackFramePayload(TArgs&&... args) noexcept
                : Values{ std::forward<TArgs>(args)..., TResult{} }
            {
            }

            const TResult& GetResult() const noexcept
            {
                return std::get<sizeof...(TArgs)>(Values);
            }

            size_t GetResultOffset() const noexcept
            {
                auto& last = std::get<sizeof...(TArgs)>(Values);
                auto& first = std::get<0>(Values);
                return static_cast<char*>(&first) - static_cast<char*>(&last);
            }
        };

        template <typename... TArgs>
        struct StackFramePayload<void(TArgs...)> final
        {
            std::tuple<TArgs...> Values;

            StackFramePayload(TArgs&&... args) noexcept
                : Values{ std::forward<TArgs>(args)... }
            {
            }

            void GetResult() const noexcept
            {
            }
        };

        struct StackFrame final
        {
            void** Stack;
            size_t ResultOffset;
            size_t Count;
        };

        using FunctionPointer = void(*)(Object*, StackFrame& frame);

        struct Function final
        {
            FunctionPointer Pointer;
            const char* Name;
            size_t ParamsCount;
            FunctionFlags Flags;
            FunctionSignature Signature;

            void Invoke(Object* o, StackFrame& frame) const noexcept
            {
                (*Pointer)(o, frame);
            }
        };

        template <typename TInvokable>
        struct DecayFunction final
        {
            using Type = TInvokable;
        };

        template <typename TType, typename TResult, typename... TArgs>
        struct DecayFunction<TResult(TType::*)(TArgs...)> final
        {
            using Type = TResult(TArgs...);
            using Args = std::tuple<TArgs...>;
            using Result = TResult;
        };

        template <typename TResult, typename... TArgs>
        struct DecayFunction<TResult(*)(TArgs...)> final
        {
            using Type = TResult(TArgs...);
            using Args = std::tuple<TArgs...>;
            using Result = TResult;
        };

        template <typename TResult, typename... TArgs>
        struct DecayFunction<TResult(TArgs...)> final
        {
            using Type = TResult(TArgs...);
            using Args = std::tuple<TArgs...>;
            using Result = TResult;
        };

        struct IDispatchable
        {
            virtual void Dispatch(Runtime::StackFrame& frame) noexcept = 0;
        };

        template <typename TInvokable>
        struct Invoke;


        template <typename TResult, typename... TArgs>
        struct Invoke<TResult(TArgs...)> final
        {
            static inline TResult Dispatchable(IDispatchable& dispatchable, TArgs... args) noexcept
            {
                TResult result{};
                void* params[]{ &args..., &result, nullptr };
                Runtime::StackFrame frame{ params, sizeof...(TArgs) * sizeof(void*), sizeof...(TArgs) };
                dispatchable.Dispatch(frame);
                return result;
            }

            static inline TResult Function(Runtime::Object* object, const Runtime::Function& function, TArgs... args) noexcept
            {
                TResult result{};
                void* params[]{ &args..., &result, nullptr };
                Runtime::StackFrame frame{ params, sizeof...(TArgs) * sizeof(void*), sizeof...(TArgs) };
                function.Invoke(object, frame);
                return result;
            }
        };

        template <typename... TArgs>
        struct Invoke<void(TArgs...)> final
        {
            static inline void Dispatchable(IDispatchable& dispatchable, TArgs... args) noexcept
            {
                void* params[]{ &args..., nullptr };
                Runtime::StackFrame frame{ params, sizeof...(TArgs) * sizeof(void*), sizeof...(TArgs) };
                dispatchable.Dispatch(frame);
            }

            static inline void Function(Runtime::Object* object, const Runtime::Function& function, TArgs... args) noexcept
            {
                void* params[]{ &args..., nullptr };
                Runtime::StackFrame frame{ params, sizeof...(TArgs) * sizeof(void*), sizeof...(TArgs) };
                function.Invoke(object, frame);
            }
        };


        struct PipeBase : public Runtime::Object, public Runtime::IDispatchable
        {
            virtual ~PipeBase() noexcept = default;

            std::vector<PipeBase*> Pipes;
            Runtime::Object* Owner;
            std::vector<Runtime::Function*> Functions;

            void Dispatch(Runtime::StackFrame& frame) noexcept override
            {
                // Call pipes
                for (auto&& pipe : Pipes)
                {
                    pipe->Dispatch(frame);
                }

                // Call functions
                for (auto&& func : Functions)
                {
                    func->Invoke(Owner, frame);
                }
            }

            virtual Runtime::FunctionSignature GetSignature() const noexcept = 0;
        };

        template <typename TInvokable>
        struct Pipe;

        template <typename TResult, typename... TArgs>
        struct Pipe<TResult(TArgs...)> : public PipeBase
        {
            TResult Invoke(TArgs... args) noexcept
            {
                return Runtime::Invoke<TResult(TArgs...)>::Dispatchable(*this, std::forward<TArgs>(args)...);
            }

            Runtime::FunctionSignature GetSignature() const noexcept  final
            {
                return FunctionTypeToSignature<TResult(TArgs...)>::Signature;
            }

            void Link(Pipe* pipe) noexcept
            {
                auto it = std::find(Pipes.begin(), Pipes.end(), pipe);
                if (it == Pipes.end())
                {
                    Pipes.push_back(pipe);
                }
            }

            void Unlink(Pipe* pipe) noexcept
            {
                auto it = std::find(Pipes.begin(), Pipes.end(), pipe);
                if (it != Pipes.end())
                {
                    Pipes.erase(it);
                }
            }

            void Link(Function* function) noexcept
            {
                auto it = std::find(Functions.begin(), Functions.end(), function);
                if (it == Functions.end())
                {
                    Functions.push_back(function);
                }
            }

            void Unlink(Function* function) noexcept
            {
                auto it = std::find(Functions.begin(), Functions.end(), function);
                if (it != Functions.end())
                {
                    Functions.erase(it);
                }
            }
        };
    }
}



namespace GenericMethodInvocation
{

#define RTTI_FUNCTION_SIGNATURE(function, signature) \
    template <> \
    struct FunctionTypeToSignature<function> final { \
        static const Runtime::FunctionSignature Signature = Runtime::FunctionSignature(signature); \
    }

    class Component : public Runtime::Object
    {
    public:
        virtual ~Component() noexcept = default;
    };

    class Pawn : public Runtime::Object
    {
        using ThisClass = Pawn;
    public:
        Pawn() noexcept;
        virtual ~Pawn() noexcept = default;

        int32_t C;

        Runtime::Pipe<void(void)> SignalPipe;
        Runtime::Pipe<int32_t(int32_t, int32_t)> AddingPipe;

    public:
        GX_NOINLINE int32_t DoAddition(int32_t a, int32_t b)
        {
            return a + b + C;
        }

        GX_NOINLINE void DoSignal()
        {
            C = 42;
        }

    public:
        rtti_function(DoAddition)
        {
            rtti_begin_call(4);
            rtti_argument(int32_t, a);
            rtti_argument(int32_t, b);
            rtti_end_call();
            rtti_return(int32_t) = rtti_this->DoAddition(a, b);
        }

        rtti_function(DoSignal)
        {
            rtti_begin_call(0);
            rtti_end_call();
            rtti_this->DoSignal();
        }
    };

    RTTI_FUNCTION_SIGNATURE(void(void), 0x1001);
    RTTI_FUNCTION_SIGNATURE(int32_t(int32_t, int32_t), 0x1002);

    Runtime::Function class_Pawn_function_DoAddition{
        &Pawn::rtticall_DoAddition,
        "DoAddition",
        4,
        Runtime::FunctionFlags{},
        FunctionTypeToSignature<typename Runtime::DecayFunction<decltype(&Pawn::DoAddition)>::Type>::Signature,
    };

    Runtime::Function class_Pawn_function_DoSignal{
        &Pawn::rtticall_DoSignal,
        "DoSignal",
        0,
        Runtime::FunctionFlags{},
        FunctionTypeToSignature<typename Runtime::DecayFunction<decltype(&Pawn::DoSignal)>::Type>::Signature
    };

    Pawn::Pawn() noexcept
    {
        this->SignalPipe.Owner = this;
        this->SignalPipe.Link(&class_Pawn_function_DoSignal);

        this->AddingPipe.Owner = this;
        this->AddingPipe.Link(&class_Pawn_function_DoAddition);
    }

    class SomeObjectBetween : public Runtime::Object
    {
    public:
        virtual ~SomeObjectBetween() noexcept = default;

        Runtime::Pipe<int32_t(int32_t, int32_t)> AddingPipe;
        Runtime::Pipe<void(void)> SignalPipe;
    };
}

#ifndef TEST_CASE
#define TEST_CASE(...) int main()
#define CHECK(...)
#endif

TEST_CASE("Generic Method invocation")
{
    using namespace GenericMethodInvocation;

    Pawn pawn{};
    pawn.C = 42;

    // Regular signal calling
    Runtime::Invoke<void(void)>::Function(&pawn, class_Pawn_function_DoSignal);

    // Arbitrary function with return value.
    {
        int32_t a = 4;
        int32_t b = 5;

        // Convenient calling
        auto r = Runtime::Invoke<int32_t(int32_t, int32_t)>::Function(&pawn, class_Pawn_function_DoAddition, a, b);

        CHECK(r == 51);
    }

    // Dispatch signal via pipe
    {
        pawn.SignalPipe.Invoke();
    }

    // Dispatch addition via pipe
    {
        pawn.C = 0;
        int32_t a = 3;
        int32_t b = 5;

        auto r = pawn.AddingPipe.Invoke(a, b);
        CHECK(r == 8);
    }

    // Dispatch via other object
    {
        SomeObjectBetween between1{};
        SomeObjectBetween between2{};

        // Link pipes
        between1.AddingPipe.Link(&pawn.AddingPipe);
        between1.SignalPipe.Link(&pawn.SignalPipe);

        between2.AddingPipe.Link(&between1.AddingPipe);
        between2.SignalPipe.Link(&between1.SignalPipe);

        pawn.C = 1;

        int32_t a = 2;
        int32_t b = 3;

        auto r = between2.AddingPipe.Invoke(a, b);
        CHECK(r == 6);

        between2.SignalPipe.Invoke();
    }
}


#include <cassert>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <array>
#include <vector>
#include <functional>
#include <ctime>

namespace Techland
{
    namespace Runtime
    {
        class Object
        {
        public: virtual ~Object() noexcept = default;
        };

        struct StackFrame final
        {
            void* Params;
            void* Result;
        };

        using FunctionPointer = void(*)(Object*, StackFrame&);

        struct Function final
        {
            FunctionPointer Pointer;
            const char* Name;

            void Invoke(Object* object, StackFrame& frame) const noexcept
            {
                (*Pointer)(object, frame);
            }
        };

        template <typename TInvokable>
        struct DecayFunction final
        {
            using Type = TInvokable;
        };

        template <typename TType, typename TResult, typename... TArgs>
        struct DecayFunction<TResult(TType::*)(TArgs...)> final
        {
            using Type = TResult(TArgs...);
            using Args = std::tuple<TArgs...>;
            using ArgsRef = std::tuple<TArgs&...>;
            using Result = TResult;
        };

        template <typename TResult, typename... TArgs>
        struct DecayFunction<TResult(*)(TArgs...)> final
        {
            using Type = TResult(TArgs...);
            using Args = std::tuple<TArgs...>;
            using ArgsRef = std::tuple<TArgs&...>;
            using Result = TResult;
        };

        template <typename TResult, typename... TArgs>
        struct DecayFunction<TResult(TArgs...)> final
        {
            using Type = TResult(TArgs...);
            using Args = std::tuple<TArgs...>;
            using ArgsRef = std::tuple<TArgs&...>;
            using Result = TResult;
        };

        struct IDispatchable
        {
            virtual void Dispatch(Runtime::StackFrame& frame) noexcept = 0;
        };

        template <typename TInvokable>
        struct Invoke;


        template <typename TResult, typename... TArgs>
        struct Invoke<TResult(TArgs...)> final
        {
            static inline TResult Dispatchable(IDispatchable& dispatchable, TArgs... args) noexcept
            {
                TResult result{};
                auto params = std::forward_as_tuple(args...);
                Runtime::StackFrame frame{ &params, &result };
                dispatchable.Dispatch(frame);
                return result;
            }

            static inline TResult Function(Runtime::Object* object, const Runtime::Function& function, TArgs... args) noexcept
            {
                TResult result{};
                auto params = std::forward_as_tuple(args...);
                Runtime::StackFrame frame{ &params, &result };
                function.Invoke(object, frame);
                return result;
            }
        };

        template <typename... TArgs>
        struct Invoke<void(TArgs...)> final
        {
            static inline void Dispatchable(IDispatchable& dispatchable, TArgs... args) noexcept
            {
                auto params = std::forward_as_tuple(args...);
                Runtime::StackFrame frame{ &params, nullptr };
                dispatchable.Dispatch(frame);
            }

            static inline void Function(Runtime::Object* object, const Runtime::Function& function, TArgs... args) noexcept
            {
                auto params = std::forward_as_tuple(args...);
                Runtime::StackFrame frame{ &params, nullptr };
                function.Invoke(object, frame);
            }
        };


        struct PipeBase : public Runtime::Object, public Runtime::IDispatchable
        {
            virtual ~PipeBase() noexcept = default;

            std::vector<PipeBase*> Pipes;
            Runtime::Object* Owner;
            std::vector<Runtime::Function*> Functions;

            void Dispatch(Runtime::StackFrame& frame) noexcept override
            {
                // Call pipes
                for (auto&& pipe : Pipes)
                {
                    pipe->Dispatch(frame);
                }

                // Call functions
                for (auto&& func : Functions)
                {
                    func->Invoke(Owner, frame);
                }
            }
        };

        template <typename TInvokable>
        struct Pipe;

        template <typename TResult, typename... TArgs>
        struct Pipe<TResult(TArgs...)> : public PipeBase
        {
            TResult Invoke(TArgs... args) noexcept
            {
                return Runtime::Invoke<TResult(TArgs...)>::Dispatchable(*this, std::forward<TArgs>(args)...);
            }
        };
    }
}

#define RTTI_FUNCTION_RESULT(name) \
static void rtticall_##name(Techland::Runtime::Object* object, Techland::Runtime::StackFrame& frame) \
{ \
    using FunctionType = Techland::Runtime::DecayFunction<decltype(&this_class_t::name)>; \
    auto&& args = *reinterpret_cast<typename FunctionType::ArgsRef*>(frame.Params); \
    auto&& result = *reinterpret_cast<typename FunctionType::Result*>(frame.Result); \
    auto fn = std::mem_fn(&this_class_t::name); \
    result = std::apply(fn, std::tuple_cat(std::forward_as_tuple(*static_cast<this_class_t*>(object)), args)); \
}

#define RTTI_FUNCTION_VOID(name) \
static void rtticall_##name(Techland::Runtime::Object* object, Techland::Runtime::StackFrame& frame) \
{ \
    using FunctionType = Techland::Runtime::DecayFunction<decltype(&this_class_t::name)>; \
    auto&& args = *reinterpret_cast<typename FunctionType::ArgsRef*>(frame.Params); \
    auto fn = std::mem_fn(&this_class_t::name); \
    std::apply(fn, std::tuple_cat(std::forward_as_tuple(*static_cast<this_class_t*>(object)), args)); \
}


namespace Demo
{
    class Pawn : public Techland::Runtime::Object
    {
        using this_class_t = Pawn;
    public:
        Pawn();
        virtual ~Pawn();
        int32_t z;

    public:
        int32_t Add(int32_t x, int32_t y);
        RTTI_FUNCTION_RESULT(Add);

        void Signal();
        RTTI_FUNCTION_VOID(Signal);

    public:
        Techland::Runtime::Pipe<void(void)> SignalPipe;
        Techland::Runtime::Pipe<int32_t(int32_t, int32_t)> AddingPipe;
    };

    Techland::Runtime::Function rtti_Pawn_Signal{ &Pawn::rtticall_Signal, "Signal" };
    Techland::Runtime::Function rtti_Pawn_Add{ &Pawn::rtticall_Add, "Add" };


    Pawn::Pawn()
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        z = rand() & 15;

        SignalPipe.Owner = this;
        SignalPipe.Functions.push_back(&rtti_Pawn_Signal);

        AddingPipe.Owner = this;
        AddingPipe.Functions.push_back(&rtti_Pawn_Add);
    }

    Pawn::~Pawn() = default;

    int32_t Pawn::Add(int32_t x, int32_t y)
    {
        return x + y + z;
    }

    void Pawn::Signal()
    {
        //std::puts("signal!");
    }
    class SomeOtherObject : public Techland::Runtime::Object
    {
    public:
        virtual ~SomeOtherObject() = default;

        Techland::Runtime::Pipe<void(void)> SignalPipe;
        Techland::Runtime::Pipe<int32_t(int32_t, int32_t)> AddingPipe;
    };

    void Test()
    {
        Pawn pawn{};

        {
            int32_t a = 2;
            int32_t b = 3;

            [[maybe_unused]] auto result = Techland::Runtime::Invoke<int32_t(int32_t, int32_t)>::Function(&pawn, rtti_Pawn_Add, a, b);
        }
        {
            Techland::Runtime::Invoke<void(void)>::Function(&pawn, rtti_Pawn_Signal);
        }

        SomeOtherObject between1{};
        SomeOtherObject between2{};

        between1.AddingPipe.Pipes.push_back(&pawn.AddingPipe);
        between1.SignalPipe.Pipes.push_back(&pawn.SignalPipe);

        between2.AddingPipe.Pipes.push_back(&between1.AddingPipe);
        between2.SignalPipe.Pipes.push_back(&between1.SignalPipe);

        {
            int32_t a = 2;
            int32_t b = 3;

            [[maybe_unused]] auto result = between2.AddingPipe.Invoke(a, b);
        }
        {
            between2.SignalPipe.Invoke();
        }
    }
}

#ifndef TEST_CASE

int main()
{
    Demo::Test();
    return 0;
}

#else


TEST_CASE("Demo test")
{
    Demo::Test();
}

#endif
