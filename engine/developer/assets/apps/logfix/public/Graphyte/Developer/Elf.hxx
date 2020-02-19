#pragma once
#include <Graphyte/Base.module.hxx>

namespace Graphyte::Developer::Elf
{
    enum class ElfImageHeaderFileMagic : uint32_t
    {
        Valid = 0x464C457Fu,
    };

    enum class ElfImageHeaderFileClass : uint8_t
    {
        None = 0,
        Bit32 = 1,
        Bit64 = 2,
    };

    enum class ElfImageHeaderFileEncoding : uint8_t
    {
        None = 0,
        LittleEndian = 1,
        BigEndian = 2,
    };

    enum class ElfImageHeaderFileVersion : uint8_t
    {
        None = 0,
        Current = 1,
    };

    enum class ElfImageHeaderOsAbi : uint8_t
    {
        SysV = 0,
        HPUX = 1,
        NetBSD = 2,
        Linux = 3,
        FreeBSD = 9,
        OpenBSD = 12,
        ARM_AEABI = 64,
        ARM = 97,
        Standalone = 255,
    };

    enum class ElfImageHeaderOsAbiVersion : uint8_t
    {
        None = 0,
    };

    enum class ElfImageHeaderFileType : uint16_t
    {
        None = 0,
        Relocatable = 1,
        Executable = 2,
        SharedLibrary = 3,
        CoreDump = 4,
        LoOs = 0xFE00u,
        HiOs = 0xFEFFu,
        LoProc = 0xFF00u,
        HiProc = 0xFFFFu,
    };


    enum class ElfImageHeaderMachineType : uint16_t
    {
        None = 0,
        X86_32 = 3,
        PPC = 20,
        PPC64 = 21,
        ARM = 40,
        X86_64 = 62,
        AARCH64 = 183,
    };

    enum class ElfImageHeaderObjectVersion : uint32_t
    {
        None = 0,
        Current = 1,
    };

    struct ElfImageHeader32 final
    {
        ElfImageHeaderFileMagic FileMagic;
        ElfImageHeaderFileClass FileClass;
        ElfImageHeaderFileEncoding FileEncoding;
        ElfImageHeaderFileVersion FileVersion;
        ElfImageHeaderOsAbi OsAbi;
        ElfImageHeaderOsAbiVersion OsAbiVersion;
        uint8_t Reserved[7];
        ElfImageHeaderFileType FileType;
        ElfImageHeaderMachineType MachineType;
        ElfImageHeaderObjectVersion ObjectVersion;
        uint32_t EntryPoint;
        uint32_t OffsetOfProgramHeaderTable;
        uint32_t OffsetOfSectionHeaderTable;
        uint32_t Flags;
        uint16_t SizeOfHeader;
        uint16_t SizeOfProgramHeader;
        uint16_t NumberOfProgramHeaders;
        uint16_t SizeOfSectionHeader;
        uint16_t NumberOfSectionHeaders;
        uint16_t IndexOfStringTable;
    };
    static_assert(sizeof(ElfImageHeader32) == 52);
    static_assert(alignof(ElfImageHeader32) == alignof(uint32_t));

    struct ElfImageHeader64 final
    {
        ElfImageHeaderFileMagic FileMagic;
        ElfImageHeaderFileClass FileClass;
        ElfImageHeaderFileEncoding FileEncoding;
        ElfImageHeaderFileVersion FileVersion;
        ElfImageHeaderOsAbi OsAbi;
        ElfImageHeaderOsAbiVersion OsAbiVersion;
        uint8_t Reserved[7];
        ElfImageHeaderFileType FileType;
        ElfImageHeaderMachineType MachineType;
        ElfImageHeaderObjectVersion ObjectVersion;
        uint64_t EntryPoint;
        uint64_t OffsetOfProgramHeaderTable;
        uint64_t OffsetOfSectionHeaderTable;
        uint32_t Flags;
        uint16_t SizeOfHeader;
        uint16_t SizeOfProgramHeader;
        uint16_t NumberOfProgramHeaders;
        uint16_t SizeOfSectionHeader;
        uint16_t NumberOfSectionHeaders;
        uint16_t IndexOfStringTable;
    };
    static_assert(sizeof(ElfImageHeader64) == 64);
    static_assert(alignof(ElfImageHeader64) == alignof(uint64_t));

