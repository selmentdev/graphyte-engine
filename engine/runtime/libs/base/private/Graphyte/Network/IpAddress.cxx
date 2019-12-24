#include "Base.pch.hxx"
#include <Graphyte/Network/IpAddress.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/ByteAccess.hxx>

#if GRAPHYTE_PLATFORM_WINDOWS
#include <mstcpip.h>
#endif

namespace Graphyte::Network
{
    namespace Impl
    {
        template <typename T>
        static constexpr uint32_t MaskBits(
            T val, uint32_t size
        )
        {
            uint32_t count = 0;
            if (val)
            {
                val = (val ^ (val - 1)) >> 1;
                for (count = 0; val; ++count)
                {
                    val >>= 1;
                }
            }
            else
            {
                count = size;
            }
            return size - count;
        }
    }

    IpAddress::IpAddress() noexcept
        : m_address{}
        , m_scope_id{}
        , m_family{ AddressFamily::Unspecified }
    {
    }

    IpAddress::IpAddress(
        AddressFamily family
    ) noexcept
        : m_address{}
        , m_scope_id{}
        , m_family{ family }
    {
    }

    IpAddress::IpAddress(
        const struct in_addr& address
    ) noexcept
        : m_address{}
        , m_scope_id{ 0 }
        , m_family{ AddressFamily::IpV4 }
    {
        m_address.v4 = address;
    }

    IpAddress::IpAddress(
        const struct in6_addr& address,
        uint32_t scope_id
    ) noexcept
        : m_address{}
        , m_scope_id{ scope_id }
        , m_family{ AddressFamily::IpV6 }
    {
        m_address.v6 = address;
    }

    IpAddress IpAddress::MakeAddress(
        const void* address,
        socklen_t length
    ) noexcept
    {
        if (length == sizeof(struct in_addr))
        {
            return IpAddress{ *reinterpret_cast<const in_addr*>(address) };
        }
        else if (length == sizeof(struct in6_addr))
        {
            return IpAddress{ *reinterpret_cast<const in6_addr*>(address) };
        }

        return IpAddress{};
    }

    IpAddress IpAddress::MakeAddress(
        const void* address,
        socklen_t length,
        uint32_t scope_id
    ) noexcept
    {
        if (length == sizeof(struct in_addr))
        {
            return IpAddress{ *reinterpret_cast<const struct in_addr*>(address) };
        }
        else if (length == sizeof(struct in6_addr))
        {
            return IpAddress{ *reinterpret_cast<const struct in6_addr*>(address), scope_id };
        }

        return IpAddress{};
    }

    IpAddress IpAddress::MakeAddress(
        const sockaddr& address
    ) noexcept
    {
        if (address.sa_family == AF_INET)
        {
            return MakeAddress(*reinterpret_cast<const struct sockaddr_in*>(&address));
        }
        else if (address.sa_family == AF_INET6)
        {
            return MakeAddress(*reinterpret_cast<const struct sockaddr_in6*>(&address));
        }

        return IpAddress{ AddressFamily::Unspecified };
    }

    IpAddress IpAddress::MakeAddress(
        const struct sockaddr_in& address
    ) noexcept
    {
        return IpAddress{ address.sin_addr };
    }

    IpAddress IpAddress::MakeAddress(
        const struct sockaddr_in6& address
    ) noexcept
    {
        return IpAddress{ address.sin6_addr, address.sin6_scope_id };
    }

    AddressFamily IpAddress::Family() const noexcept
    {
        return m_family;
    }

    uint32_t IpAddress::ScopeId() const noexcept
    {
        if (IsV6())
        {
            return m_scope_id;
        }

        return 0;
    }

    bool IpAddress::IsV4() const noexcept
    {
        return m_family == AddressFamily::IpV4;
    }

    bool IpAddress::IsV6() const noexcept
    {
        return m_family == AddressFamily::IpV6;
    }

