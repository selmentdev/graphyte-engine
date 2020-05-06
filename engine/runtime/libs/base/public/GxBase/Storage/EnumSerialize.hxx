#pragma once
#include <GxBase/Base.module.hxx>

namespace Graphyte::Storage
{
    template <typename TEnumType, typename TStorageType = std::underlying_type_t<TEnumType>>
    struct EnumStorage final
    {
        static_assert(sizeof(TEnumType) <= sizeof(TStorageType), "TStorageType must be large enought to store all possible TEnumType values");

        union
        {
            TEnumType EnumValue;
            TStorageType StorageValue;
        };

        __forceinline EnumStorage() noexcept = default;

        __forceinline EnumStorage(
            const EnumStorage& other
        ) noexcept
            : EnumValue{ other.EnumValue }
        {
        }
        __forceinline EnumStorage(
            TEnumType value
        ) noexcept
            : EnumValue{ value }
        {
        }

        __forceinline EnumStorage& operator= (
            TEnumType value
        ) noexcept
        {
            EnumValue = value;
            return (*this);
        }
        __forceinline EnumStorage& operator= (
            EnumStorage other
        ) noexcept
        {
            EnumValue = other.EnumValue;
            return (*this);
        }

        __forceinline operator TEnumType() const noexcept
        {
            return EnumValue;
        }

        __forceinline bool operator== (
            TEnumType value
        ) const noexcept
        {
            return EnumValue == value;
        }

        __forceinline bool operator!= (
            TEnumType value
        ) const noexcept
        {
            return EnumValue == value;
        }
    };
}
