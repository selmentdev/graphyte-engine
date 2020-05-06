#pragma once
#include <GraphyteAssets/GxAssetsMaterial.hxx>
#include <GraphyteAssets/ICompiler.hxx>
#include <Graphyte/Diagnostics.hxx>

namespace GraphyteAssets
{
    class MaterialCompiler final : public ICompiler
    {
    public:
        MaterialCompiler() noexcept;
        virtual ~MaterialCompiler() noexcept;

        bool Compile(std::string_view request) noexcept override;
        bool Process(Graphyte::System::CommandLineEnumerator& command_line) noexcept override;
    };
}