    bool IpAddress::IsAny() const noexcept
    {
        switch (m_family)
        {
        case AddressFamily::IpV4:
            {
                return m_address.v4.s_addr == INADDR_ANY;
            }

        case AddressFamily::IpV6:
            {
                return m_address.as_uint16[0] == 0
                    && m_address.as_uint16[1] == 0
                    && m_address.as_uint16[2] == 0
                    && m_address.as_uint16[3] == 0
                    && m_address.as_uint16[4] == 0
                    && m_address.as_uint16[5] == 0
                    && m_address.as_uint16[6] == 0
                    && m_address.as_uint16[7] == 0;
            }
        default:
            {
                break;
            }
        }

        return false;
    }

    bool IpAddress::IsBroadcast() const noexcept
    {
        if (IsV4())
        {
            return m_address.v4.s_addr == INADDR_NONE;
        }

        return false;
    }

    bool IpAddress::IsLoopback() const noexcept
    {
        switch (m_family)
        {
        case AddressFamily::IpV4:
            {
                return (NetworkToHost(static_cast<uint32_t>(m_address.v4.s_addr)) & 0xFF000000) == 0x7F000000;
            }

        case AddressFamily::IpV6:
            {
                return m_address.as_uint16[0] == 0
                    && m_address.as_uint16[1] == 0
                    && m_address.as_uint16[2] == 0
                    && m_address.as_uint16[3] == 0
                    && m_address.as_uint16[4] == 0
                    && m_address.as_uint16[5] == 0
                    && m_address.as_uint16[6] == 0
                    && NetworkToHost(m_address.as_uint16[7]) == UINT16_C(0x0001);
            }
        default:
            {
                break;
            }
        }

        return false;
    }

    bool IpAddress::IsMulticast() const noexcept
    {
        switch (m_family)
        {
        case AddressFamily::IpV4:
            {
                return (NetworkToHost(static_cast<uint32_t>(m_address.v4.s_addr)) & UINT32_C(0xF0000000)) == UINT32_C(0xE0000000);
            }

        case AddressFamily::IpV6:
            {
                return (NetworkToHost(m_address.as_uint16[0]) & UINT16_C(0xFFE0)) == UINT16_C(0xFF00);
            }
        default:
            {
                break;
            }
        }

        return false;
    }

    bool IpAddress::IsUnicast() const noexcept
    {
        return !IsAny()
            && !IsBroadcast()
            && !IsMulticast();
    }

    bool IpAddress::IsLinkLocal() const noexcept
    {
        switch (m_family)
        {
        case AddressFamily::IpV4:
            {
                return (NetworkToHost(static_cast<uint32_t>(m_address.v4.s_addr)) & UINT32_C(0xFFFF0000)) == UINT32_C(0xA9FE0000);
            }

        case AddressFamily::IpV6:
            {
                return (NetworkToHost(m_address.as_uint16[0]) & UINT16_C(0xFFE0)) == UINT16_C(0xFE80);
            }
        default:
            {
                break;
            }
        }

        return false;
    }

    bool IpAddress::IsSiteLocal() const noexcept
    {
        switch (m_family)
        {
        case AddressFamily::IpV4:
            {
                uint32_t const address = NetworkToHost(static_cast<uint32_t>(m_address.v4.s_addr));

                return ((address & UINT32_C(0xFF000000)) == UINT32_C(0x0A000000))
                    || ((address & UINT32_C(0xFFFF0000)) == UINT32_C(0xC0A80000))
                    || ((address >= UINT32_C(0xAC100000)) && (address <= UINT32_C(0xAC1FFFFF)));
            }

        case AddressFamily::IpV6:
            {
                return ((NetworkToHost(m_address.as_uint16[0]) & UINT16_C(0xFFE0)) == UINT16_C(0xFEC0))
                    || ((NetworkToHost(m_address.as_uint16[0]) & UINT16_C(0xFF00)) == UINT16_C(0xFC00));
            }
        default:
            {
                break;
            }
        }

        return false;
    }

