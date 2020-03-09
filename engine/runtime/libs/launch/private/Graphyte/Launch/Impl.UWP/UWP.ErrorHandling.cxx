#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>
#include <Graphyte/Application.hxx>

#pragma warning(push)
#pragma warning(disable : 4715)

#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Web.Syndication.h>

namespace Graphyte::Launch
{
    void InitializeErrorHandling() noexcept
    {
        winrt::init_apartment();
        //using namespace winrt::Windows::Foundation;
        //using namespace ;

        winrt::Windows::Foundation::Uri rssFeedUri{ L"https://blogs.windows.com/feed" };
        winrt::Windows::Web::Syndication::SyndicationClient syndicationClient;
        winrt::Windows::Web::Syndication::SyndicationFeed syndicationFeed = syndicationClient.RetrieveFeedAsync(rssFeedUri).get();
        for (const winrt::Windows::Web::Syndication::SyndicationItem syndicationItem : syndicationFeed.Items())
        {
            winrt::hstring titleAsHstring = syndicationItem.Title().Text();
            wprintf(L"%s\n", titleAsHstring.c_str());
        }
    }
}

#pragma warning(pop)
