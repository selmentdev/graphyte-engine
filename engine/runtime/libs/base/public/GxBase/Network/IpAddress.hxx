#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Network/Types.hxx>

namespace Graphyte::Network
{
    class BASE_API IpAddress final
    {
        friend class IpEndPoint;
    private:
        union AddressStorage
        {
            struct in6_addr v6;
            struct in_addr v4;
            uint8_t as_uint8[16];
            uint16_t as_uint16[8];
            uint32_t as_uint32[4];
            uint64_t as_uint64[2];
        } m_address;
        uint32_t m_scope_id;
        AddressFamily m_family;

    public:
        static constexpr const size_t IPv4AddressBytes = 4;
        static constexpr const size_t IPv6AddressBytes = 16;

    public:
        IpAddress() noexcept;
        IpAddress(const IpAddress& address) noexcept = default;
        IpAddress(IpAddress&& address) noexcept = default;
        IpAddress& operator=(const IpAddress&) noexcept = default;
        IpAddress& operator=(IpAddress&&) noexcept = default;
        
        explicit IpAddress(AddressFamily family) noexcept;
        explicit IpAddress(const struct in_addr& address) noexcept;
        explicit IpAddress(const struct in6_addr& address, uint32_t scope_id = 0) noexcept;

    public:
        static IpAddress MakeAddress(const void* address, socklen_t length) noexcept;
        static IpAddress MakeAddress(const void* address, socklen_t length, uint32_t scope_id) noexcept;
        static IpAddress MakeAddress(const struct sockaddr& address) noexcept;
        static IpAddress MakeAddress(const struct sockaddr_in& address) noexcept;
        static IpAddress MakeAddress(const struct sockaddr_in6& address) noexcept;

    public:
        AddressFamily Family() const noexcept;
        uint32_t ScopeId() const noexcept;

    public:
        bool IsV4() const noexcept;
        bool IsV6() const noexcept;
        bool IsAny() const noexcept;
        bool IsBroadcast() const noexcept;
        bool IsLoopback() const noexcept;
        bool IsMulticast() const noexcept;
        bool IsUnicast() const noexcept;
        bool IsLinkLocal() const noexcept;
        bool IsSiteLocal() const noexcept;
        bool IsV4Compatible() const noexcept;
        bool IsV4Mapped() const noexcept;
        bool IsWellKnownMulticast() const noexcept;
        bool IsNodeLocalMulticast() const noexcept;
        bool IsLinkLocalMulticast() const noexcept;
        bool IsSiteLocalMulticast() const noexcept;
        bool IsOrgLocalMulticast() const noexcept;
        bool IsGlobalMulticast() const noexcept;

    public:
        IpAddress MapToV4() const noexcept;
        IpAddress MapToV6() const noexcept;

    public:
        socklen_t Length() const noexcept;
        const void* Address() const noexcept;
        uint32_t PrefixLength() const noexcept;

    public:
        static IpAddress Mask(const IpAddress& address, const IpAddress& mask) noexcept;
        static IpAddress Mask(const IpAddress& address, const IpAddress& mask, const IpAddress& set) noexcept;

    public:
        bool ToBytesIPv4(std::array<std::uint8_t, 4>& result) noexcept;
        bool ToBytesIPv6(std::array<std::uint8_t, 16>& result) noexcept;
        bool ToString(std::string& result) const noexcept;
        static bool TryParse(IpAddress& result, const char* address) noexcept;
        static bool TryParse(IpAddress& result, const char* address, AddressFamily family) noexcept;

    public:
        static IpAddress Any(AddressFamily family) noexcept;
        static IpAddress Broadcast(AddressFamily family) noexcept;
        static IpAddress Loopback(AddressFamily family) noexcept;
        static IpAddress None(AddressFamily family) noexcept;
    };
}
