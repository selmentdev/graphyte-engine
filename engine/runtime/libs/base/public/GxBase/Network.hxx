#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Status.hxx>
//#include <GxBase/Network/IpEndPoint.hxx>

namespace Graphyte::Network
{
    BASE_API void Initialize() noexcept;

    BASE_API void Finalize() noexcept;

    BASE_API Status HasInternetConnection(
        bool& status
    ) noexcept;

#if false
    BASE_API Status Download(
        std::unique_ptr<std::byte[]>& result,
        size_t& size,
        std::string_view url
    ) noexcept;

    BASE_API Status ResolveDns(
        IpEndPoint& address,
        const char* host_name,
        const char* service_name = nullptr
    ) noexcept;

    BASE_API Status ResolveDns(
        std::vector<IpEndPoint>& address_list,
        const char* host_name,
        const char* service_name = nullptr
    ) noexcept;

    BASE_API Status ResolveDns(
        std::string& host,
        const IpEndPoint& address
    ) noexcept;

    BASE_API Status ResolveDns(
        std::vector<std::string>& host_list,
        const IpEndPoint& address
    ) noexcept;
#endif
}
