#include <Graphyte/Base.module.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Threading.hxx>
#include <Graphyte/Graphics/Image.hxx>
#include <Graphyte/Storage/FileManager.hxx>

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

#include <Graphyte/System/Dialogs.hxx>

int GraphyteMain([[maybe_unused]] int argc, [[maybe_unused]] char** argv) noexcept
{
    std::vector<std::string> paths{};
    std::vector<Graphyte::System::FileDialogFilter> filters{
        { "Text Files", "*.txt", },
        { "All Files", "*.*", },
    };

    if (Graphyte::System::OpenFile(paths, filters, "Open Chujemuje") == Graphyte::Status::Success)
    {
        for (auto const& path : paths)
        {
            GX_LOG(LogAssetsCompiler, Info, "file: {}\n", path);
        }
    }
    else
    {
        GX_LOG(LogAssetsCompiler, Info, "failed to get path\n");
    }

    Graphyte::Uuid u = Graphyte::Uuid::Create();
    std::string s{};
    Graphyte::Converter<Graphyte::Uuid>::ToString(s, u);
    Graphyte::Uuid u1{};
    Graphyte::Converter<Graphyte::Uuid>::FromString(u1, s);
    Graphyte::Converter<Graphyte::Uuid>::FromString(u1, "00000000000000000dupadupadupadup");
    Graphyte::Converter<Graphyte::Uuid>::FromString(u1, "0000000000000000dupadupadupadupa");
    Graphyte::Converter<Graphyte::Uuid>::FromString(u1, "000000000000000dupadupadupadupad");
    Graphyte::Converter<Graphyte::Uuid>::FromString(u1, "00000000000000dupadupadupadupadu");

    GX_LOG(LogAssetsCompiler, Info, "username: {}\n", Graphyte::System::GetUserName());

    return 0;
}
