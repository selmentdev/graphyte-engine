#if false
#include <GxBase/Network/IpEndPoint.hxx>
#include <GxBase/Network/IpAddress.hxx>
#include <GxBase/String.hxx>
#include <GxBase/Diagnostics.hxx>

#if GRAPHYTE_PLATFORM_WINDOWS
#include <mstcpip.h>
#endif

namespace Graphyte::Network
{
    IpEndPoint::IpEndPoint() noexcept
        : m_Address{}
    {
    }

    IpEndPoint::IpEndPoint(
        const IpAddress& address,
        uint16_t port
    ) noexcept
        : m_Address{}
    {
        switch (address.Family())
        {
        case AddressFamily::IpV4:
            {
                m_Address.V4.sin_family = AF_INET;
                m_Address.V4.sin_addr = address.m_address.v4;
                m_Address.V4.sin_port = htons(port);
                break;
            }
        case AddressFamily::IpV6:
            {
                m_Address.V6.sin6_family = AF_INET6;
                m_Address.V6.sin6_addr = address.m_address.v6;
                m_Address.V6.sin6_scope_id = address.m_scope_id;
                m_Address.V6.sin6_port = htons(port);
                break;
            }
        default:
            {
                break;
            }
        }
    }

    IpEndPoint::IpEndPoint(
        const sockaddr& address
    ) noexcept
        : m_Address{}
    {
        m_Address.GenericAddress = address;
    }

    IpEndPoint::IpEndPoint(
        const sockaddr_in& address
    ) noexcept
        : m_Address{}
    {
        m_Address.V4 = address;
        m_Address.GenericAddress.sa_family = AF_INET;
    }

    IpEndPoint::IpEndPoint(
        const sockaddr_in6& address
    ) noexcept
        : m_Address{}
    {
        m_Address.V6 = address;
        m_Address.GenericAddress.sa_family = AF_INET6;
    }

    IpEndPoint::IpEndPoint(
        const struct sockaddr* address,
        socklen_t length
    ) noexcept
        : m_Address{}
    {
        std::memcpy(&m_Address.GenericAddress, address, static_cast<size_t>(length));
    }

    IpAddress IpEndPoint::GetAddress() const noexcept
    {
        switch (GetFamily())
        {
        case AddressFamily::IpV4:
            {
                return IpAddress::MakeAddress(m_Address.V4);
            }
        case AddressFamily::IpV6:
            {
                return IpAddress::MakeAddress(m_Address.V6);
            }
        default:
            {
                break;
            }
        }

        return IpAddress{};
    }

    void IpEndPoint::SetAddress(
        const IpAddress& address
    ) noexcept
    {
        uint16_t port = 0;
        uint32_t scope_id = 0;

        //
        // Get port.
        //
        switch (GetFamily())
        {
        case AddressFamily::IpV4:
            {
                port = m_Address.V4.sin_port;
                break;
            }
        case AddressFamily::IpV6:
            {
                port = m_Address.V6.sin6_port;
                scope_id = m_Address.V6.sin6_scope_id;
                break;
            }
        default:
            {
                break;
            }
        }

        switch (address.Family())
        {
        case AddressFamily::IpV4:
            {
                m_Address.V4.sin_family = AF_INET;
                m_Address.V4.sin_addr = address.m_address.v4;
                m_Address.V4.sin_port = port;
                break;
            }
        case AddressFamily::IpV6:
            {
                m_Address.V6.sin6_family = AF_INET6;
                m_Address.V6.sin6_addr = address.m_address.v6;
                m_Address.V6.sin6_port = port;
                m_Address.V6.sin6_scope_id = scope_id;
                break;
            }
        default:
            {
                break;
            }
        }
    }

    uint16_t IpEndPoint::GetPort() const noexcept
    {
        switch (GetFamily())
        {
        case AddressFamily::IpV4:
            {
                return ntohs(m_Address.V4.sin_port);
            }
        case AddressFamily::IpV6:
            {
                return ntohs(m_Address.V6.sin6_port);
            }
        default:
            {
                break;
            }
        }

        return 0;
    }

    void IpEndPoint::SetPort(
        uint16_t value
    ) noexcept
    {
        switch (GetFamily())
        {
        case AddressFamily::IpV4:
            {
                m_Address.V4.sin_port = htons(value);
                break;
            }
        case AddressFamily::IpV6:
            {
                m_Address.V6.sin6_port = htons(value);
                break;
            }
        default:
            {
                break;
            }
        }
    }

    AddressFamily IpEndPoint::GetFamily() const noexcept
    {
        return static_cast<AddressFamily>(m_Address.GenericAddress.sa_family);
    }

