#include <GxBase/Base.module.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/Threading.hxx>
#include <GxGraphics/Graphics/Image.hxx>
#include <GxBase/Storage/FileManager.hxx>

GX_DECLARE_LOG_CATEGORY(LogAssetsCompiler, Trace, Trace);
GX_DEFINE_LOG_CATEGORY(LogAssetsCompiler);

#include <GxLaunch/Launch/Main.hxx>

Graphyte::Application::ApplicationDescriptor GraphyteApp{
    "Graphyte Assets Compiler",
    "assets.compiler",
    "Graphyte",
    Graphyte::Application::ApplicationType::ConsoleTool,
    Graphyte::Version{ 1, 0, 0, 0 }
};

#include <GxBase/Uuid.hxx>
#include <GxBase/Maths.hxx>
#include <GxBase/System/Dialogs.hxx>
#include <GxBase/Random.hxx>
#include <GxBase/Maths/Vector.hxx>
#include <GxBase/Maths/Plane.hxx>
#include <GxBase/Maths/Quaternion.hxx>
#include <GxBase/Maths/Geometric.hxx>

int GraphyteMain([[maybe_unused]] int argc, [[maybe_unused]] char** argv) noexcept
{
    using namespace Graphyte::Maths;
    auto const v0 = Make<Vector4>(1.0f, 2.0f, 3.0f, 4.0f);
    auto const q0 = Make<Quaternion>(1.0f, 0.0f, 0.0f, 5.0f);
    auto const l0 = Length(q0);
    (void)l0;
    return 0;
}
