#include <GxBase/Storage/Archive.hxx>

GX_DEFINE_LOG_CATEGORY(LogStorage);

namespace Graphyte::Storage
{
    Archive::Archive() noexcept
        : m_Version{ 0 }
        , m_IsLoading{ false }
        , m_IsSaving{ false }
        , m_Error{ false }
        , m_Persistent{ false }
    {
    }

    Archive::~Archive() noexcept
    {
    }
}
