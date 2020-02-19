#pragma once
#include <GraphyteAssets/GxAssetsFont.hxx>
#include <GraphyteAssets/ICompiler.hxx>

namespace GraphyteAssets
{
    struct ASSETS_FONT_API IFontCompiler : public ICompiler
    {
        virtual ~IFontCompiler() noexcept;
    };
}
