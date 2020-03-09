#include <Graphyte/Network.hxx>

namespace Graphyte::Network::Impl
{
    static Status MapGAIResult(
        int value
    ) noexcept
    {
        switch (value)
        {
            case EAI_AGAIN:
                return Status::TryAgain;
            case EAI_BADFLAGS:
                return Status::InvalidArgument;
            case EAI_MEMORY:
                return Status::NotEnoughMemory;
            case EAI_SERVICE:
            case EAI_NONAME:
                return Status::NotFound;
            case EAI_FAMILY:
            case EAI_SOCKTYPE:
                return Status::NotSupported;
            case EAI_FAIL:
            default:
                break;
        }

        return Status::Failure;
    }
}

namespace Graphyte::Network
{
    BASE_API Status ResolveDns(
        IpEndPoint& address,
        const char* host_name,
        const char* service_name
    ) noexcept
    {
        struct addrinfo hints{
            .ai_family = AF_UNSPEC,
            .ai_socktype = SOCK_STREAM,
            .ai_protocol = IPPROTO_TCP,
        };

        struct addrinfo* result = nullptr;

        const auto status = getaddrinfo(
            host_name,
            service_name,
            &hints,
            &result
        );

        if (status == 0)
        {
            address = IpEndPoint{
                result->ai_addr,
                static_cast<socklen_t>(result->ai_addrlen)
            };

            freeaddrinfo(result);

            return Status::Success;
        }

        return Impl::MapGAIResult(status);
    }

    BASE_API Status ResolveDns(
        std::vector<IpEndPoint>& address_list,
        const char* host_name,
        const char* service_name
    ) noexcept
    {
        struct addrinfo hints{
            .ai_family = AF_UNSPEC,
            .ai_socktype = SOCK_STREAM,
            .ai_protocol = IPPROTO_TCP,
        };

        struct addrinfo* result = nullptr;

        const auto status = getaddrinfo(
            host_name,
            service_name,
            &hints,
            &result
        );

        if (status == 0)
        {
            address_list.clear();

            while (result != nullptr)
            {
                address_list.push_back(
                    IpEndPoint{
                        result->ai_addr,
                        static_cast<socklen_t>(result->ai_addrlen)
                    }
                );

                result = result->ai_next;
            }

            freeaddrinfo(result);

            return Status::Success;
        }

        return Impl::MapGAIResult(status);
    }

    BASE_API Status ResolveDns(
        std::string& host,
        const IpEndPoint& address
    ) noexcept
    {
        std::array<char, NI_MAXHOST> sock_host{};
        std::array<char, NI_MAXSERV> sock_serv{};

        auto status = getnameinfo(
            address.GetSockAddr(),
            address.GetSockLength(),
            sock_host.data(),
            static_cast<socklen_t>(sock_host.size()),
            sock_serv.data(),
            static_cast<socklen_t>(sock_serv.size()),
            NI_NUMERICHOST | NI_NUMERICSERV
        );

        if (status == 0)
        {
            host.assign(sock_host.data());

            return Status::Success;
        }

        return Impl::MapGAIResult(status);
    }

    BASE_API Status ResolveDns(
        std::vector<std::string>& host_list,
        const IpEndPoint& address
    ) noexcept
    {
#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
        // Hack 'till we develop something better: GetAddrInfoEx
        std::string host{};

        auto status = ResolveDns(host, address);
        
        if (status == Status::Success)
        {
            host_list.push_back(host);
            return Status::Success;
        }

        return status;
#else
        const char* buffer = nullptr;
        int length = 0;
        int type = 0;

        switch (address.m_Address.GenericAddress.sa_family)
        {
        case AF_INET:
            {
                buffer = reinterpret_cast<const char*>(&address.m_Address.V4.sin_addr);
                length = sizeof(struct in_addr);
                type = AF_INET;
                break;
            }

        case AF_INET6:
            {
                buffer = reinterpret_cast<const char*>(&address.m_Address.V6.sin6_addr);
                length = sizeof(struct in6_addr);
                type = AF_INET6;
                break;
            }

        default:
            {
                return Status::NotSupported;
            }
        }

        struct hostent* entry = gethostbyaddr(buffer, static_cast<socklen_t>(length), type);

        if (entry != nullptr)
        {
            host_list.push_back(std::string{ entry->h_name });

            for (char** alias = entry->h_aliases; (*alias) != nullptr; ++alias)
            {
                host_list.push_back(std::string{ *alias });
            }

            return Status::Success;
        }

        switch (h_errno)
        {
            case HOST_NOT_FOUND:
                return Status::NotFound;
            case TRY_AGAIN:
                return Status::TryAgain;
            case NO_ADDRESS:
#if NO_ADDRESS != NO_DATA
            case NO_DATA:
//  Check whether this one is defined to something else
#endif
                return Status::NotFound;
            case NO_RECOVERY:
            default:
                break;
        }

        return Status::Failure;
#endif
    }
}
