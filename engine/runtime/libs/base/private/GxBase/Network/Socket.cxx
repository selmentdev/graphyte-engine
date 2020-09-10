#if false
#include <GxBase/Network/Socket.hxx>
#include <GxBase/Flags.hxx>
#include <GxBase/Diagnostics.hxx>

namespace Graphyte::Network
{
    class SocketExtensions final
    {
    public:
        static int32_t ConvertSocketFlags(
            SocketFlags flags
        ) noexcept
        {
            int32_t result = 0;

            if (flags != SocketFlags::None)
            {
                constexpr const auto requiredFlags = SocketFlags::OutOfBand
                    | SocketFlags::MaxIoVectorLength
                    | SocketFlags::Peek
                    | SocketFlags::DontRoute
                    | SocketFlags::Partial;

                if (!Flags::Has(flags, requiredFlags))
                {
                    return -1;
                }

                if (Flags::Has(flags, SocketFlags::OutOfBand))
                {
                    result |= MSG_OOB;
                }

                if (Flags::Has(flags, SocketFlags::Peek))
                {
                    result |= MSG_PEEK;
                }

                if (Flags::Has(flags, SocketFlags::DontRoute))
                {
                    result |= MSG_DONTROUTE;
                }

#ifdef MSG_MORE
                if (Flags::Has(flags, SocketFlags::Partial))
                {
                    result |= MSG_MORE;
                }
#endif
            }

            return result;
        }

        static int32_t ConvertAddressFamily(
            AddressFamily family
        ) noexcept
        {
            switch (family)
            {
            case AddressFamily::Unspecified:
                {
                    return AF_UNSPEC;
                }
            case AddressFamily::IpV4:
                {
                    return AF_INET;
                }
            case AddressFamily::IpV6:
                {
                    return AF_INET6;
                }
            default:
                {
                    break;
                }
            }

            return -1;
        }

        static int32_t ConvertSocketType(
            SocketType type
        ) noexcept
        {
            switch (type)
            {
            case SocketType::Stream:
                {
                    return SOCK_STREAM;
                }
            case SocketType::Datagram:
                {
                    return SOCK_DGRAM;
                }
            case SocketType::Raw:
                {
                    return SOCK_RAW;
                }
            case SocketType::Rdm:
                {
                    return SOCK_RDM;
                }
            case SocketType::SequentialPacket:
                {
                    return SOCK_SEQPACKET;
                }
            default:
                {
                    break;
                }
            }

            return -1;
        }

        static int32_t ConvertSocketProtocol(
            ProtocolType protocol
        ) noexcept
        {
            switch (protocol)
            {
                //case ProtocolType::Ip:
            case ProtocolType::IpV4:
            case ProtocolType::IpV6:
                //case ProtocolType::IcmpV4:
                //case ProtocolType::IcmpV6:
                //case ProtocolType::Ggp:
            case ProtocolType::Tcp:
                //case ProtocolType::Pup:
            case ProtocolType::Udp:
                //case ProtocolType::Idp:
                {
                    return static_cast<int32_t>(protocol);
                }
            default:
                {
                    return -1;
                }
            }
        }

        static int32_t ConvertSocketOptions(int32_t level, int32_t name, int32_t& nativeLevel, int32_t& nativeName) noexcept
        {
        switch (level)
        {

        }
        }
    };

    Socket::Socket() noexcept
        : m_Handle{ Socket::InvalidHandle }
        , m_Error{ SocketError::Success }
    {
    }

    Socket::~Socket() noexcept
    {
        GX_ASSERT(m_Handle == Socket::InvalidHandle);
    }

    //    WaitStatus

    WaitStatus Socket::Create(
        AddressFamily family,
        SocketType type,
        ProtocolType protocol
    ) noexcept
    {
        m_Handle = Socket::InvalidHandle;
        m_Error = SocketError::Success;

        const int32_t familyAsInt = SocketExtensions::ConvertAddressFamily(family);
        const int32_t typeAsInt = SocketExtensions::ConvertSocketType(type);
        const int32_t protocolAsInt = SocketExtensions::ConvertSocketProtocol(protocol);

        GX_ASSERT(familyAsInt != -1);
        GX_ASSERT(typeAsInt != -1);
        GX_ASSERT(protocolAsInt != -1);

        Socket::SocketHandle handle = socket(familyAsInt, typeAsInt, protocolAsInt);
        if (handle == Socket::InvalidHandle && familyAsInt == AF_INET && typeAsInt == SOCK_RAW && protocolAsInt == 0)
        {
            handle = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
        }

        if (handle == Socket::InvalidHandle)
        {
            StoreLastError();
            return WaitStatus::Failure;
        }

        {
            int32_t value = 1;
            const int32_t result = setsockopt(
                handle,
                SOL_SOCKET,
                SO_REUSEADDR,
                reinterpret_cast<char*>(&value),
                sizeof(value)
            );

            if (result == -1)
            {
                StoreLastError();
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP
                if (closesocket(handle) == -1)
#else
                if (close(handle) == -1)
#endif
                {
                    StoreLastError();
                }

                return WaitStatus::Failure;
            }
        }

        m_Handle = handle;
        m_Error = SocketError::Success;
        return WaitStatus::Success;
    }

    WaitStatus Socket::SetBlocking(
        bool blocking
    ) noexcept
    {
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP

        u_long value = static_cast<u_long>(blocking ? 0 : 1);

        const int32_t result = ioctlsocket(m_Handle, FIONBIO, &value);

#elif defined(O_NONBLOCK)

        int flags{};

        if (-1 == (flags = fcntl(m_Handle, F_GETFL, 0)))
        {
            flags = 0;
        }

        if (blocking)
        {
            flags |= O_NONBLOCK;
        }

        const int32_t result = fcntl(m_Handle, F_SETFL, flags);
#else

        u_long value = static_cast<u_long>(blocking ? 0 : 1);

        const int32_t result = ioctl(m_Handle, FIONBIO, &value);

#endif

        if (result == Socket::SocketErrorValue)
        {
            StoreLastError();
            return WaitStatus::Failure;
        }

        return WaitStatus::Success;
    }
}
#endif