    bool IpAddress::IsV4Compatible() const noexcept
    {
        switch (m_family)
        {
        case AddressFamily::IpV4:
            {
                return true;
            }

        case AddressFamily::IpV6:
            {
                return m_address.as_uint16[0] == 0
                    && m_address.as_uint16[1] == 0
                    && m_address.as_uint16[2] == 0
                    && m_address.as_uint16[3] == 0
                    && m_address.as_uint16[4] == 0
                    && m_address.as_uint16[5] == 0;
            }
        default:
            {
                break;
            }
        }

        return false;
    }

    bool IpAddress::IsV4Mapped() const noexcept
    {
        switch (m_family)
        {
        case AddressFamily::IpV4:
            {
                return true;
            }

        case AddressFamily::IpV6:
            {
                return m_address.as_uint16[0] == 0
                    && m_address.as_uint16[1] == 0
                    && m_address.as_uint16[2] == 0
                    && m_address.as_uint16[3] == 0
                    && m_address.as_uint16[4] == 0
                    && (NetworkToHost(m_address.as_uint16[5]) == UINT16_C(0xFFFF));
            }
        default:
            {
                break;
            }
        }

        return false;
    }

    bool IpAddress::IsWellKnownMulticast() const noexcept
    {
        switch (m_family)
        {
        case AddressFamily::IpV4:
            {
                return (NetworkToHost(static_cast<uint32_t>(m_address.v4.s_addr)) & UINT32_C(0xFFFFFF00)) == UINT32_C(0xE0000000);
            }

        case AddressFamily::IpV6:
            {
                return (NetworkToHost(m_address.as_uint16[0]) & UINT16_C(0xFFF0)) == UINT16_C(0xFF00);
            }
        default:
            {
                break;
            }
        }

        return false;
    }

    bool IpAddress::IsNodeLocalMulticast() const noexcept
    {
        switch (m_family)
        {
        case AddressFamily::IpV4:
            {
                return false;
            }

        case AddressFamily::IpV6:
            {
                return (NetworkToHost(m_address.as_uint16[0]) & UINT16_C(0xFFEF)) == UINT16_C(0xFF01);
            }
        default:
            {
                break;
            }
        }

        return false;
    }

    bool IpAddress::IsLinkLocalMulticast() const noexcept
    {
        switch (m_family)
        {
        case AddressFamily::IpV4:
            {
                return (NetworkToHost(static_cast<uint32_t>(m_address.v4.s_addr)) & UINT32_C(0xFF000000)) == UINT32_C(0xE0000000);
            }

        case AddressFamily::IpV6:
            {
                return (NetworkToHost(m_address.as_uint16[0]) & UINT16_C(0xFFEF)) == UINT16_C(0xFF02);
            }
        default:
            {
                break;
            }
        }

        return false;
    }

    bool IpAddress::IsSiteLocalMulticast() const noexcept
    {
        switch (m_family)
        {
        case AddressFamily::IpV4:
            {
                return (NetworkToHost(static_cast<uint32_t>(m_address.v4.s_addr)) & UINT32_C(0xFFFF0000)) == UINT32_C(0xEFFF0000);
            }

        case AddressFamily::IpV6:
            {
                return (NetworkToHost(m_address.as_uint16[0]) & UINT16_C(0xFFF0)) == UINT16_C(0xFF05);
            }
        default:
            {
                break;
            }
        }

        return false;
    }

    bool IpAddress::IsOrgLocalMulticast() const noexcept
    {
        switch (m_family)
        {
        case AddressFamily::IpV4:
            {
                return (NetworkToHost(static_cast<uint32_t>(m_address.v4.s_addr)) & UINT32_C(0xFFFF0000)) == UINT32_C(0xEFC00000);
            }

        case AddressFamily::IpV6:
            {
                return (NetworkToHost(m_address.as_uint16[0]) & UINT16_C(0xFFF0)) == UINT16_C(0xFF08);
            }
        default:
            {
                break;
            }
        }

        return false;
    }