    enum class ElfSectionIndex : uint16_t
    {
        Undefined = 0,
    };

    enum class ElfSectionType : uint32_t
    {
        Unused = 0,
        ProgramData = 1,
        SymbolTable = 2,
        StringTable = 3,
        Rela = 4,
        SymbolHashTable = 5,
        Dynamic = 6,
        Notes = 7,
        NoBits = 8,
        Rel = 9,
        SharedLib = 10,
        LinkerSymbolTable = 11,
        CtorArray = 14,
        DtorArray = 15,
        PreCtorArray = 16,
        SectionGroup = 17,
        SymbolTableExtended = 18,
    };

    enum class ElfSectionFlags : uint32_t
    {
        Write = 1 << 0,
        Alloc = 1 << 1,
        Executable = 1 << 2,
        Merge = 1 << 4,
        Strings = 1 << 5,
        InfoLink = 1 << 6,
        LinkOrder = 1 << 7,
        OsNonConforming = 1 << 8,
        Group = 1 << 9,
        Tls = 1 << 10,
        Compressed = 1 << 11,
    };

    struct ElfSectionHeader32 final
    {
        uint32_t Name;
        ElfSectionType Type;
        ElfSectionFlags Flags;
        uint32_t VirtualAddress;
        uint32_t Offset;
        uint32_t Size;
        uint32_t Link;
        uint32_t Info;
        uint32_t Align;
        uint32_t SizeOfEntry;
    };
    static_assert(sizeof(ElfSectionHeader32) == 40);

    struct ElfSectionHeader64 final
    {
        uint32_t Name;
        ElfSectionType Type;
        ElfSectionFlags Flags;
        uint64_t VirtualAddress;
        uint64_t Offset;
        uint64_t Size;
        uint32_t Link;
        uint32_t Info;
        uint64_t Align;
        uint64_t SizeOfEntry;
    };
    static_assert(sizeof(ElfSectionHeader64) == 64);

    enum class ElfSymbolType : uint8_t
    {
        NoType = 0,
        Object = 1,
        Function = 2,
        Section = 3,
        File = 4,
        Common = 5,
        Tls = 6,
    };

    enum class ElfSymbolBind : uint8_t
    {
        Local = 0,
        Global = 1,
        Weak = 2,
    };

    enum class ElfSymbolVisibility : uint8_t
    {
        Default = 0,
        Internal = 1,
        Hidden = 2,
        Protected = 3,
    };

    struct ElfSymbol32 final
    {
        uint32_t Name;
        uint32_t Value;
        uint32_t Size;
        uint8_t Info;
        uint8_t Other;
        uint16_t SectionIndex;
    };
    static_assert(sizeof(ElfSymbol32) == 16);

    struct ElfSymbol64 final
    {
        uint32_t Name;
        uint8_t Info;
        uint8_t Other;
        uint16_t SectionIndex;
        uint64_t Value;
        uint64_t Size;
    };
    static_assert(sizeof(ElfSymbol64) == 24);

    constexpr ElfSymbolType GetSymbolType(const ElfSymbol32& symbol) noexcept
    {
        return static_cast<ElfSymbolType>(symbol.Info & 0xFu);
    }

    constexpr ElfSymbolType GetSymbolType(const ElfSymbol64& symbol) noexcept
    {
        return static_cast<ElfSymbolType>(symbol.Info & 0xFu);
    }

    constexpr ElfSymbolBind GetSymbolBind(const ElfSymbol32& symbol) noexcept
    {
        return static_cast<ElfSymbolBind>((symbol.Info >> 4) & 0xFu);
    }

    constexpr ElfSymbolBind GetSymbolBind(const ElfSymbol64& symbol) noexcept
    {
        return static_cast<ElfSymbolBind>((symbol.Info >> 4) & 0xFu);
    }

    constexpr ElfSymbolVisibility GetSymbolVisibility(const ElfSymbol32& symbol) noexcept
    {
        return static_cast<ElfSymbolVisibility>(symbol.Other & 0x3u);
    }

    constexpr ElfSymbolVisibility GetSymbolVisibility(const ElfSymbol64& symbol) noexcept
    {
        return static_cast<ElfSymbolVisibility>(symbol.Other & 0x3u);
    }
}
