#include <GxBase/Application.hxx>
#include <GxGraphics/Graphics/Gpu/GpuVertex.hxx>

#include "VulkanGpuCommandList.hxx"
#include "VulkanGpuDevice.hxx"

#if GRAPHYTE_PLATFORM_LINUX
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <X11/Xlib-xcb.h>
#endif

namespace Graphyte::Graphics
{
#if false
    static const std::array<VkVertexInputAttributeDescription, 6> VK_VertexInput_GpuVertexComplex{
        {
            { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(GpuVertexComplex, Position) },
            { 0, 1, VK_FORMAT_R8G8B8A8_SNORM, offsetof(GpuVertexComplex, Normal) },
            { 0, 2, VK_FORMAT_R8G8B8A8_SNORM, offsetof(GpuVertexComplex, Tangent) },
            { 0, 3, VK_FORMAT_R16G16_SFLOAT, offsetof(GpuVertexComplex, UV[0]) },
            { 0, 4, VK_FORMAT_R16G16_SFLOAT, offsetof(GpuVertexComplex, UV[1]) },
            { 0, 5, VK_FORMAT_R8G8B8A8_UNORM, offsetof(GpuVertexComplex, Color) },
        }
    };
#endif

    struct VulkanGpuUtils final
    {
        static VkResult CreateDebugUtilsMessenger(
            VkInstance instance,
            const VkDebugUtilsMessengerCreateInfoEXT* createInfo,
            const VkAllocationCallbacks* allocator,
            VkDebugUtilsMessengerEXT* callback) noexcept
        {
            auto fn = VKGetFunction<PFN_vkCreateDebugUtilsMessengerEXT>(
                instance,
                "vkCreateDebugUtilsMessengerEXT");

            if (fn != nullptr)
            {
                return fn(
                    instance,
                    createInfo,
                    allocator,
                    callback);
            }
            else
            {
                return VK_ERROR_EXTENSION_NOT_PRESENT;
            }
        }

        static void DestroyDebugUtilsMessenger(
            VkInstance instance,
            VkDebugUtilsMessengerEXT callback,
            const VkAllocationCallbacks* allocator) noexcept
        {
            auto fn = VKGetFunction<PFN_vkDestroyDebugUtilsMessengerEXT>(
                instance,
                "vkDestroyDebugUtilsMessengerEXT");

            if (fn != nullptr)
            {
                fn(
                    instance,
                    callback,
                    allocator);
            }
        }

        static VkResult CreateDebugReportCallback(
            VkInstance instance,
            const VkDebugReportCallbackCreateInfoEXT* createInfo,
            const VkAllocationCallbacks* allocator,
            VkDebugReportCallbackEXT* callback) noexcept
        {
            auto fn = VKGetFunction<PFN_vkCreateDebugReportCallbackEXT>(
                instance,
                "vkCreateDebugReportCallbackEXT");

            if (fn != nullptr)
            {
                return fn(
                    instance,
                    createInfo,
                    allocator,
                    callback);
            }
            else
            {
                return VK_ERROR_EXTENSION_NOT_PRESENT;
            }
        }

        static void DestroyDebugReportCallback(
            VkInstance instance,
            VkDebugReportCallbackEXT callback,
            const VkAllocationCallbacks* allocator) noexcept
        {
            auto fn = VKGetFunction<PFN_vkDestroyDebugReportCallbackEXT>(
                instance,
                "vkDestroyDebugReportCallbackEXT");

            if (fn != nullptr)
            {
                fn(
                    instance,
                    callback,
                    allocator);
            }
        }

        struct QueueFamilyIndices final
        {
            std::optional<uint32_t> GraphicsFamily;
            std::optional<uint32_t> ComputeFamily;

            bool IsComplete() const noexcept
            {
                return GraphicsFamily.has_value() && ComputeFamily.has_value();
            }
        };

        static QueueFamilyIndices GetQueueFamilies(
            VkPhysicalDevice device) noexcept
        {
            QueueFamilyIndices result{};

            uint32_t count{};
            vkGetPhysicalDeviceQueueFamilyProperties(
                device,
                &count,
                nullptr);

            std::vector<VkQueueFamilyProperties> properties(count);
            vkGetPhysicalDeviceQueueFamilyProperties(
                device,
                &count,
                std::data(properties));

            for (uint32_t i = 0; i < static_cast<uint32_t>(properties.size()); ++i)
            {
                auto const& family = properties[i];

                if (family.queueCount > 0 && family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                {
                    result.GraphicsFamily = i;
                }

                if (family.queueCount > 0 && family.queueFlags & VK_QUEUE_COMPUTE_BIT)
                {
                    result.ComputeFamily = i;
                }

                if (result.IsComplete())
                {
                    break;
                }
            }

            return result;
        }

        struct SwapChainSupportDetails final
        {
            VkSurfaceCapabilitiesKHR Capabilities;
            std::vector<VkSurfaceFormatKHR> Formats;
            std::vector<VkPresentModeKHR> PresentModes;
        };

        static SwapChainSupportDetails GetSwapChainSupportDetails(
            VkPhysicalDevice device,
            VkSurfaceKHR surface) noexcept
        {
            SwapChainSupportDetails result{};

            GPU_VK_VALIDATE(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
                device,
                surface,
                &result.Capabilities));

            uint32_t formatCount{};
            GPU_VK_VALIDATE(vkGetPhysicalDeviceSurfaceFormatsKHR(
                device,
                surface,
                &formatCount,
                nullptr));

            return result;
        }
    };


