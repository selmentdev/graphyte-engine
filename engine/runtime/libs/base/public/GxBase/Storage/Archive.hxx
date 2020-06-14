#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/Types.hxx>
#include <GxBase/Uuid.hxx>
#include <GxBase/DateTime.hxx>

GX_DECLARE_LOG_CATEGORY(LogStorage, Trace, Trace);

namespace Graphyte::Storage
{
    class BASE_API Archive
    {
    protected:
        uint32_t m_Version;
        bool m_IsLoading : 1;
        bool m_IsSaving : 1;
        bool m_Error : 1;
        bool m_Persistent : 1;

    public:
        Archive() noexcept;
        virtual ~Archive() noexcept;

    public:
        virtual void Serialize(
            void* buffer,
            size_t size) noexcept = 0;

        virtual int64_t GetPosition() noexcept
        {
            return 0;
        }

        virtual int64_t GetSize() noexcept
        {
            return 0;
        }

        virtual void SetPosition(
            [[maybe_unused]] int64_t position) noexcept
        {
        }

        virtual void Flush() noexcept
        {
        }

    public:
        bool IsSaving() const noexcept
        {
            return m_IsSaving;
        }

        bool IsLoading() const noexcept
        {
            return m_IsLoading;
        }

        bool IsError() const noexcept
        {
            return m_Error;
        }

        bool IsPersistent() const noexcept
        {
            return m_Persistent;
        }

    public:
        __forceinline friend Archive& operator<<(
            Archive& archive,
            std::string& value) noexcept
        {
            GX_ASSERT(value.length() <= static_cast<size_t>(std::numeric_limits<int32_t>::max()));

            if (archive.m_IsLoading)
            {
                uint32_t size = 0;
                archive << size;
                value.resize(size);
            }
            else if (archive.m_IsSaving)
            {
                uint32_t size = static_cast<uint32_t>(value.length());
                archive << size;
            }

            archive.Serialize(std::data(value), std::size(value));

            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, bool& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, char& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, char8_t& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, char16_t& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, char32_t& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, wchar_t& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, signed char& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, signed short& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, signed int& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, signed long& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, signed long long& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, unsigned char& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, unsigned short& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, unsigned int& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, unsigned long& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, unsigned long long& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, float& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, double& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, long double& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, Float2A& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, Float3A& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, Float4A& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, Float3x3A& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, Float4x3A& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, Float4x4A& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, Float2& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, Float3& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, Float4& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, Float3x3& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, Float4x3& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
        __forceinline friend Archive& operator<<(Archive& archive, Float4x4& value) noexcept
        {
            archive.Serialize(&value, sizeof(value));
            return archive;
        }
    };

    template <typename TEnumType>
    __forceinline Archive& operator<<(Archive& archive, TEnumType& value) noexcept
        requires(std::is_enum_v<TEnumType>)
    {
        archive.Serialize(&value, sizeof(value));
        return archive;
    }

    template <typename T>
    __forceinline Archive& operator<<(Archive& archive, std::vector<T>& value) noexcept
        requires(!std::is_polymorphic_v<T>)
    {
        if (archive.IsLoading())
        {
            uint64_t size{};
            archive << size;
            GX_ASSERT(static_cast<size_t>(size) == size);
            value.resize(static_cast<size_t>(size));
            value.shrink_to_fit();
        }
        else if (archive.IsSaving())
        {
            uint64_t size = static_cast<uint64_t>(value.size());
            archive << size;
        }

        archive.Serialize(std::data(value), std::size(value) * sizeof(T));

        return archive;
    }

    __forceinline Archive& operator<<(Archive& archive, Uuid& value) noexcept
    {
        return archive << value.Low << value.High;
    }

    __forceinline Archive& operator<<(Archive& archive, DateTime& value) noexcept
    {
        return archive << value.Value;
    }

    __forceinline Archive& operator<<(Archive& archive, TimeSpan& value) noexcept
    {
        return archive << value.Value;
    }
}
