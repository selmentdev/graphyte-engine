#include <GraphyteAssets/Module.MaterialCompiler.hxx>
#include <GraphyteAssets/CompilerFactory.hxx>
#include <GraphyteAssets/MaterialCompiler.hxx>

namespace GraphyteAssets
{
    ASSETS_MATERIAL_API void InitializeAssetsMaterialLibrary() noexcept
    {
        CompilerFactory::Get().Register("compile-material", []() -> std::unique_ptr<ICompiler> {
            return std::make_unique<MaterialCompiler>();
        });
    }

    ASSETS_MATERIAL_API void ShutdownAssetsMaterialLibrary() noexcept
    {
    }
}
