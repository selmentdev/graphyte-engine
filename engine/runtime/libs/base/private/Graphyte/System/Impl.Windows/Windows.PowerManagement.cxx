#include "Base.pch.hxx"
#include <Graphyte/System.hxx>
#include <Graphyte/Diagnostics.hxx>

#include "../Platform.impl.hxx"

namespace Graphyte::System
{
    BASE_API Status GetBatteryState(
        BatteryState& state,
        int& level,
        int& lifetime
    ) noexcept
    {
        Status result = Status::Success;

        //
        // https://msdn.microsoft.com/en-us/library/windows/desktop/aa373232%28v=vs.85%29.aspx
        //

        SYSTEM_POWER_STATUS system_power_status = {};

        if (GetSystemPowerStatus(&system_power_status) == FALSE)
        {
            state = BatteryState::Unknown;

            //
            // Failed to get actual battery state.
            //
            // Translate error to status code.
            //

            result = Diagnostics::GetStatusFromSystemError();
        }
        else if (system_power_status.BatteryFlag == BATTERY_FLAG_UNKNOWN)
        {
            state = BatteryState::Unknown;
        }
        else if (system_power_status.BatteryFlag & BATTERY_FLAG_NO_BATTERY)
        {
            state = BatteryState::NoBattery;
        }
        else if (system_power_status.BatteryFlag & BATTERY_FLAG_CHARGING)
        {
            state = BatteryState::Charging;
        }
        else if (system_power_status.ACLineStatus == AC_LINE_ONLINE)
        {
            state = BatteryState::Charged;
        }
        else
        {
            state = BatteryState::Disacharging;
        }

        if (BYTE percent = system_power_status.BatteryLifePercent; percent != BATTERY_PERCENTAGE_UNKNOWN)
        {
            level = std::min<int>(percent, 100);
        }
        else
        {
            level = -1;
        }

        if (DWORD seconds = system_power_status.BatteryLifeTime; seconds != BATTERY_LIFE_UNKNOWN)
        {
            lifetime = static_cast<int>(seconds);
        }
        else
        {
            lifetime = -1;
        }

        return result;
    }
}