    VKAPI_ATTR VkBool32 VKAPI_CALL VulkanGpuDevice::DebugCallback(
        VkDebugReportFlagsEXT flags,
        VkDebugReportObjectTypeEXT objType,
        uint64_t obj,
        size_t location,
        int32_t code,
        const char* layerPrefix,
        const char* msg,
        void* userData) noexcept
    {
        (void)flags;
        (void)objType;
        (void)obj;
        (void)location;
        (void)code;
        (void)layerPrefix;
        (void)msg;
        (void)userData;

        GX_LOG_TRACE(LogVkRender, "Validation: {}\n", msg);
        return VK_FALSE;
    }

    struct QueueFamilyIndices final
    {
        std::optional<uint32_t> GraphicsFamily;
        std::optional<uint32_t> ComputeFamily;

        bool IsComplete() const noexcept
        {
            return GraphicsFamily.has_value() && ComputeFamily.has_value();
        }
    };

    static QueueFamilyIndices FindQueueFamilies(
        VkPhysicalDevice device)
    {
        QueueFamilyIndices indices{};

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(
            device,
            &queueFamilyCount,
            nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(
            device,
            &queueFamilyCount,
            queueFamilies.data());

        uint32_t i = 0;
        for (const auto& queueFamily : queueFamilies)
        {
            if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                indices.GraphicsFamily = i;
            }

            if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
            {
                indices.ComputeFamily = i;
            }

            if (indices.IsComplete())
            {
                break;
            }

            i++;
        }

        return indices;
    }

