#include <GxBase/Status.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/System.hxx>
#include <GxBase/Storage/Path.hxx>
#include <GxBase/Storage/IFileSystem.hxx>
#include <GxBase/Storage/FileManager.hxx>

#include <DbgHelp.h>

namespace Graphyte::Diagnostics
{
#if defined(__MINGW32__) || defined(__MINGW64__)

    static constexpr MINIDUMP_TYPE MiniDumpWithModuleHeaders = 0x00080000;
    static constexpr MINIDUMP_TYPE MiniDumpFilterTriage = 0x00100000;

#endif

    static BOOL CALLBACK CreateMiniDumpCallback(
        [[maybe_unused]] PVOID param,
        const PMINIDUMP_CALLBACK_INPUT input,
        PMINIDUMP_CALLBACK_OUTPUT output
    ) noexcept
    {
        BOOL result = FALSE;

        if (input != nullptr && output != nullptr)
        {
            switch (input->CallbackType)
            {
                case IncludeModuleCallback:
                case IncludeThreadCallback:
                case ThreadCallback:
                case ThreadExCallback:
                case MemoryCallback:
                    {
                        result = TRUE;
                        break;
                    }
                case ModuleCallback:
                    {
                        if ((output->ModuleWriteFlags & ModuleReferencedByMemory) != 0)
                        {
                            output->ModuleWriteFlags ^= ModuleWriteModule;
                        }

                        result = TRUE;
                        break;
                    }
                case CancelCallback:
                    {
                        break;
                    }
            }
        }

        return result;
    }

    Status WriteCoreDump(
        HANDLE handle,
        EXCEPTION_POINTERS* exception
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        GX_ASSERT(exception != nullptr);

        MINIDUMP_EXCEPTION_INFORMATION mdei{
            .ThreadId = GetCurrentThreadId(),
            .ExceptionPointers = exception,
            .ClientPointers = FALSE,
        };

        MINIDUMP_CALLBACK_INFORMATION mdci{
            .CallbackRoutine = static_cast<MINIDUMP_CALLBACK_ROUTINE>(CreateMiniDumpCallback),
            .CallbackParam = nullptr,
        };

        auto mdt = static_cast<MINIDUMP_TYPE>(
            MiniDumpNormal |
            MiniDumpWithDataSegs |
            MiniDumpWithHandleData |
            MiniDumpWithIndirectlyReferencedMemory |
            MiniDumpWithProcessThreadData |
            MiniDumpWithPrivateReadWriteMemory |
            MiniDumpWithThreadInfo |
            MiniDumpWithCodeSegs |
            MiniDumpWithPrivateWriteCopyMemory |
            MiniDumpWithTokenInformation |
            MiniDumpWithModuleHeaders
        );

        BOOL result = MiniDumpWriteDump(
            GetCurrentProcess(),
            GetCurrentProcessId(),
            handle,
            mdt,
            &mdei,
            nullptr,
            &mdci
        );

        if (result == FALSE)
        {
            auto hr = static_cast<HRESULT>(GetLastError());

            GX_LOG(LogPlatform, Error, "Failed to write minidump: {}\n", Diagnostics::GetMessageFromHRESULT(hr));

            return Status::Failure;
        }

        return Status::Success;
    }

    Status CreateCoreDump(
        EXCEPTION_POINTERS* exception
    ) noexcept
    {
        GX_ASSERT(exception != nullptr);

        // TODO: Implement function to creating crashdump in one pass
        std::string filename{};
        ToString(filename, DateTime::Now(), DateTimeFormat::FileSafe);
        filename.append(".dmp");

        std::string dump_path = Storage::FileManager::GetCrashdumpDirectory();

        Status status = Storage::IFileSystem::GetPlatformNative().DirectoryTreeCreate(dump_path);

        if (status == Status::Success)
        {
            Storage::Path::Append(dump_path, filename);

            HANDLE hFile = CreateFileW(
                System::Impl::WidenString(dump_path).c_str(),
                GENERIC_WRITE,
                0,
                nullptr,
                CREATE_ALWAYS,
                FILE_ATTRIBUTE_NORMAL,
                nullptr
            );

            if (hFile != INVALID_HANDLE_VALUE)
            {
                status = WriteCoreDump(hFile, exception);

                CloseHandle(hFile);
            }
            else
            {
                GX_ABORT("Failed to create dump file");
            }
        }

        return status;
    }
}
