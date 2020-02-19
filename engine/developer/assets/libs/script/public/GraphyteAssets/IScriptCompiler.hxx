#pragma once
#include <GraphyteAssets/GxAssetsScript.hxx>
#include <GraphyteAssets/ICompiler.hxx>

namespace GraphyteAssets
{
    struct ASSETS_SCRIPT_API IScriptCompiler : public ICompiler
    {
        virtual ~IScriptCompiler() noexcept;
    };
}
