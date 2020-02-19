#include <Graphyte/Network.hxx>
#include <Graphyte/Diagnostics.hxx>

#define GRAPHYTE_SDKS_WITH_CURL 0

#if GRAPHYTE_SDKS_WITH_CURL
#include <curl/curl.h>
#endif

#if GRAPHYTE_PLATFORM_WINDOWS
#include <netlistmgr.h>
#include <wrl/client.h>

namespace Graphyte::Network::Impl::Windows
{
    Microsoft::WRL::ComPtr<INetworkListManager> GNetworkListManager{};
}

#endif

#if GRAPHYTE_SDKS_WITH_CURL
namespace Graphyte::Network::Impl
{
    static size_t CURL_Client_Download_WriteCallback(
        void* content,
        size_t size,
        size_t count,
        void* context
    )
    {
        GX_ASSERT(context != nullptr);

        auto* buffer = reinterpret_cast<std::vector<std::byte>*>(context);

        size_t content_size = size * count;
        std::byte* content_typed = reinterpret_cast<std::byte*>(content);

        std::copy_n(content_typed, content_size, std::back_inserter(*buffer));
        return content_size;
    }
}
#endif

namespace Graphyte::Network
{
    BASE_API void Initialize() noexcept
    {
        //
        // Do platform-specific initialization.
        //

#if GRAPHYTE_PLATFORM_WINDOWS

        HRESULT hr = CoCreateInstance(
            CLSID_NetworkListManager,
            nullptr,
            CLSCTX_ALL,
            IID_INetworkListManager,
            reinterpret_cast<LPVOID*>(Impl::Windows::GNetworkListManager.GetAddressOf())
        );

        GX_ABORT_UNLESS(SUCCEEDED(hr),
            "Failed to initialize network subsystem: ({:08x}, {})",
            hr,
            Diagnostics::GetMessageFromHRESULT(hr)
        );

        GX_ASSERT(Impl::Windows::GNetworkListManager != nullptr);


#elif GRAPHYTE_PLATFORM_LINUX
#else
#   error Not supported
#endif

#if GRAPHYTE_SDKS_WITH_CURL
        //
        // Initialize CURL.
        //

        [[maybe_unused]] CURLcode curl_status = curl_global_init(CURL_GLOBAL_ALL);
        GX_ASSERT(curl_status == CURLE_OK);
#endif
    }

    BASE_API void Finalize() noexcept
    {
#if GRAPHYTE_SDKS_WITH_CURL
        curl_global_cleanup();
#endif

#if GRAPHYTE_PLATFORM_WINDOWS
        Impl::Windows::GNetworkListManager = nullptr;
#endif
    }

    BASE_API Status HasInternetConnection(
        bool& status
    ) noexcept
    {
#if GRAPHYTE_PLATFORM_WINDOWS
        GX_ASSERT(Impl::Windows::GNetworkListManager != nullptr);

        VARIANT_BOOL result{};

        HRESULT hr = Impl::Windows::GNetworkListManager->get_IsConnectedToInternet(&result);

        if (SUCCEEDED(hr))
        {
            status = (result == VARIANT_TRUE);
            return Status::Success;
        }

        status = false;
        return Status::Failure;

#elif GRAPHYTE_PLATFORM_LINUX

        status = false;

        return Status::NotImplemented;

#else

#   error "Not supported"

        status = false;

        return Status::NotImplemented;

#endif
    }

    BASE_API Status Download(
        [[maybe_unused]] std::unique_ptr<std::byte[]>& result,
        [[maybe_unused]] size_t& size,
        [[maybe_unused]] std::string_view url
    ) noexcept
    {
#if GRAPHYTE_SDKS_WITH_CURL
        std::string url_string{ url.data(), url.size() };
        std::vector<std::byte> buffer{};

        CURLcode status = CURLE_OK;

        CURL* handle = curl_easy_init();

        status = curl_easy_setopt(handle, CURLOPT_URL, url_string.c_str());
        GX_ASSERT(status == CURLE_OK);

        status = curl_easy_setopt(handle, CURLOPT_WRITEDATA, reinterpret_cast<void*>(&buffer));
        GX_ASSERT(status == CURLE_OK);

        status = curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, Impl::CURL_Client_Download_WriteCallback);
        GX_ASSERT(status == CURLE_OK);

        status = curl_easy_setopt(handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        GX_ASSERT(status == CURLE_OK);

        status = curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
        GX_ASSERT(status == CURLE_OK);

        status = curl_easy_perform(handle);
        GX_ASSERTF(status == CURLE_OK, "CURL request failed with: {} (`{}`)",
            static_cast<uint32_t>(status),
            curl_easy_strerror(status)
        );

        result = std::make_unique<std::byte[]>(buffer.size());
        std::copy_n(buffer.data(), buffer.size(), result.get());
        size = buffer.size();

        curl_easy_cleanup(handle);

        if (status == CURLE_OK)
        {
            return Status::Success;
        }

        return Status::Failure;
#else
        return Status::NotImplemented;
#endif
    }
}
