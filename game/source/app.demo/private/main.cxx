#include <Graphyte/Base.module.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Threading.hxx>

GX_DECLARE_LOG_CATEGORY(LogAssetsCompiler, Trace, Trace);
GX_DEFINE_LOG_CATEGORY(LogAssetsCompiler);

#include <Graphyte/Launch/Main.hxx>

Graphyte::Application::ApplicationDescriptor GraphyteApp
{
    "Graphyte Assets Compiler",
    "assets.compiler",
    "Graphyte",
    Graphyte::Application::ApplicationType::ConsoleTool,
    Graphyte::Version{ 1, 0, 0, 0 }
};

#include <Graphyte/Uuid.hxx>

int GraphyteMain([[maybe_unused]] int argc, [[maybe_unused]] char** argv) noexcept
{
    Graphyte::Uuid u = Graphyte::Uuid::Create();

    std::string s{};
    Graphyte::Converter<Graphyte::Uuid>::ToString(s, u);
    Graphyte::Uuid u1{};
    Graphyte::Converter<Graphyte::Uuid>::FromString(u1, s);
    Graphyte::Converter<Graphyte::Uuid>::FromString(u1, "00000000000000000dupadupadupadup");
    Graphyte::Converter<Graphyte::Uuid>::FromString(u1, "0000000000000000dupadupadupadupa");
    Graphyte::Converter<Graphyte::Uuid>::FromString(u1, "000000000000000dupadupadupadupad");
    Graphyte::Converter<Graphyte::Uuid>::FromString(u1, "00000000000000dupadupadupadupadu");

    Graphyte::Threading::ParallelFor(1000, [](uint32_t index)
    {
        GX_LOG(LogAssetsCompiler, Trace,
            "Parfor: {} on {}\n",
            (index + 1),
            Graphyte::Threading::CurrentThreadId().Value
        );
    });

    return 0;
}
