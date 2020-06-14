#pragma once
#include <Graphyte/Diagnostics.hxx>

namespace GraphyteAssets
{
    enum struct ShaderFunctionParamDirection
    {
        None,
        In,
        Out,
        InOut,
    };

    struct ShaderFunctionParam final
    {
        std::string Name;
        std::string Type;
        ShaderFunctionParamDirection Direction;
    };

    struct ShaderFunction final
    {
        std::string Name;
        std::string ReturnType;
        std::vector<ShaderFunctionParam> Params;
    };

    struct ShaderUniformField final
    {
        std::string Name;
        std::string Type;
    }

    struct ShaderUniform final
    {
        std::vector<ShaderUniformField> Fields;
    };

    struct ShaderDeclarationField final
    {
        std::string Name;
        std::string Type;
    };

    struct ShaderInputDeclaration final
    {
        std::vector<ShaderDeclarationField> Fields;
    };

    struct ShaderOutputDeclaration final
    {
        std::vector<ShaderDeclarationField> Fields;
    };

    struct ShaderModule final
    {
        std::string Name;
        std::vector<std::string> Includes;
        std::vector<ShaderUniform> Uniforms;
        std::vector<ShaderFunction> Functions;
        std::vector<ShaderInputDeclaration> InputDeclarations;
        std::vector<ShaderOutputDeclaration> OutputDeclarations;
    };

    class ASSETS_MATERIAL_API MaterialFormat
    {
    };
}
