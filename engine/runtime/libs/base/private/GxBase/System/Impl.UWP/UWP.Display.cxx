#include <GxBase/System.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>

#include "../Platform.impl.hxx"

namespace Graphyte::System
{
    BASE_API Status GetDisplayMetrics(
        DisplayMetrics& result
    ) noexcept
    {
        result = {};
        return Status::NotImplemented;
    }

    BASE_API DeviceScreenOrientation GetScreenOrientation() noexcept
    {
        return DeviceScreenOrientation::Landscape;
    }

    BASE_API ColorF GetScreenPixel(
        [[maybe_unused]] Point position,
        [[maybe_unused]] float gamma
    ) noexcept
    {
        return {};
    }

    BASE_API Status ControlScreensaver(
        bool enable
    ) noexcept
    {
        (void)enable;
        return Status::Success;
    }

    BASE_API void PreventScreensaver() noexcept
    {
    }
}
