#include <GxBase/System.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>

#include "../Platform.impl.hxx"

namespace Graphyte::System::Impl
{
    static BOOL CALLBACK AcquireMonitorInfo(
        HMONITOR monitor,
        HDC monitor_dc [[maybe_unused]],
        LPRECT rect [[maybe_unused]],
        LPARAM context) noexcept
    {
        MONITORINFOEXW miex{
            {
                .cbSize = sizeof(MONITORINFOEXW),
            }
        };

        GetMonitorInfoW(monitor, &miex);

        DisplayInfo& info = *reinterpret_cast<DisplayInfo*>(context);

        if (Impl::WidenString(info.Name) == miex.szDevice)
        {
            info.DisplayRect = {
                miex.rcMonitor.left,
                miex.rcMonitor.top,
                miex.rcMonitor.right - miex.rcMonitor.left,
                miex.rcMonitor.bottom - miex.rcMonitor.top,
            };

            info.WorkAreaRect = {
                miex.rcWork.left,
                miex.rcWork.top,
                miex.rcWork.right - miex.rcWork.left,
                miex.rcWork.bottom - miex.rcWork.top,
            };

            return FALSE;
        }

        return TRUE;
    }
}

namespace Graphyte::System
{
    BASE_API Status GetDisplayMetrics(
        DisplayMetrics& result) noexcept
    {
        //
        // Get primary display size.
        //

        result.PrimaryDisplaySize = {
            GetSystemMetrics(SM_CXSCREEN),
            GetSystemMetrics(SM_CYSCREEN),
        };


        //
        // Get work area rect.
        //

        RECT work_area = { -1, -1, -1, -1 };

        if (!SystemParametersInfoW(SPI_GETWORKAREA, 0, &work_area, 0))
        {
            work_area = {};
        }

        result.PrimaryDisplayWorkArea = {
            work_area.left,
            work_area.top,
            work_area.right - work_area.left,
            work_area.bottom - work_area.top,
        };


        //
        // Get virtual display rect.
        //

        result.VirtualDisplayRect = {
            GetSystemMetrics(SM_XVIRTUALSCREEN),
            GetSystemMetrics(SM_YVIRTUALSCREEN),
            GetSystemMetrics(SM_CXVIRTUALSCREEN),
            GetSystemMetrics(SM_CYVIRTUALSCREEN),
        };

        //
        // Get displays.
        //

        result.Displays.clear();

        DISPLAY_DEVICEW device{
            .cb = sizeof(device),
        };

        for (DWORD device_id{ 0 }; EnumDisplayDevicesW(nullptr, device_id, &device, 0) != FALSE; ++device_id)
        {
            if ((device.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) != 0)
            {
                DISPLAY_DEVICEW monitor{
                    .cb = sizeof(monitor),
                };

                for (DWORD monitor_id{ 0 }; EnumDisplayDevicesW(device.DeviceName, monitor_id, &monitor, 0) != FALSE; ++monitor_id)
                {
                    if ((monitor.StateFlags & DISPLAY_DEVICE_ACTIVE) && !(monitor.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER))
                    {
                        DisplayInfo display_info{};

                        display_info.Name    = Impl::NarrowString(device.DeviceName);
                        display_info.Id      = Impl::NarrowString(monitor.DeviceID);
                        display_info.Primary = (device.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) != 0;

                        EnumDisplayMonitors(nullptr, nullptr, Impl::AcquireMonitorInfo, reinterpret_cast<LPARAM>(&display_info));

                        result.Displays.push_back(display_info);
                    }
                }
            }
        }

        return Status::Success;
    }

    BASE_API DeviceScreenOrientation GetScreenOrientation() noexcept
    {
        return DeviceScreenOrientation::Landscape;
    }

    BASE_API ColorF GetScreenPixel(
        Point position,
        float gamma) noexcept
    {
        COLORREF const pixel = GetPixel(
            GetDC(HWND_DESKTOP),
            position.Left,
            position.Top);

        float const divisor   = 1.0F / 255.0F;
        float const channel_r = divisor * static_cast<float>(static_cast<uint8_t>(pixel));
        float const channel_g = divisor * static_cast<float>(static_cast<uint8_t>(pixel >> 8));
        float const channel_b = divisor * static_cast<float>(static_cast<uint8_t>(pixel >> 16));

        float const gamma_value = std::max(gamma, 1.0F);

        return ColorF{
            std::pow(channel_r, gamma_value),
            std::pow(channel_g, gamma_value),
            std::pow(channel_b, gamma_value),
            1.0F
        };
    }

    BASE_API Status ControlScreensaver(
        bool enable) noexcept
    {
        (void)enable;
        return Status::Success;
    }

    BASE_API void PreventScreensaver() noexcept
    {
        INPUT input{
            .type = INPUT_MOUSE,
            .mi   = {
                .dx          = 0,
                .dy          = 0,
                .mouseData   = 0,
                .dwFlags     = MOUSEEVENTF_MOVE,
                .time        = 0,
                .dwExtraInfo = 0,
            }
        };

        SendInput(
            1,
            &input,
            sizeof(input));
    }
}
