#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Status.hxx>
#include <GxBase/Diagnostics.hxx>

// =================================================================================================
//
// Native library handle type.
//

namespace Graphyte::System
{
    struct LibraryHandle final
    {
#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

        HMODULE Value;

#elif GRAPHYTE_PLATFORM_POSIX

        void* Value;

#else
#error Not implemented.
#endif

        bool IsValid() const noexcept
        {
            return Value != nullptr;
        }
    };
}


// =================================================================================================
//
// Library implementation.
//

namespace Graphyte::System
{
    class BASE_API Library final
    {
    private:
        LibraryHandle m_Handle{};

    public:
        Library() = default;

        Library(const Library&) = delete;

        Library(Library&& other) noexcept
            : m_Handle{ std::exchange(other.m_Handle, {}) }
        {
        }

        Library(std::string_view path) noexcept
        {
            [[maybe_unused]] auto const status = this->Load(path);
            GX_ASSERT(status == Status::Success);
        }

        ~Library() noexcept
        {
            if (m_Handle.IsValid())
            {
                [[maybe_unused]] auto const status = this->Unload();
                GX_ASSERT(status == Status::Success);
            }
        }

        Library& operator=(const Library&) = delete;

        Library& operator=(Library&& other) noexcept
        {
            m_Handle = std::exchange(other.m_Handle, {});
            return (*this);
        }

    public:
        /// @brief Loads specified shared library.
        ///
        /// @param path Provides path to library.
        Status Load(std::string_view path) noexcept;

        /// @brief Unloads library.
        Status Unload() noexcept;

        void* Resolve(const char* name) const noexcept;

        template <typename T>
        T* Resolve(const char* name) const noexcept
        {
            return reinterpret_cast<T*>(this->Resolve(name));
        }

        bool IsValid() const noexcept
        {
            return m_Handle.IsValid();
        }
    };
}
