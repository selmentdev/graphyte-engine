#include "D3D12Common.hxx"

namespace Graphyte::Graphics::Gpu
{
    struct GpuD3D12RootParameter final
    {
        friend class GpuD3D12RootSignature;
    private:
        D3D12_ROOT_PARAMETER m_RootParam;
    public:
        GpuD3D12RootParameter() noexcept
        {
            m_RootParam.ParameterType = (D3D12_ROOT_PARAMETER_TYPE)0xffff'ffff;
        }
        GpuD3D12RootParameter() noexcept
        {
            Clear();
        }

        void Clear() noexcept
        {
            if (m_RootParam.ParameterType == D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE)
            {
                delete[] m_RootParam.DescriptorTable.pDescriptorRanges;
            }

            m_RootParam.ParameterType = (D3D12_ROOT_PARAMETER_TYPE)0xffff'ffff;
        }

    public:
        void SetConstants(UINT shader_register, UINT count, D3D12_SHADER_VISIBILITY shader_visibility = D3D12_SHADER_VISIBILITY_ALL) noexcept
        {
            m_RootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
            m_RootParam.ShaderVisibility = shader_visibility;
            m_RootParam.Constants.Num32BitValues = count;
            m_RootParam.Constants.ShaderRegister = shader_register;
            m_RootParam.Constants.RegisterSpace = 0;
        }
        void SetConstantBuffer(UINT shader_register, D3D12_SHADER_VISIBILITY shader_visibility = D3D12_SHADER_VISIBILITY_ALL) noexcept
        {
            m_RootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
            m_RootParam.ShaderVisibility = shader_visibility;
            m_RootParam.Descriptor.ShaderRegister = shader_register;
            m_RootParam.Descriptor.RegisterSpace = 0;
        }
        void SetSRVBuffer(UINT shader_register, D3D12_SHADER_VISIBILITY shader_visibility = D3D12_SHADER_VISIBILITY_ALL) noexcept
        {
            m_RootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_SRV;
            m_RootParam.ShaderVisibility = shader_visibility;
            m_RootParam.Descriptor.ShaderRegister = shader_register;
            m_RootParam.Descriptor.RegisterSpace = 0;
        }
        void SetUAVBuffer(UINT shader_register, D3D12_SHADER_VISIBILITY shader_visibility = D3D12_SHADER_VISIBILITY_ALL) noexcept
        {
            m_RootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_UAV;
            m_RootParam.ShaderVisibility = shader_visibility;
            m_RootParam.Descriptor.ShaderRegister = shader_register;
            m_RootParam.Descriptor.RegisterSpace = 0;
        }
        void SetDescriptorTable(UINT range_count, D3D12_SHADER_VISIBILITY shader_visibility = D3D12_SHADER_VISIBILITY_ALL) noexcept
        {
            m_RootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
            m_RootParam.ShaderVisibility = shader_visibility;
            m_RootParam.DescriptorTable.NumDescriptorRanges = range_count;
            m_RootParam.DescriptorTable.pDescriptorRanges = new D3D12_DESCRIPTOR_RANGE[range_count];
        }
        void SetDescriptorRange(D3D12_DESCRIPTOR_RANGE_TYPE type, UINT shader_register, UINT count, D3D12_SHADER_VISIBILITY shader_visibility = D3D12_SHADER_VISIBILITY_ALL)
        {
            SetDescriptorTable(1, shader_visibility);
            SetTableRange(0, type, shader_register, count);
        }
        void SetTableRange(UINT range_index, D3D12_DESCRIPTOR_RANGE_TYPE type, UINT shader_register, UINT count, UINT space = 0)noexcept
        {
            D3D12_DESCRIPTOR_RANGE* range = const_cast<D3D12_DESCRIPTOR_RANGE*>(m_RootParam.DescriptorTable.pDescriptorRanges + range_index);
            range->RangeType = type;
            range->NumDescriptors = count;
            range->BaseShaderRegister = shader_register;
            range->RegisterSpace = space;
            range->OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
        }

        const D3D12_ROOT_PARAMETER& operator() () const noexcept
        {
            return m_RootParam;
        }
    };

    class GpuD3D12RootSignature final
    {
    private:
        std::unique_ptr<GpuD3D12RootParameter[]> m_ParamArray;
        std::unique_ptr<D3D12_STATIC_SAMPLER_DESC[]> m_SamplerArray;
        ID3D12RootSignature* m_Signature;
        uint32_t m_DescriptorTableBitmap;
        uint32_t m_SamplerTableBitmap;
        uint32_t m_DescriptorTableSize[16];
        uint32_t m_RootParameters;
        uint32_t m_Samplers;
        uint32_t m_InitializedStaticSamplers;
        bool m_Finalized;

    public:
        GpuD3D12RootSignature(UINT root_params = 0, UINT static_samplers = 0) noexcept
            : m_Finalized{ false }
            , m_RootParameters{ root_params }
        {
            Reset(root_params, static_samplers);
        }

        ~GpuD3D12RootSignature() noexcept = default;

    public:
        void Reset(UINT root_params, UINT static_samplers) noexcept
        {
            if (root_params > 0)
            {
                m_ParamArray.reset(new GpuD3D12RootParameter[root_params]);
            }
            else
            {
                m_ParamArray = nullptr;
            }
            m_RootParameters = root_params;

            if (static_samplers > 0)
            {
                m_SamplerArray.reset(new D3D12_STATIC_SAMPLER_DESC[static_samplers]);
            }
            else
            {
                m_SamplerArray = nullptr;
            }
            m_Samplers = static_samplers;
            m_InitializedStaticSamplers = 0;
        }

        GpuD3D12RootParameter& operator[] (size_t index) noexcept
        {
            GX_ASSERT(index < m_RootParameters);
            return m_ParamArray.get()[index];
        }
        const GpuD3D12RootParameter& operator[] (size_t index) const noexcept
        {
            GX_ASSERT(index < m_RootParameters);
            return m_ParamArray.get()[index];
        }

        ID3D12RootSignature* GetSignature() const noexcept
        {
            return m_Signature;
        }

        void InitializeStaticSampler(UINT shader_register, const D3D12_SAMPLER_DESC&& desc, D3D12_SHADER_VISIBILITY shader_visibility = D3D12_SHADER_VISIBILITY_ALL) noexcept;
        void Finalize(const char* name, D3D12_ROOT_SIGNATURE_FLAGS flags = D3D12_ROOT_SIGNATURE_FLAG_NONE);
    };
}
