#include "Test.Base.pch.hxx"
#include <Graphyte/Network/IpAddress.hxx>

TEST_CASE("IpAddress specials")
{
    using Graphyte::Network::IpAddress;
    using Graphyte::Network::AddressFamily;

    SECTION("Unknown family")
    {
        SECTION("Any")
        {
            auto address = IpAddress::Any(AddressFamily::Unspecified);
            CHECK(address.IsAny() == false);
            CHECK(address.IsBroadcast() == false);
            CHECK(address.IsGlobalMulticast() == false);
            CHECK(address.IsLinkLocal() == false);
            CHECK(address.IsLinkLocalMulticast() == false);
            CHECK(address.IsLoopback() == false);
            CHECK(address.IsMulticast() == false);
            CHECK(address.IsNodeLocalMulticast() == false);
            CHECK(address.IsOrgLocalMulticast() == false);
            CHECK(address.IsSiteLocal() == false);
            CHECK(address.IsSiteLocalMulticast() == false);
            CHECK(address.IsUnicast() == true);
            CHECK(address.IsV4() == false);
            CHECK(address.IsV4Compatible() == false);
            CHECK(address.IsV4Mapped() == false);
            CHECK(address.IsV6() == false);
            CHECK(address.IsWellKnownMulticast() == false);
        }

        SECTION("Broadcast")
        {
            auto address = IpAddress::Broadcast(AddressFamily::Unspecified);
            CHECK(address.IsAny() == false);
            CHECK(address.IsBroadcast() == false);
            CHECK(address.IsGlobalMulticast() == false);
            CHECK(address.IsLinkLocal() == false);
            CHECK(address.IsLinkLocalMulticast() == false);
            CHECK(address.IsLoopback() == false);
            CHECK(address.IsMulticast() == false);
            CHECK(address.IsNodeLocalMulticast() == false);
            CHECK(address.IsOrgLocalMulticast() == false);
            CHECK(address.IsSiteLocal() == false);
            CHECK(address.IsSiteLocalMulticast() == false);
            CHECK(address.IsUnicast() == true);
            CHECK(address.IsV4() == false);
            CHECK(address.IsV4Compatible() == false);
            CHECK(address.IsV4Mapped() == false);
            CHECK(address.IsV6() == false);
            CHECK(address.IsWellKnownMulticast() == false);
        }

        SECTION("Loopback")
        {
            auto address = IpAddress::Loopback(AddressFamily::Unspecified);
            CHECK(address.IsAny() == false);
            CHECK(address.IsBroadcast() == false);
            CHECK(address.IsGlobalMulticast() == false);
            CHECK(address.IsLinkLocal() == false);
            CHECK(address.IsLinkLocalMulticast() == false);
            CHECK(address.IsLoopback() == false);
            CHECK(address.IsMulticast() == false);
            CHECK(address.IsNodeLocalMulticast() == false);
            CHECK(address.IsOrgLocalMulticast() == false);
            CHECK(address.IsSiteLocal() == false);
            CHECK(address.IsSiteLocalMulticast() == false);
            CHECK(address.IsUnicast() == true);
            CHECK(address.IsV4() == false);
            CHECK(address.IsV4Compatible() == false);
            CHECK(address.IsV4Mapped() == false);
            CHECK(address.IsV6() == false);
            CHECK(address.IsWellKnownMulticast() == false);
        }

        SECTION("None")
        {
            auto address = IpAddress::None(AddressFamily::Unspecified);
            CHECK(address.IsAny() == false);
            CHECK(address.IsBroadcast() == false);
            CHECK(address.IsGlobalMulticast() == false);
            CHECK(address.IsLinkLocal() == false);
            CHECK(address.IsLinkLocalMulticast() == false);
            CHECK(address.IsLoopback() == false);
            CHECK(address.IsMulticast() == false);
            CHECK(address.IsNodeLocalMulticast() == false);
            CHECK(address.IsOrgLocalMulticast() == false);
            CHECK(address.IsSiteLocal() == false);
            CHECK(address.IsSiteLocalMulticast() == false);
            CHECK(address.IsUnicast() == true);
            CHECK(address.IsV4() == false);
            CHECK(address.IsV4Compatible() == false);
            CHECK(address.IsV4Mapped() == false);
            CHECK(address.IsV6() == false);
            CHECK(address.IsWellKnownMulticast() == false);
        }
    }

    SECTION("IPv4")
    {
        SECTION("Any")
        {
            auto address = IpAddress::Any(AddressFamily::IpV4);
            CHECK(address.IsAny() == true);
            CHECK(address.IsBroadcast() == false);
            CHECK(address.IsGlobalMulticast() == false);
            CHECK(address.IsLinkLocal() == false);
            CHECK(address.IsLinkLocalMulticast() == false);
            CHECK(address.IsLoopback() == false);
            CHECK(address.IsMulticast() == false);
            CHECK(address.IsNodeLocalMulticast() == false);
            CHECK(address.IsOrgLocalMulticast() == false);
            CHECK(address.IsSiteLocal() == false);
            CHECK(address.IsSiteLocalMulticast() == false);
            CHECK(address.IsUnicast() == false);
            CHECK(address.IsV4() == true);
            CHECK(address.IsV4Compatible() == true);
            CHECK(address.IsV4Mapped() == true);
            CHECK(address.IsV6() == false);
            CHECK(address.IsWellKnownMulticast() == false);
        }

        SECTION("Broadcast")
        {
            auto address = IpAddress::Broadcast(AddressFamily::IpV4);
            CHECK(address.IsAny() == false);
            CHECK(address.IsBroadcast() == true);
            CHECK(address.IsGlobalMulticast() == false);
            CHECK(address.IsLinkLocal() == false);
            CHECK(address.IsLinkLocalMulticast() == false);
            CHECK(address.IsLoopback() == false);
            CHECK(address.IsMulticast() == false);
            CHECK(address.IsNodeLocalMulticast() == false);
            CHECK(address.IsOrgLocalMulticast() == false);
            CHECK(address.IsSiteLocal() == false);
            CHECK(address.IsSiteLocalMulticast() == false);
            CHECK(address.IsUnicast() == false);
            CHECK(address.IsV4() == true);
            CHECK(address.IsV4Compatible() == true);
            CHECK(address.IsV4Mapped() == true);
            CHECK(address.IsV6() == false);
            CHECK(address.IsWellKnownMulticast() == false);
        }

        SECTION("Loopback")
        {
            auto address = IpAddress::Loopback(AddressFamily::IpV4);
            CHECK(address.IsAny() == false);
            CHECK(address.IsBroadcast() == false);
            CHECK(address.IsGlobalMulticast() == false);
            CHECK(address.IsLinkLocal() == false);
            CHECK(address.IsLinkLocalMulticast() == false);
            CHECK(address.IsLoopback() == false);
            CHECK(address.IsMulticast() == false);
            CHECK(address.IsNodeLocalMulticast() == false);
            CHECK(address.IsOrgLocalMulticast() == false);
            CHECK(address.IsSiteLocal() == false);
            CHECK(address.IsSiteLocalMulticast() == false);
            CHECK(address.IsUnicast() == true);
            CHECK(address.IsV4() == true);
            CHECK(address.IsV4Compatible() == true);
            CHECK(address.IsV4Mapped() == true);
            CHECK(address.IsV6() == false);
            CHECK(address.IsWellKnownMulticast() == false);
        }

        SECTION("None")
        {
            auto address = IpAddress::None(AddressFamily::IpV4);
            CHECK(address.IsAny() == false);
            CHECK(address.IsBroadcast() == true);
            CHECK(address.IsGlobalMulticast() == false);
            CHECK(address.IsLinkLocal() == false);
            CHECK(address.IsLinkLocalMulticast() == false);
            CHECK(address.IsLoopback() == false);
            CHECK(address.IsMulticast() == false);
            CHECK(address.IsNodeLocalMulticast() == false);
            CHECK(address.IsOrgLocalMulticast() == false);
            CHECK(address.IsSiteLocal() == false);
            CHECK(address.IsSiteLocalMulticast() == false);
            CHECK(address.IsUnicast() == false);
            CHECK(address.IsV4() == true);
            CHECK(address.IsV4Compatible() == true);
            CHECK(address.IsV4Mapped() == true);
            CHECK(address.IsV6() == false);
            CHECK(address.IsWellKnownMulticast() == false);
        }
    }

    SECTION("IPv6")
    {
        SECTION("Any")
        {
            auto address = IpAddress::Any(AddressFamily::IpV6);
            CHECK(address.IsAny() == true);
            CHECK(address.IsBroadcast() == false);
            CHECK(address.IsGlobalMulticast() == false);
            CHECK(address.IsLinkLocal() == false);
            CHECK(address.IsLinkLocalMulticast() == false);
            CHECK(address.IsLoopback() == false);
            CHECK(address.IsMulticast() == false);
            CHECK(address.IsNodeLocalMulticast() == false);
            CHECK(address.IsOrgLocalMulticast() == false);
            CHECK(address.IsSiteLocal() == false);
            CHECK(address.IsSiteLocalMulticast() == false);
            CHECK(address.IsUnicast() == false);
            CHECK(address.IsV4() == false);
            CHECK(address.IsV4Compatible() == true);
            CHECK(address.IsV4Mapped() == false);
            CHECK(address.IsV6() == true);
            CHECK(address.IsWellKnownMulticast() == false);
        }

        SECTION("Broadcast")
        {
            auto address = IpAddress::Broadcast(AddressFamily::IpV6);
            CHECK(address.IsAny() == true);
            CHECK(address.IsBroadcast() == false);
            CHECK(address.IsGlobalMulticast() == false);
            CHECK(address.IsLinkLocal() == false);
            CHECK(address.IsLinkLocalMulticast() == false);
            CHECK(address.IsLoopback() == false);
            CHECK(address.IsMulticast() == false);
            CHECK(address.IsNodeLocalMulticast() == false);
            CHECK(address.IsOrgLocalMulticast() == false);
            CHECK(address.IsSiteLocal() == false);
            CHECK(address.IsSiteLocalMulticast() == false);
            CHECK(address.IsUnicast() == false);
            CHECK(address.IsV4() == false);
            CHECK(address.IsV4Compatible() == true);
            CHECK(address.IsV4Mapped() == false);
            CHECK(address.IsV6() == true);
            CHECK(address.IsWellKnownMulticast() == false);
        }

        SECTION("Loopback")
        {
            auto address = IpAddress::Loopback(AddressFamily::IpV6);
            CHECK(address.IsAny() == false);
            CHECK(address.IsBroadcast() == false);
            CHECK(address.IsGlobalMulticast() == false);
            CHECK(address.IsLinkLocal() == false);
            CHECK(address.IsLinkLocalMulticast() == false);
            CHECK(address.IsLoopback() == true);
            CHECK(address.IsMulticast() == false);
            CHECK(address.IsNodeLocalMulticast() == false);
            CHECK(address.IsOrgLocalMulticast() == false);
            CHECK(address.IsSiteLocal() == false);
            CHECK(address.IsSiteLocalMulticast() == false);
            CHECK(address.IsUnicast() == true);
            CHECK(address.IsV4() == false);
            CHECK(address.IsV4Compatible() == true);
            CHECK(address.IsV4Mapped() == false);
            CHECK(address.IsV6() == true);
            CHECK(address.IsWellKnownMulticast() == false);
        }

        SECTION("None")
        {
            auto address = IpAddress::None(AddressFamily::IpV6);
            CHECK(address.IsAny() == true);
            CHECK(address.IsBroadcast() == false);
            CHECK(address.IsGlobalMulticast() == false);
            CHECK(address.IsLinkLocal() == false);
            CHECK(address.IsLinkLocalMulticast() == false);
            CHECK(address.IsLoopback() == false);
            CHECK(address.IsMulticast() == false);
            CHECK(address.IsNodeLocalMulticast() == false);
            CHECK(address.IsOrgLocalMulticast() == false);
            CHECK(address.IsSiteLocal() == false);
            CHECK(address.IsSiteLocalMulticast() == false);
            CHECK(address.IsUnicast() == false);
            CHECK(address.IsV4() == false);
            CHECK(address.IsV4Compatible() == true);
            CHECK(address.IsV4Mapped() == false);
            CHECK(address.IsV6() == true);
            CHECK(address.IsWellKnownMulticast() == false);
        }
    }
}