    bool IpAddress::IsGlobalMulticast() const noexcept
    {
        switch (m_family)
        {
        case AddressFamily::IpV4:
            {
                uint32_t const address = NetworkToHost(static_cast<uint32_t>(m_address.v4.s_addr));

                return (address >= UINT32_C(0xE0000100))
                    && (address <= UINT32_C(0xEE000000));
            }

        case AddressFamily::IpV6:
            {
                return (NetworkToHost(m_address.as_uint16[0]) & UINT16_C(0xFFF0)) == UINT16_C(0xFF0F);
            }
        default:
            {
                break;
            }
        }

        return false;
    }

    IpAddress IpAddress::MapToV4() const noexcept
    {
        if (IsV6())
        {
            AddressStorage addr{};
            addr.as_uint8[0] = m_address.as_uint8[12];
            addr.as_uint8[1] = m_address.as_uint8[13];
            addr.as_uint8[2] = m_address.as_uint8[14];
            addr.as_uint8[3] = m_address.as_uint8[15];

            return IpAddress{ addr.v4 };
        }

        return (*this);
    }

    IpAddress IpAddress::MapToV6() const noexcept
    {
        if (IsV4())
        {
            AddressStorage addr{};
            addr.as_uint16[5] = UINT16_C(0xFFFF);
            addr.as_uint8[0] = m_address.as_uint8[12];
            addr.as_uint8[1] = m_address.as_uint8[13];
            addr.as_uint8[2] = m_address.as_uint8[14];
            addr.as_uint8[3] = m_address.as_uint8[15];

            return IpAddress{ addr.v6, 0 };
        }

        return (*this);
    }

    socklen_t IpAddress::Length() const noexcept
    {
        switch (m_family)
        {
        case AddressFamily::IpV4:
            {
                return sizeof(m_address.v4);
            }
        case AddressFamily::IpV6:
            {
                return sizeof(m_address.v6);
            }
        default:
            {
                break;
            }
        }

        return 0;
    }

    const void* IpAddress::Address() const noexcept
    {
        return &m_address;
    }

    uint32_t IpAddress::PrefixLength() const noexcept
    {
        switch (m_family)
        {
        case AddressFamily::IpV4:
            {
                return Impl::MaskBits(NetworkToHost(static_cast<uint32_t>(m_address.v4.s_addr)), 32);
            }
        case AddressFamily::IpV6:
            {
                uint32_t bits = 0;
                uint32_t pos = 128;

                for (int i = 15; i >= 0; --i)
                {
                    uint32_t address = m_address.v6.s6_addr[i];

                    if ((bits = Impl::MaskBits(address, 8)) != 0)
                    {
                        return pos - (8 - bits);
                    }

                    pos -= 8;
                }

                break;
            }
        default:
            {
                break;
            }
        }

        return 0;
    }

    IpAddress IpAddress::Mask(
        const IpAddress& address,
        const IpAddress& mask
    ) noexcept
    {
        bool const can_mask = address.IsV4() && mask.IsV4();

        GX_ASSERT(can_mask);

        IpAddress result = address;

        if (can_mask)
        {
            result.m_address.v4.s_addr &= mask.m_address.v4.s_addr;
        }

        return result;
    }

    IpAddress IpAddress::Mask(
        const IpAddress& address,
        const IpAddress& mask,
        const IpAddress& set
    ) noexcept
    {
        bool const can_mask = address.IsV4() && mask.IsV4() && set.IsV4();

        GX_ASSERT(can_mask);

        IpAddress result = address;

        if (can_mask)
        {
            result.m_address.v4.s_addr &= mask.m_address.v4.s_addr;
            result.m_address.v4.s_addr |= set.m_address.v4.s_addr & ~mask.m_address.v4.s_addr;
        }

        return result;
    }

    bool IpAddress::ToBytesIPv4(
        std::array<std::uint8_t, 4>& result
    ) noexcept
    {
        if (m_family == AddressFamily::IpV4)
        {
            std::copy(&m_address.as_uint8[0], &m_address.as_uint8[4], std::begin(result));
            return true;
        }

        return false;
    }

    bool IpAddress::ToBytesIPv6(
        std::array<std::uint8_t, 16>& result
    ) noexcept
    {
        if (m_family == AddressFamily::IpV6)
        {
            std::copy(&m_address.as_uint8[0], &m_address.as_uint8[16], std::begin(result));
            return true;
        }

        return false;
    }

