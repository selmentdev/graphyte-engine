#include <Graphyte/Base.module.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Threading.hxx>
#include <Graphyte/Maths2/Vector.hxx>
#include <Graphyte/Maths2/Noise.hxx>
#include <Graphyte/Graphics/ImageCodecs/ImageCodec.DDS.hxx>
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

GX_NOINLINE Graphyte::Maths::Vec4 mathcall Temp(
    Graphyte::Maths::Vec4 v1,
    Graphyte::Maths::Vec4 v2,
    Graphyte::Maths::Vec4 v3,
    Graphyte::Maths::Vec4 v4,
    Graphyte::Maths::Vec4 v5,
    Graphyte::Maths::Vec4 v6,
    Graphyte::Maths::Vec4 v7
) noexcept
{
    auto const r1 = Graphyte::Maths::MulAdd(v1, v2, v3);
    auto const r2 = Graphyte::Maths::MulSub(v2, v3, v4);
    auto const r3 = Graphyte::Maths::NegMulAdd(v3, v4, v5);
    auto const r4 = Graphyte::Maths::NegMulSub(v4, v5, v6);
    auto const g1 = Graphyte::Maths::MulAdd(r1, r2, v7);
    auto const g2 = Graphyte::Maths::MulAdd(r3, r4, v7);
    return Graphyte::Maths::MulAdd(g1, g2, v7);
}

int GraphyteMain([[maybe_unused]] int argc, [[maybe_unused]] char** argv) noexcept
{
    auto const g = Temp(
        Graphyte::Maths::Make<Graphyte::Maths::Vec4>(1.0F),
        Graphyte::Maths::Make<Graphyte::Maths::Vec4>(1.0F),
        Graphyte::Maths::Make<Graphyte::Maths::Vec4>(1.0F),
        Graphyte::Maths::Make<Graphyte::Maths::Vec4>(1.0F),
        Graphyte::Maths::Make<Graphyte::Maths::Vec4>(1.0F),
        Graphyte::Maths::Make<Graphyte::Maths::Vec4>(1.0F),
        Graphyte::Maths::Make<Graphyte::Maths::Vec4>(1.0F)
    );

    Graphyte::Maths::Float4A ffff;
    Graphyte::Maths::Store(&ffff, g);

    GX_LOG(LogAssetsCompiler, Trace, "{},{},{},{}\n", ffff.X, ffff.Y, ffff.Z, ffff.W);

    Graphyte::Uuid u = Graphyte::Uuid::Create();
    std::string s{};
    Graphyte::Converter<Graphyte::Uuid>::ToString(s, u);
    Graphyte::Uuid u1{};
    Graphyte::Converter<Graphyte::Uuid>::FromString(u1, s);
    Graphyte::Converter<Graphyte::Uuid>::FromString(u1, "00000000000000000dupadupadupadup");
    Graphyte::Converter<Graphyte::Uuid>::FromString(u1, "0000000000000000dupadupadupadupa");
    Graphyte::Converter<Graphyte::Uuid>::FromString(u1, "000000000000000dupadupadupadupad");
    Graphyte::Converter<Graphyte::Uuid>::FromString(u1, "00000000000000dupadupadupadupadu");

    size_t const width{ 512 };
    size_t const height{ 512 };
    auto image = Graphyte::Graphics::Image::Create2D(
        Graphyte::Graphics::PixelFormat::R32G32B32A32_FLOAT,
        width,
        height
    );

    auto* pixels = image->GetSubresource(0);
    auto const half = Graphyte::Maths::Make<Graphyte::Maths::Vec4>(0.5F);

    for (size_t h = 0; h < height; ++h)
    {
        auto* scanline = pixels->GetScanline<Graphyte::Maths::Float4>(h);

        for (size_t w = 0; w < width; ++w)
        {
            auto* pixel = scanline + w;

            float const scale = 0.5F;
            float const fw = scale * (static_cast<float>(w) / static_cast<float>(width));
            float const fh = scale * (static_cast<float>(h) / static_cast<float>(height));

            auto const fr = Graphyte::Maths::Noises::snoise(Graphyte::Maths::Make<Graphyte::Maths::Vec2>(fw, fh));
            auto const r = Graphyte::Maths::Make<Graphyte::Maths::Vec4>(fr, fr, fr, 1.0F);
            auto const hr = MulAdd(r, half, half);
            Store(pixel, hr);
        }
    }

    std::unique_ptr<Graphyte::Storage::Archive> archive{};
    if (Graphyte::Storage::FileManager::CreateWriter(archive, "d:/test.dds") == Graphyte::Status::Success)
    {
        Graphyte::Graphics::ImageCodecDDS codec{};
        if (codec.Encode(image, *archive) != Graphyte::Status::Success)
        {
            GX_LOG(LogAssetsCompiler, Error, "Failed to encode DDS file\n");
        }
    }
    else
    {
        GX_LOG(LogAssetsCompiler, Error, "Failed to save file\n");
    }

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