    const sockaddr* IpEndPoint::GetSockAddr() const noexcept
    {
        return &m_Address.GenericAddress;
    }

    socklen_t IpEndPoint::GetSockLength() const noexcept
    {
        switch (GetFamily())
        {
        case AddressFamily::IpV4:
            {
                return sizeof(m_Address.V4);
            }
        case AddressFamily::IpV6:
            {
                return sizeof(m_Address.V6);
            }
        default:
            {
                break;
            }
        }

        return 0;
    }

#if !(GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP)
    static bool SplitEndpoint(
        std::string_view address,
        std::string& host,
        std::string& serv
    ) noexcept
    {
        auto const position = address.find_last_of(':');
        if (position != std::string_view::npos)
        {
            auto arg_host = address.substr(0, position);
            auto arg_serv = address.substr(position + 1);

            bool const is_ipv6 = (arg_host.front() == '[' && arg_host.back() == ']');

            if (is_ipv6)
            {
                arg_host.remove_prefix(1);
                arg_host.remove_suffix(1);
            }

            host.assign(arg_host);
            serv.assign(arg_serv);
            return true;
        }
        
        return false;
    }
#endif

    bool IpEndPoint::TryParse(
        IpEndPoint& out_result,
        const char* value
    ) noexcept
    {
        GX_ASSERT(value != nullptr);

#if (GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP)
        AddressStorage u{};
        if (RtlIpv4StringToAddressExA(value, TRUE, &u.V4.sin_addr, &u.V4.sin_port) == 0)
        {
            u.V4.sin_family = AF_INET;
            out_result = IpEndPoint{ u.V4 };
            return true;
        }
        else if (RtlIpv6StringToAddressExA(value, &u.V6.sin6_addr, &u.V6.sin6_scope_id, &u.V6.sin6_port) == 0)
        {
            u.V6.sin6_family = AF_INET6;
            out_result = IpEndPoint{ u.V6 };
            return true;
        }

        return false;
#else
        std::string host{};
        std::string serv{};

        SplitEndpoint(value, host, serv);

        struct addrinfo* addr{};

        struct addrinfo hints{};
        hints.ai_family = AF_UNSPEC;
        hints.ai_flags = AI_NUMERICHOST;

        bool const valid = getaddrinfo(
            host.c_str(),
            serv.c_str(),
            &hints,
            &addr) == 0;

        if (valid && addr != nullptr)
        {
            out_result = IpEndPoint{ addr->ai_addr, static_cast<socklen_t>(addr->ai_addrlen) };
        }

        freeaddrinfo(addr);

        return valid;
#endif
    }

    bool IpEndPoint::ToString(
        std::string& out_result
    ) const noexcept
    {
#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
        std::array<char, INET6_ADDRSTRLEN> temp_buffer{};
        ULONG string_length = static_cast<ULONG>(temp_buffer.max_size());
        bool valid = false;

        switch (m_Address.GenericAddress.sa_family)
        {
        case AF_INET:
            {
                valid = (RtlIpv4AddressToStringExA(
                    &m_Address.V4.sin_addr,
                    m_Address.V4.sin_port,
                    temp_buffer.data(),
                    &string_length) == 0);
                break;
            }
        case AF_INET6:
            {
                valid = (RtlIpv6AddressToStringExA(
                    &m_Address.V6.sin6_addr,
                    m_Address.V6.sin6_scope_id,
                    m_Address.V6.sin6_port,
                    temp_buffer.data(),
                    &string_length) == 0);
                break;
            }
        }

        if (valid)
        {
            out_result.assign(temp_buffer.data());
        }

        return valid;
#else
        std::array<char, NI_MAXHOST> sock_host{};
        std::array<char, NI_MAXSERV> sock_serv{};

        auto valid = getnameinfo(
            GetSockAddr(),
            GetSockLength(),
            sock_host.data(),
            static_cast<socklen_t>(sock_host.size()),
            sock_serv.data(),
            static_cast<socklen_t>(sock_serv.size()),
            NI_NUMERICHOST | NI_NUMERICSERV
        ) == 0;

        out_result.clear();

        if (valid)
        {
            const char* format = (m_Address.GenericAddress.sa_family == AF_INET6)
                ? "[{}]:{}"
                : "{}:{}";

            fmt::memory_buffer buffer{};
            fmt::format_to(buffer, format, sock_host.data(), sock_serv.data());
            out_result.assign(buffer.data(), buffer.size());
        }

        return valid;
#endif
    }
}
#endif
