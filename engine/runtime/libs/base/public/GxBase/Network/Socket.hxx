#pragma once
#error Do not include now
#include <GxBase/Base.module.hxx>
#include <GxBase/Network/IpAddress.hxx>
#include <GxBase/Network/IpEndPoint.hxx>

namespace Graphyte::Network
{
    struct MulticastOptionIpV4
    {
        IpAddress MulticastAddress;
        IpAddress LocalAddress;
        int InterfaceIndex;
    };

    struct MulticastOptionIpV6
    {
        IpAddress Address;
        int InterfaceIndex;
    };

    struct PollRequest;

    class BASE_API Socket final
    {
    public:
        using SocketDescriptor = uint64_t;
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP
        using SocketHandle                                = SOCKET;
        static constexpr const SocketHandle InvalidHandle = INVALID_SOCKET;
        static constexpr const int SocketErrorValue       = SOCKET_ERROR;
#else
        using SocketHandle                                = int;
        static constexpr const SocketHandle InvalidHandle = -1;
        static constexpr const int SocketErrorValue       = -1;
#endif
    private:
        SocketHandle m_Handle;
        SocketError m_Error;

    public:
        Socket() noexcept;
        ~Socket() noexcept;
        Socket(const Socket&) = delete;
        Socket& operator=(const Socket&) = delete;

    public:
        SocketError GetError() const noexcept;
        bool IsClosed() const noexcept
        {
            return this->m_Handle == Socket::InvalidHandle;
        }

        WaitStatus Create(SocketDescriptor fd, int32_t family, int32_t type, int32_t protocol) noexcept;
        WaitStatus Create(AddressFamily family, SocketType type, ProtocolType protocol) noexcept;

        WaitStatus Close() noexcept;
        WaitStatus Listen() noexcept;
        WaitStatus Bind(const IpEndPoint& end_point) noexcept;
        WaitStatus Connect(const IpEndPoint& end_point) noexcept;
        WaitStatus Disconnect(bool reuse) noexcept;
        WaitStatus Shutdown(int32_t how) noexcept;
        WaitStatus GetLocalEndPoint(IpEndPoint& end_point) noexcept;
        WaitStatus GetRemoteEndPoint(IpEndPoint& end_point) noexcept;

        WaitStatus Receive(void* buffer, int32_t length, int32_t& out_received) noexcept;
        WaitStatus Receive(void* buffer, int32_t length, SocketFlags flags, int32_t& out_received) noexcept;

        WaitStatus Send(const void* buffer, int32_t length, int32_t& out_sent) noexcept;
        WaitStatus Send(const void* buffer, int32_t length, SocketFlags flags, int32_t& out_sent) noexcept;

        WaitStatus ReceiveFrom(IpEndPoint& end_point, const void* buffer, int32_t length, int32_t& out_received) noexcept;
        WaitStatus ReceiveFrom(IpEndPoint& end_point, const void* buffer, int32_t length, SocketFlags flags, int32_t& out_received) noexcept;

        WaitStatus SendTo(const IpEndPoint& end_point, const void* buffer, int32_t length, int32_t& out_sent) noexcept;
        WaitStatus SendTo(const IpEndPoint& end_point, const void* buffer, int32_t length, SocketFlags flags, int32_t& out_sent) noexcept;

        WaitStatus GetBytesAvailable(int32_t& amount) noexcept;

        WaitStatus Accept(Socket& out_socket) noexcept;

        WaitStatus IoControl(int32_t command, const void* data_in, size_t data_in_size, void* data_out, size_t data_out_size, int32_t* out_processed) noexcept;

        static WaitStatus Poll(std::vector<PollRequest>& requests, int32_t timeout, int32_t* result, int32_t* error) noexcept;

        static bool IsFamilySupported(AddressFamily family) noexcept;

        WaitStatus SetBlocking(bool blocking) noexcept;
        WaitStatus GetLinger(bool& status, int& seconds) const noexcept;
        WaitStatus SetLinger(bool status, int seconds) noexcept;
        WaitStatus SetDontFragment(bool& status) const noexcept;
        WaitStatus GetDontFragment(bool status) const noexcept;
        WaitStatus GetEnableBroadcast(bool& status) const noexcept;
        WaitStatus SetEnableBroadcast(bool status) const noexcept;
        WaitStatus GetAddressReuse(bool& status) const noexcept;
        WaitStatus SetAddressReuse(bool status) const noexcept;

        WaitStatus JoinMulticast(const IpEndPoint& multicast) noexcept;
        WaitStatus JoinMulticast(const IpEndPoint& multicast, const IpEndPoint& local) noexcept;
        WaitStatus JoinMulticast(int interface_index, const IpEndPoint& multicast) noexcept;
        WaitStatus DropMulticast(const IpEndPoint& multicast) noexcept;
        WaitStatus DropMulticast(int interface_index, const IpEndPoint& multicast) noexcept;

    private:
        WaitStatus SetSocketOptionInternal(int32_t level, int32_t name, const void* value, socklen_t length) noexcept
        {
            const int32_t result = setsockopt(this->m_Handle, level, name, static_cast<const char*>(value), static_cast<socklen_t>(length));

            if (result == -1)
            {
                this->StoreLastError();
                return WaitStatus::Failure;
            }

            return WaitStatus::Success;
        }

        WaitStatus GetSocketOptionInternal(int32_t level, int32_t name, void* value, socklen_t* length) noexcept
        {
            const int32_t result = getsockopt(this->m_Handle, level, name, static_cast<char*>(value), static_cast<socklen_t*>(length));

            if (result == -1)
            {
                this->StoreLastError();
                return WaitStatus::Failure;
            }

            return WaitStatus::Success;
        }

        void StoreLastError() noexcept
        {
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP
            this->m_Error = static_cast<SocketError>(WSAGetLastError());
#else
            this->m_Error = static_cast<SocketError>(errno);
#endif
        }
    };
}
