#include <GraphyteAssets/MaterialCompiler.hxx>
#include <Graphyte/Serialization/Writer.hxx>
#include <Graphyte/Serialization/Reader.hxx>
#include <Graphyte/Storage/FileManager.hxx>
#include <Graphyte/Compression.hxx>

namespace GraphyteAssets
{
    enum struct ShaderParamDirection : uint32_t
    {
        None,
        In,
        Out,
        Ref,
    };

    struct ShaderParam final
    {
        std::string Name;
        std::string Type;
        ShaderParamDirection Direction;
    };

    struct ShaderFunction final
    {
        std::string Name;
        std::string ReturnType;
        std::vector<ShaderParam> Params;
    };

    struct ShaderModule final
    {
        std::string Name;
        std::string Description;
        std::vector<ShaderFunction> Functions;
    };

    template <typename T>
    struct SerializerHelper
    {
        static bool Load(T& result, const Graphyte::Serialization::Reader::Value& serializer) = delete;

        static bool Save(Graphyte::Serialization::Writer::Value& serializer, const T& value) = delete;
    };

    template <>
    struct SerializerHelper<ShaderParamDirection> final
    {
        static bool Load(ShaderParamDirection& result, const Graphyte::Serialization::Reader::Value& serializer) noexcept
        {
            std::string_view temp{};
            if (serializer.GetValue(temp))
            {
                if (temp == "in")
                {
                    result = ShaderParamDirection::In;
                }
                else if (temp == "out")
                {
                    result = ShaderParamDirection::Out;
                }
                else if (temp == "ref")
                {
                    result = ShaderParamDirection::Ref;
                }

                return true;
            }

            return false;
        }
        static bool Save(Graphyte::Serialization::Writer::Value& serializer, const ShaderParamDirection& value) noexcept
        {
            std::string_view s{};

            switch (value)
            {
                case ShaderParamDirection::In:
                    s = "in";
                    break;
                case ShaderParamDirection::Out:
                    s = "out";
                    break;
                case ShaderParamDirection::Ref:
                    s = "ref";
                    break;
                default:
                    break;
            }

            if (!s.empty())
            {
                return serializer.String(s);
            }

            return false;
        }
    };

    MaterialCompiler::MaterialCompiler() noexcept
    {
    }

    MaterialCompiler::~MaterialCompiler() noexcept
    {
    }

    bool MaterialCompiler::Compile(std::string_view request) noexcept
    {
        (void)request;
        return true;
    }

    bool MaterialCompiler::Process(Graphyte::System::CommandLineEnumerator& command_line) noexcept
    {
        std::string content;

        using Graphyte::Serialization::Writer;

        Writer writer{};
        auto document = writer.StartDocument();
        {
            auto document_content = document.StartObject();
            {
                document_content.Key("module");
                auto m = document_content.StartObject();
                {
                    m.KeyValue("description", "this is module description\nthis module contains some shader functions\nit defines shader functions for shader compiler", false, true);
                    m.Key("functions");
                    auto functions = m.StartArray();
                    {
                        for (size_t i = 0; i < 10; ++i)
                        {
                            auto function = functions.StartObject();
                            function.Key("name");
                            function.String(fmt::format("function_{}", i), true);
                            function.Key("return");
                            function.String("float3");
                            function.Key("params");
                            auto params = function.StartArray(false);
                            {
                                auto param1 = params.StartObject(true);
                                {
                                    param1.Key("name");
                                    param1.String("param1");
                                    param1.Key("type");
                                    param1.String("float3");
                                    param1.Key("dir");
                                    SerializerHelper<ShaderParamDirection>::Save(param1, ShaderParamDirection::Ref);
                                    param1.End();
                                }

                                auto param2 = params.StartObject(true);
                                {
                                    param2.Key("name");
                                    param2.String("param2");
                                    param2.Key("type");
                                    param2.String("float3");
                                    param2.Key("dir");
                                    param2.String("out");
                                    param2.End();
                                }
                            }
                            params.End();

                            function.End();
                        }
                    }
                    functions.End();
                }
                m.End();
            }
            document_content.End();
        }
        document.End();

        std::string serialized{};
        writer.ToString(serialized);

        Graphyte::Storage::FileManager::WriteText(serialized, "module.yaml");

        std::vector<std::byte> data{};
        Graphyte::Compression::CompressString(Graphyte::CompressionMethod::LZ4HC, data, serialized);
        Graphyte::Storage::FileManager::WriteBinary(data, "module.yaml.lz4hc");

        (void)command_line;
        return true;
    }
}