    bool IpAddress::ToString(
        std::string& result
    ) const noexcept
    {
        std::array<char, 64> temp_buffer{};

        switch (m_family)
        {
        case AddressFamily::IpV4:
            {
#if GRAPHYTE_PLATFORM_WINDOWS
                RtlIpv4AddressToStringA(&m_address.v4, temp_buffer.data());
#else
                inet_ntop(AF_INET, &m_address.v4, temp_buffer.data(), temp_buffer.size());
#endif
                result.assign(temp_buffer.data());
                return true;
            }

        case AddressFamily::IpV6:
            {
#if GRAPHYTE_PLATFORM_WINDOWS
                RtlIpv6AddressToStringA(&m_address.v6, temp_buffer.data());
#else
                inet_ntop(AF_INET6, &m_address.v4, temp_buffer.data(), temp_buffer.size());
#endif
                result.assign(temp_buffer.data());
                return true;
            }

        default:
            {
                break;
            }
        }

        return false;
    }

    bool IpAddress::TryParse(
        IpAddress& result,
        const char* address
    ) noexcept
    {
        if (TryParse(result, address, AddressFamily::IpV4))
        {
            return true;
        }

        if (TryParse(result, address, AddressFamily::IpV6))
        {
            return true;
        }

        return false;

    }

    bool IpAddress::TryParse(
        IpAddress& result,
        const char* address,
        AddressFamily family
    ) noexcept
    {
        if (address != nullptr)
        {
#if GRAPHYTE_PLATFORM_WINDOWS
            USHORT port = {};
            ULONG scope_id = {};
#endif
            switch (family)
            {
            case AddressFamily::IpV4:
                {
                    in_addr ipv4_address{};
#if GRAPHYTE_PLATFORM_WINDOWS
                    if (RtlIpv4StringToAddressExA(address, TRUE, &ipv4_address, &port) == 0)
#else
                    if (inet_pton(AF_INET, address, &ipv4_address) == 1)
#endif
                    {
                        result = IpAddress{ ipv4_address };
                        return true;
                    }

                    break;
                }

            case AddressFamily::IpV6:
                {
                    in6_addr ipv6_address{};
                    //
                    // Otherwise, it may be valid IPv6 address.
                    //
#if GRAPHYTE_PLATFORM_WINDOWS
                    if (RtlIpv6StringToAddressExA(address, &ipv6_address, &scope_id, &port) == 0)
#else
                    if (inet_pton(AF_INET6, address, &ipv6_address) == 1)
#endif
                    {
                        result = IpAddress{ ipv6_address };
                        return true;
                    }

                    break;
                }
            default:
                {
                    break;
                }
            }
        }
        return false;
    }

    IpAddress IpAddress::Any(
        AddressFamily family
    ) noexcept
    {
        IpAddress result{ family };

        if (family == AddressFamily::IpV4)
        {
            result.m_address.v4.s_addr = INADDR_ANY;
        }
        else if (family == AddressFamily::IpV6)
        {
            result.m_address.v6 = in6addr_any;
        }

        return result;
    }

    IpAddress IpAddress::Broadcast(
        AddressFamily family
    ) noexcept
    {
        IpAddress result{ family };

        if (family == AddressFamily::IpV4)
        {
            result.m_address.v4.s_addr = INADDR_BROADCAST;
        }

        return result;
    }

    IpAddress IpAddress::Loopback(
        AddressFamily family
    ) noexcept
    {
        IpAddress result{ family };

        if (family == AddressFamily::IpV4)
        {
            result.m_address.v4.s_addr = INADDR_LOOPBACK;
        }
        else if (family == AddressFamily::IpV6)
        {
            result.m_address.v6 = in6addr_loopback;
        }

        return result;
    }

    IpAddress IpAddress::None(
        AddressFamily family
    ) noexcept
    {
        IpAddress result{ family };

        if (family == AddressFamily::IpV4)
        {
            result.m_address.v4.s_addr = INADDR_NONE;
        }

        return result;
    }
}
