#include <Graphyte/System.hxx>
#include <Graphyte/Maths.hxx>
//#include <Graphyte/Math/Scalar.hxx>

#include "../Platform.impl.hxx"

#include <SDL2/SDL.h>

namespace Graphyte::System
{
    BASE_API Status GetDisplayMetrics(
        DisplayMetrics& result
    ) noexcept
    {

        int32_t displays_count = SDL_GetNumVideoDisplays();

        result.Displays.clear();

        if (displays_count > 0)
        {
            int32_t virtual_span_l = {};
            int32_t virtual_span_t = {};
            int32_t virtual_span_r = {};
            int32_t virtual_span_b = {};

            for (int32_t index = 0; index < displays_count; ++index)
            {
                SDL_Rect display_bounds{};
                SDL_GetDisplayBounds(index, &display_bounds);

                SDL_Rect usable_bounds{};
                SDL_GetDisplayUsableBounds(index, &usable_bounds);

                DisplayInfo display{};
                display.Name = SDL_GetDisplayName(index);
                display.Id = fmt::format("display{}", index);
                display.DisplayRect = {
                    display_bounds.x,
                    display_bounds.y,
                    display_bounds.w,
                    display_bounds.h,
                };
                display.WorkAreaRect = {
                    usable_bounds.x,
                    usable_bounds.y,
                    usable_bounds.w,
                    usable_bounds.h,
                };
                display.Primary = (index == 0);

                result.Displays.push_back(display);

                if (display.Primary)
                {
                    result.PrimaryDisplayWorkArea = display.WorkAreaRect;
                    result.PrimaryDisplaySize = {
                        display_bounds.w,
                        display_bounds.h,
                    };

                    virtual_span_l = result.PrimaryDisplayWorkArea.Left;
                    virtual_span_t = result.PrimaryDisplayWorkArea.Top;
                    virtual_span_r = result.PrimaryDisplayWorkArea.Left + result.PrimaryDisplayWorkArea.Width;
                    virtual_span_b = result.PrimaryDisplayWorkArea.Top + result.PrimaryDisplayWorkArea.Height;
                }
                else
                {
                    virtual_span_l = std::min(display_bounds.x, virtual_span_l);
                    virtual_span_t = std::min(display_bounds.y, virtual_span_t);
                    virtual_span_r = std::max(display_bounds.x + display_bounds.w, virtual_span_r);
                    virtual_span_b = std::max(display_bounds.y + display_bounds.h, virtual_span_b);
                }
            }

            result.VirtualDisplayRect = {
                virtual_span_l,
                virtual_span_t,
                virtual_span_r - virtual_span_l,
                virtual_span_b - virtual_span_t,
            };
        }
        else
        {
            result.PrimaryDisplaySize = {};
            result.PrimaryDisplayWorkArea = {};
            result.VirtualDisplayRect = {};
        }

        return Status::Success;
    }

    BASE_API DeviceScreenOrientation GetScreenOrientation() noexcept
    {
        return DeviceScreenOrientation::Landscape;
    }

    BASE_API ColorF GetScreenPixel(
        Point position,
        float gamma
    ) noexcept
    {
        (void)position;
        (void)gamma;
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
