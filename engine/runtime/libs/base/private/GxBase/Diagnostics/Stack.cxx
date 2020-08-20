#include <GxBase/Diagnostics.hxx>
#include <GxBase/Storage/Path.hxx>
#include <GxBase/Flags.hxx>

namespace Graphyte::Diagnostics
{
    BASE_API std::string ToString(
        const StackFrame& frame,
        StackFrameFormat format) noexcept
    {
        std::string result{};

        if (Flags::Has(format, StackFrameFormat::Address))
        {
            result += fmt::format("{}: ", reinterpret_cast<void*>(frame.Address));
        }

        if (!frame.Module.empty() && Flags::Has(format, StackFrameFormat::Module))
        {
            result += Storage::GetFilename(frame.Module);
            result += '!';
        }

        result += frame.Function;

        if (!frame.File.empty() && Flags::Has(format, StackFrameFormat::Location))
        {
            result += fmt::format(" {}:{}", Storage::GetFilename(frame.File), frame.Line);
        }

        return result;
    }

    BASE_API std::string ToString(
        std::span<const StackFrame> frames,
        StackFrameFormat format) noexcept
    {
        std::string result{};

        for (const auto& frame : frames)
        {
            result += ToString(frame, format);
            result += '\n';
        }

        return result;
    }
}