    VulkanGpuDevice::VulkanGpuDevice() noexcept
    {
        //
        // Get extensions count.
        //
        uint32_t extension_count{};
        GPU_VK_VALIDATE(vkEnumerateInstanceExtensionProperties(
            nullptr,
            &extension_count,
            nullptr));

        //
        // Extensions.
        //
        const char* extensions[]
        {
            VK_KHR_SURFACE_EXTENSION_NAME,
#if GRAPHYTE_PLATFORM_WINDOWS
                VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#endif
#if GRAPHYTE_PLATFORM_LINUX
                VK_KHR_XCB_SURFACE_EXTENSION_NAME,
#endif
                VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
            //VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME,
            //VK_KHR_DEDICATED_ALLOCATION_EXTENSION_NAME,
        };

        //
        // Validation layers.
        //
        static const char* validation_layers[] = {
            "VK_LAYER_LUNARG_standard_validation"
        };

        uint32_t layer_count{};
        GPU_VK_VALIDATE(vkEnumerateInstanceLayerProperties(
            &layer_count,
            nullptr));

        std::vector<VkLayerProperties> available_layers(layer_count);
        GPU_VK_VALIDATE(vkEnumerateInstanceLayerProperties(
            &layer_count,
            std::data(available_layers)));

        for (auto const& layer : validation_layers)
        {
            bool found = false;

            for (auto const& properties : available_layers)
            {
                if (std::string_view{ layer } == std::string_view{ properties.layerName })
                {
                    found = true;
                }
            }

            GX_ABORT_UNLESS(found, "Cannot enable Vulkan validation layer: {}", layer);
        }


        //
        // Fill application info.
        //

        VkApplicationInfo application_info{
            .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pApplicationName   = "Graphyte Engine",
            .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
            .pEngineName        = "Graphyte Engine",
            .engineVersion      = VK_MAKE_VERSION(1, 0, 0),
            .apiVersion         = VK_API_VERSION_1_1,
        };


        //
        // Create instance.
        //

        VkInstanceCreateInfo create_info{
            .sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pApplicationInfo        = &application_info,
            .enabledLayerCount       = static_cast<uint32_t>(std::size(validation_layers)),
            .ppEnabledLayerNames     = std::data(validation_layers),
            .enabledExtensionCount   = static_cast<uint32_t>(std::size(extensions)),
            .ppEnabledExtensionNames = std::data(extensions),
        };

        for (auto const& extension : extensions)
        {
            GX_LOG_TRACE(LogVkRender, "Extension: {}\n", extension);
        }

        for (auto const& layer : validation_layers)
        {
            GX_LOG_TRACE(LogVkRender, "Layer: {}\n", layer);
        }

        GPU_VK_VALIDATE(vkCreateInstance(
            &create_info,
            nullptr,
            &m_Instance));

        VkDebugReportCallbackCreateInfoEXT debug_callback_report{
            .sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT,
            .flags = VK_DEBUG_REPORT_INFORMATION_BIT_EXT
                     | VK_DEBUG_REPORT_WARNING_BIT_EXT
                     | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT
                     | VK_DEBUG_REPORT_ERROR_BIT_EXT
                     | VK_DEBUG_REPORT_DEBUG_BIT_EXT,
            .pfnCallback = &VulkanGpuDevice::DebugCallback,
        };

        {
            auto callback = VKGetFunction<PFN_vkCreateDebugReportCallbackEXT>(
                m_Instance,
                "vkCreateDebugReportCallbackEXT");

            GPU_VK_VALIDATE(callback(
                m_Instance,
                &debug_callback_report,
                nullptr,
                &m_DebugCallback));
        }

        //
        // Get devices
        //

        uint32_t device_count{};
        GPU_VK_VALIDATE(vkEnumeratePhysicalDevices(
            m_Instance,
            &device_count,
            nullptr));

        std::vector<VkPhysicalDevice> devices{ device_count };
        GPU_VK_VALIDATE(vkEnumeratePhysicalDevices(
            m_Instance,
            &device_count,
            std::data(devices)));

        for (auto const& device : devices)
        {
            VkPhysicalDeviceProperties device_properties;

            vkGetPhysicalDeviceProperties(
                device,
                &device_properties);
            VkPhysicalDeviceFeatures device_features;
            vkGetPhysicalDeviceFeatures(
                device,
                &device_features);

            GX_LOG_TRACE(LogVkRender,
                "Device: ({:04x} {:04x} {}) - {}\n",
                static_cast<uint32_t>(device_properties.vendorID),
                static_cast<uint32_t>(device_properties.deviceID),
                static_cast<uint32_t>(device_properties.deviceType),
                device_properties.deviceName);

            if (device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && device_features.geometryShader)
            {
                GX_LOG_TRACE(LogVkRender, "Found device: {}\n", device_properties.deviceName);
                m_PhysicalDevice = device;
                break;
            }
        }

        GX_ABORT_UNLESS(m_PhysicalDevice != nullptr, "Failed to determine Vulkan physical device");

        auto const& indices = FindQueueFamilies(
            m_PhysicalDevice);

        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType                   = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex        = indices.GraphicsFamily.value();
        queueCreateInfo.queueCount              = 1;

        float queuePriority              = 1.0F;
        queueCreateInfo.pQueuePriorities = &queuePriority;

        VkPhysicalDeviceFeatures deviceFeatures = {};

        VkDeviceCreateInfo createInfo = {};
        createInfo.sType              = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        createInfo.pQueueCreateInfos    = &queueCreateInfo;
        createInfo.queueCreateInfoCount = 1;

        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = 0;

        //if (enableValidationLayers)
        {
            createInfo.enabledLayerCount   = static_cast<uint32_t>(std::size(validation_layers));
            createInfo.ppEnabledLayerNames = std::data(validation_layers);
        }
        //else
        //{
        //    createInfo.enabledLayerCount = 0;
        //}

        GPU_VK_VALIDATE(vkCreateDevice(
            m_PhysicalDevice,
            &createInfo,
            nullptr,
            &m_Device));

        vkGetDeviceQueue(
            m_Device,
            indices.GraphicsFamily.value(),
            0,
            &m_GraphicsQueue);

        VmaAllocatorCreateInfo allocatorInfo{};
        allocatorInfo.flags                       = 0; // VMA_ALLOCATOR_CREATE_KHR_DEDICATED_ALLOCATION_BIT;
        allocatorInfo.physicalDevice              = m_PhysicalDevice;
        allocatorInfo.device                      = m_Device;
        allocatorInfo.preferredLargeHeapBlockSize = 0;
        allocatorInfo.pAllocationCallbacks        = nullptr;
        allocatorInfo.pDeviceMemoryCallbacks      = nullptr;
        allocatorInfo.frameInUseCount             = 0;
        allocatorInfo.pHeapSizeLimit              = nullptr;
        allocatorInfo.pVulkanFunctions            = nullptr;

        GPU_VK_VALIDATE(vmaCreateAllocator(
            &allocatorInfo,
            &m_Allocator));

        m_CommandList = new VulkanGpuCommandList();

        vkGetDeviceQueue(
            m_Device,
            indices.GraphicsFamily.value(),
            0,
            &m_GraphicsQueue);

        vkGetDeviceQueue(
            m_Device,
            indices.ComputeFamily.value(),
            0,
            &m_ComputeQueue);
    }

    VulkanGpuDevice::~VulkanGpuDevice() noexcept
    {
        delete m_CommandList;

        vmaDestroyAllocator(
            m_Allocator);

        vkDestroyDevice(
            m_Device,
            nullptr);

        {
            auto callback = VKGetFunction<PFN_vkDestroyDebugReportCallbackEXT>(
                m_Instance,
                "vkDestroyDebugReportCallbackEXT");

            callback(
                m_Instance,
                m_DebugCallback,
                nullptr);
        }

        vkDestroyInstance(
            m_Instance,
            nullptr);
    }

    void VulkanGpuDevice::Tick(
        float time) noexcept
    {
        (void)time;
    }
}
