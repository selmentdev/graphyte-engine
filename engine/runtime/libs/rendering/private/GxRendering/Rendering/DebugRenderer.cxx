
#include <Graphyte/Rendering/DebugRenderer.hxx>

namespace Graphyte::Rendering::Impl
{
    class DebugRenderer final : public IDebugRenderer
    {
    private:
        Graphics::GpuDeviceHandle m_Device;

    public:
        DebugRenderer(Graphics::GpuDeviceHandle device) noexcept
            : m_Device{ device }
        {
        }

        virtual ~DebugRenderer() noexcept = default;

    public:
        virtual void Update(
            [[maybe_unused]] float deltaTime) noexcept override
        {
        }

        virtual void Enable(
            [[maybe_unused]] bool value) noexcept override
        {
        }

        virtual void Render(
            [[maybe_unused]] Graphics::GpuCommandListHandle commandList) noexcept override
        {
            (void)m_Device;
        }

    public:
        virtual void Line(
            [[maybe_unused]] Maths::Vector3 start,
            [[maybe_unused]] Maths::Vector3 end,
            [[maybe_unused]] Maths::Color color,
            [[maybe_unused]] float width,
            [[maybe_unused]] bool ztest,
            [[maybe_unused]] float timeout) noexcept override
        {
        }
    };
}

namespace Graphyte::Rendering
{
    RENDERING_API std::unique_ptr<IDebugRenderer> CreateDebugRender(
        [[maybe_unused]] Graphics::GpuDeviceHandle device) noexcept
    {
        if (Rendering::IsDebugRenderEnabled)
        {
            return std::make_unique<Impl::DebugRenderer>(device);
        }

        return nullptr;
    }
}
