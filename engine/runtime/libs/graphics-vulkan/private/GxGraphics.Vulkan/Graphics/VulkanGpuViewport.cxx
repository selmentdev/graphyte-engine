#include <GxBase/Application.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/System.hxx>

#include "VulkanGpuViewport.hxx"
#include "VulkanGpuDevice.hxx"

#if GX_PLATFORM_LINUX
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <X11/Xlib-xcb.h>
#include <SDL2/SDL_vulkan.h>
#endif

namespace Graphyte::Graphics
{
    GpuViewportHandle VulkanGpuDevice::CreateViewport(
        void* native_handle,
        uint32_t width,
        uint32_t height,
        bool fullscreen,
        PixelFormat color_format,
        PixelFormat depth_format,
        GpuMsaaQuality msaa) noexcept
    {
#if GX_PLATFORM_LINUX

        auto* sdl_window = reinterpret_cast<SDL_Window*>(native_handle);


        SDL_SysWMinfo window_info;
        SDL_VERSION(&window_info.version);

        GX_ENSURE(SDL_GetWindowWMInfo(
                      sdl_window,
                      &window_info)
                  == SDL_TRUE);

        VkXcbSurfaceCreateInfoKHR create_info{};
        create_info.sType      = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
        create_info.connection = XGetXCBConnection(window_info.info.x11.display);

        // Does this static_cast is required?
        create_info.window = static_cast<xcb_window_t>(window_info.info.x11.window);

        auto create_surface_khr = VKGetFunction<PFN_vkCreateXcbSurfaceKHR>(
            m_Instance,
            "vkCreateXcbSurfaceKHR");

        GX_ASSERT(create_surface_khr != nullptr);

        VkSurfaceKHR surface{};

        GPU_VK_VALIDATE(create_surface_khr(
            m_Instance,
            &create_info,
            nullptr,
            &surface));

#elif GX_PLATFORM_WINDOWS

        VkWin32SurfaceCreateInfoKHR create_info{};
        create_info.sType     = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        create_info.hinstance = System::Impl::g_InstanceHandle;
        create_info.hwnd      = reinterpret_cast<HWND>(native_handle);

        auto create_surface_khr = VKGetFunction<PFN_vkCreateWin32SurfaceKHR>(
            m_Instance,
            "vkCreateWin32SurfaceKHR");

        GX_ASSERT(create_surface_khr != nullptr);

        VkSurfaceKHR surface{};
        GPU_VK_VALIDATE(create_surface_khr(
            m_Instance,
            &create_info,
            nullptr,
            &surface));

#endif
        (void)native_handle;
        (void)width;
        (void)height;
        (void)fullscreen;
        (void)color_format;
        (void)depth_format;
        (void)msaa;

#if false
        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = surface;
#endif

        auto native     = new VulkanGpuViewport();
        native->Surface = surface;
        //native->

        return native;
    }

    void VulkanGpuDevice::DestroyViewport(
        GpuViewportHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<VulkanGpuViewport*>(handle);

        vkDestroySurfaceKHR(
            m_Instance,
            native->Surface,
            nullptr);
    }

    void VulkanGpuDevice::ResizeViewport(
        GpuViewportHandle handle,
        uint32_t width,
        uint32_t height,
        bool fullscreen,
        PixelFormat format) noexcept
    {
        (void)handle;
        (void)width;
        (void)height;
        (void)fullscreen;
        (void)format;
    }

    void VulkanGpuDevice::BeginDrawViewport(
        GpuViewportHandle handle) noexcept
    {
        (void)handle;
    }

    void VulkanGpuDevice::EndDrawViewport(
        GpuViewportHandle handle,
        bool present,
        int interval) noexcept
    {
        (void)handle;
        (void)present;
        (void)interval;
    }
}
