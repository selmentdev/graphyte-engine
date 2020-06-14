#include "VulkanGpuOcclusionQuery.hxx"
#include "VulkanGpuCommandList.hxx"

namespace Graphyte::Graphics
{
    void VulkanGpuCommandList::BeginOcclusionQuery(
        [[maybe_unused]] GpuOcclusionQueryHandle handle) noexcept
    {
    }

    void VulkanGpuCommandList::EndOcclusionQuery(
        [[maybe_unused]] GpuOcclusionQueryHandle handle) noexcept
    {
    }

    bool VulkanGpuCommandList::GetOcclusionQueryResult(
        [[maybe_unused]] GpuOcclusionQueryHandle handle,
        [[maybe_unused]] uint64_t& result,
        [[maybe_unused]] bool wait) noexcept
    {
        return false;
    }
}
