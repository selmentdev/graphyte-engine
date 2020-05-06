#include <GxBase/Base.module.hxx>
#include <GxBase/Modules.hxx>

class BaseModule final : public Graphyte::IModule
{
public:
    virtual void OnInitialize() noexcept final override
    {
    }

    virtual void OnFinalize() noexcept final override
    {
    }
};

GX_IMPLEMENT_MODULE(BaseModule);
