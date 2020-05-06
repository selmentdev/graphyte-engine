#include "D3D11GpuDevice.hxx"
#include "D3D11GpuUniformBuffer.hxx"
#include <GxBase/Bitwise.hxx>
#include <GxBase/Flags.hxx>

namespace Graphyte::Graphics
{
    GpuUniformBufferHandle D3D11GpuDevice::CreateUniformBuffer(
        size_t size,
        GpuBufferUsage usage,
        const GpuSubresourceData* subresource
    ) noexcept
    {
        GX_ASSERT(size != 0);
        GX_ASSERTF(Graphyte::IsAligned<size_t>(size, 16), "Uniform buffer must be 16 bytes aligned");

        D3D11_BUFFER_DESC desc{
            .ByteWidth = static_cast<UINT>(size),
            .Usage = Flags::Any(usage, GpuBufferUsage::AnyDynamic) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT,
            .BindFlags = D3D11_BIND_CONSTANT_BUFFER,
            .CPUAccessFlags = Flags::Any(usage, GpuBufferUsage::AnyDynamic) ? D3D11_CPU_ACCESS_WRITE : UINT{},
        };

        D3D11_SUBRESOURCE_DATA init_data{};
        D3D11_SUBRESOURCE_DATA* native_data = nullptr;

        if (subresource != nullptr)
        {
            GX_ASSERT(size == subresource->Pitch);

            init_data = {
                .pSysMem = subresource->Memory,
                .SysMemPitch = static_cast<UINT>(size),
                .SysMemSlicePitch = 0,
            };

            native_data = &init_data;
        }

        ID3D11Buffer* buffer{};

        GPU_DX_VALIDATE(m_Device->CreateBuffer(
            &desc,
            native_data,
            &buffer
        ));

        auto result = new D3D11GpuUniformBuffer{};
        result->m_Resource = buffer;
        result->m_Size = static_cast<UINT>(size);
        result->m_Usage = usage;
        return result;
    }

    void D3D11GpuDevice::DestroyUniformBuffer(
        GpuUniformBufferHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuUniformBuffer*>(handle);
        GX_ASSERT(native->m_Resource != nullptr);

        this->DeferResourceRelease(native->m_Resource);
        delete native;
    }

    void* D3D11GpuDevice::LockUniformBuffer(
        GpuUniformBufferHandle handle,
        uint32_t offset,
        uint32_t size,
        GpuResourceLockMode lock_mode
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuUniformBuffer*>(handle);

        GX_ASSERT(native->m_Resource != nullptr);

        GX_ASSERT(size != 0);

        D3D11_BUFFER_DESC desc{};
        native->m_Resource->GetDesc(&desc);

        bool const is_dynamic = desc.Usage == D3D11_USAGE_DYNAMIC;

        D3D11GpuResourceLockKey key{ native->m_Resource };
        D3D11GpuResourceLockData data{};

        if (is_dynamic)
        {
            GX_ASSERT(lock_mode == GpuResourceLockMode::WriteOnly);

            D3D11_MAPPED_SUBRESOURCE mapped{};
            GPU_DX_VALIDATE(m_Context->Map(
                native->m_Resource,
                0,
                D3D11_MAP_WRITE_DISCARD,
                0,
                &mapped
            ));

            data.SetData(mapped.pData);
            data.Pitch = mapped.RowPitch;
            data.DepthPitch = mapped.DepthPitch;
        }
        else
        {
            if (lock_mode == GpuResourceLockMode::ReadOnly)
            {
                D3D11_BUFFER_DESC staging{
                    .ByteWidth = size,
                    .Usage = D3D11_USAGE_STAGING,
                    .BindFlags = 0,
                    .CPUAccessFlags = D3D11_CPU_ACCESS_READ,
                    .MiscFlags = 0,
                };

                Microsoft::WRL::ComPtr<ID3D11Buffer> staging_buffer{};
                GPU_DX_VALIDATE(m_Device->CreateBuffer(
                    &staging,
                    nullptr,
                    staging_buffer.GetAddressOf()
                ));

                data.StagingResource = staging_buffer;

                D3D11_BOX box{
                    .left = offset,
                    .top = box.front = 0,
                    .right = size,
                    .bottom = box.back = 1,
                };

                m_Context->CopySubresourceRegion(
                    staging_buffer.Get(),
                    0,
                    0,
                    0,
                    0,
                    native->m_Resource,
                    0,
                    &box
                );

                D3D11_MAPPED_SUBRESOURCE mapped{};

                GPU_DX_VALIDATE(m_Context->Map(
                    staging_buffer.Get(),
                    0,
                    D3D11_MAP_READ,
                    0,
                    &mapped
                ));

                data.SetData(mapped.pData);
                data.Pitch = mapped.RowPitch;
                data.DepthPitch = mapped.DepthPitch;
            }
            else
            {
                data.Allocate(desc.ByteWidth);
                data.Pitch = desc.ByteWidth;
            }
        }

        [[maybe_unused]] auto result = m_ResourceLocks.insert(std::make_pair(key, data));
        GX_ASSERT(result.second == true);

        return (void*)((uint8_t*)data.GetData() + offset);
    }

    void D3D11GpuDevice::UnlockUniformBuffer(
        GpuUniformBufferHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuUniformBuffer*>(handle);

        D3D11_BUFFER_DESC desc{};
        native->m_Resource->GetDesc(&desc);

        bool const is_dynamic = desc.Usage == D3D11_USAGE_DYNAMIC;

        D3D11GpuResourceLockKey key{ native->m_Resource };

        auto data = m_ResourceLocks.find(key);
        GX_ASSERT(data != m_ResourceLocks.end());

        if (is_dynamic)
        {
            m_Context->Unmap(native->m_Resource, 0);
        }
        else
        {
            auto& staging = data->second;
            if (staging.StagingResource != nullptr)
            {
                ID3D11Buffer* staging_buffer = (ID3D11Buffer*)staging.StagingResource.Get();
                m_Context->Unmap(
                    staging_buffer,
                    0
                );
            }
            else
            {
                m_Context->UpdateSubresource(
                    native->m_Resource,
                    key.Subresource,
                    nullptr,
                    staging.GetData(),
                    staging.Pitch,
                    0
                );

                staging.DeallocateData();
            }
        }

        m_ResourceLocks.erase(data);
    }
    
    void D3D11GpuDevice::CopyUniformBuffer(
        GpuUniformBufferHandle source,
        GpuUniformBufferHandle destination
    ) noexcept
    {
        auto native_source = static_cast<D3D11GpuUniformBuffer*>(source);
        auto native_destination = static_cast<D3D11GpuUniformBuffer*>(destination);

#if ENABLE_GPU_API_DEBUG
        D3D11_BUFFER_DESC source_desc{};
        native_source->m_Resource->GetDesc(&source_desc);

        D3D11_BUFFER_DESC destination_desc{};
        native_destination->m_Resource->GetDesc(&destination_desc);

        GX_ASSERT(source_desc.ByteWidth == destination_desc.ByteWidth);
#endif

        m_Context->CopyResource(
            native_destination->m_Resource,
            native_source->m_Resource
        );
    }
}
