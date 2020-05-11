#include <GxBase/System.hxx>
#include <GxBase/Diagnostics.hxx>

#include "../Platform.impl.hxx"

#include <SDL2/SDL.h>

namespace Graphyte::System
{
    BASE_API Status GetBatteryState(
        BatteryState& state,
        int& level,
        int& lifetime
    ) noexcept
    {
        switch (SDL_GetPowerInfo(&lifetime, &level))
        {
        case SDL_POWERSTATE_UNKNOWN:
            {
                state = BatteryState::Unknown;
                return Status::Success;
            }

        case SDL_POWERSTATE_ON_BATTERY:
            {
                state = BatteryState::Disacharging;
                return Status::Success;
            }

        case SDL_POWERSTATE_NO_BATTERY:
            {
                state = BatteryState::NoBattery;
                return Status::Success;
            }

        case SDL_POWERSTATE_CHARGING:
            {
                state = BatteryState::Charging;
                return Status::Success;
            }

        case SDL_POWERSTATE_CHARGED:
            {
                state = BatteryState::Charged;
                return Status::Success;
            }
        }

        return Status::Failure;
    }
}
