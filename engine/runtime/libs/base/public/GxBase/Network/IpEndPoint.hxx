#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Network/Types.hxx>

namespace Graphyte::Network
{
    struct AddressStorage final
    {
        union
        {
            struct sockaddr_in6 V6;
            struct sockaddr_in V4;
            struct sockaddr GenericAddress;
        };
    };

    class IpAddress;

    class BASE_API IpEndPoint final
    {
        friend class Dns;
    public:
        AddressStorage m_Address;

    public:
        IpEndPoint() noexcept;
        IpEndPoint(const IpAddress& address, uint16_t port) noexcept;
        IpEndPoint(const struct sockaddr& address) noexcept;
        IpEndPoint(const struct sockaddr_in& address) noexcept;
        IpEndPoint(const struct sockaddr_in6& address) noexcept;
        IpEndPoint(const struct sockaddr* address, socklen_t length) noexcept;


    public:
        IpAddress GetAddress() const noexcept;
        void SetAddress(const IpAddress& address) noexcept;

        uint16_t GetPort() const noexcept;
        void SetPort(uint16_t value) noexcept;

        AddressFamily GetFamily() const noexcept;

        const sockaddr* GetSockAddr() const noexcept;
        socklen_t GetSockLength() const noexcept;

    public:
        static constexpr const int MinPort = 0;
        static constexpr const int MaxPort = 65535;

    public:
        static bool TryParse(IpEndPoint& out_result, const char* value) noexcept;
        bool ToString(std::string& out_result) const noexcept;
    };
}
