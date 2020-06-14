#include <GxBase/Application.hxx>

#include "../Platform.impl.hxx"

#include <SDL2/SDL.h>

namespace Graphyte::System::Impl
{
    void InitializePlatform() noexcept
    {
        //
        // Initialize SDL.
        //

        if (Application::GetDescriptor().Type != Application::ApplicationType::ConsoleTool && Application::GetDescriptor().Type != Application::ApplicationType::UnitTest)
        {
            if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            {
                GX_ASSERTF(false, "SDL Initialization failure: `{}`", SDL_GetError());
            }

#if GRAPHYTE_CONFIG_DO_ASSERT
            auto const initialized_subsystems = SDL_WasInit(SDL_INIT_EVERYTHING);
            GX_ASSERTF((initialized_subsystems & SDL_INIT_EVENTS) != 0, "SDL_INIT_EVENTS not initialized");
            GX_ASSERTF((initialized_subsystems & SDL_INIT_JOYSTICK) != 0, "SDL_INIT_JOYSTICK not initialized");
            GX_ASSERTF((initialized_subsystems & SDL_INIT_GAMECONTROLLER) != 0, "SDL_INIT_GAMECONTROLLER not initialized");
#endif
        }

        SDL_version linked_version{};
        SDL_GetVersion(&linked_version);

        GX_LOG(LogPlatform, Info, "SDL Version linked: {}.{}.{}\n",
            linked_version.major, linked_version.minor, linked_version.patch);

        SDL_version compiled_version{};
        SDL_VERSION(&compiled_version);

        GX_LOG(LogPlatform, Info, "SDL Version compiled: {}.{}.{}\n",
            compiled_version.major, compiled_version.minor, compiled_version.patch);
    }

    void FinalizePlatform() noexcept
    {
        GX_ASSERT_SINGLE_CALL();

        if (Application::GetDescriptor().Type != Application::ApplicationType::ConsoleTool && Application::GetDescriptor().Type != Application::ApplicationType::UnitTest)
        {
            SDL_Quit();
        }
    }
}
