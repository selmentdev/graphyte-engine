#include <Graphyte/System.hxx>
#include <Graphyte/Flags.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>
#include <Graphyte/String.hxx>
#include <Graphyte/Application.hxx>

#include <windowsx.h>
#undef IsMaximized
#undef IsMinimized

namespace Graphyte::Application::Impl
{
    ApplicationDescriptor GApplicationDescriptor{};
    bool GIsFirstInstance{ false };

    static bool GIsRequestingExit{ false };
    static Input::ModifierKeyState GApplicationModifierKeys{};
    static bool GApplicationActivateByMouse{};
    static bool GApplicationHighPrecisionMouse{};
    static bool GApplicationIsMouseAttached{};
    static EventHandler* GApplicationEventHandler{};
}

namespace Graphyte::Application
{
    BASE_API void Initialize() noexcept
    {
    }

    BASE_API void Finalize() noexcept
    {
    }

    BASE_API const ApplicationDescriptor& GetDescriptor() noexcept
    {
        return Impl::GApplicationDescriptor;
    }

    BASE_API bool IsFirstInstance() noexcept
    {
        return Impl::GIsFirstInstance;
    }

    BASE_API bool IsRequestingExit() noexcept
    {
        return Impl::GIsRequestingExit;
    }

    BASE_API void RequestExit(
        bool force
    ) noexcept
    {
        (void)force;
    }

    BASE_API bool IsForeground() noexcept
    {
        return false;
    }

    BASE_API void PollInputDevices(
        [[maybe_unused]] float deltaTime
    ) noexcept
    {
    }

    BASE_API void PumpMessages(
        [[maybe_unused]] float deltaTime
    ) noexcept
    {
        (void)deltaTime;
    }

    BASE_API void Tick(
        [[maybe_unused]] float deltaTime
    ) noexcept
    {
    }

    BASE_API void SetEventHandler(
        [[maybe_unused]] EventHandler* handler
    ) noexcept
    {
    }

    BASE_API EventHandler* GetEventHandler() noexcept
    {
        return Impl::GApplicationEventHandler;
    }

    BASE_API Window* CreateWindow(
        [[maybe_unused]] const WindowDescriptor& descriptor
    ) noexcept
    {
        return nullptr;
    }

    BASE_API void DestroyWindow(
        [[maybe_unused]] Window* window
    ) noexcept
    {
    }
}
