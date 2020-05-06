#pragma once
#include <GxBase/Base.module.hxx>

namespace Graphyte::Network
{
    enum class WaitStatus
    {
        Success,
        Failure,
        Timeout,
    };

    enum class AddressFamily
    {
        Unknown = -1,
        Unspecified = AF_UNSPEC,
        IpV4 = AF_INET,
        IpV6 = AF_INET6,
    };

    enum class SocketType
    {
        Stream = SOCK_STREAM,
        Datagram = SOCK_DGRAM,
        Raw = SOCK_RAW,
        Rdm = SOCK_RDM,
        SequentialPacket = SOCK_SEQPACKET,
    };

    enum class ProtocolType
    {
        Unknown = -1,
        Unspecified = 0,
        IpV4 = IPPROTO_IP,
        IpV6 = IPPROTO_IPV6,
        Tcp = IPPROTO_TCP,
        Udp = IPPROTO_UDP,
    };

    enum class SocketError
    {
        UnknownError = -1,
        Success = 0,

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
#define SELECT_VALUE(X, Y, ...)     X
#elif GRAPHYTE_PLATFORM_LINUX || GRAPHYTE_PLATFORM_ANDROID
#define SELECT_VALUE(X, Y, ...)     Y
#endif
        AccessDenied = SELECT_VALUE(WSAEACCES, EINTR),
        AddressAlreadyInUse = SELECT_VALUE(WSAEADDRINUSE, EADDRINUSE),
        AddressFamilyNotSupported = SELECT_VALUE(WSAEAFNOSUPPORT, EAFNOSUPPORT),
        AddressNotAvailable = SELECT_VALUE(WSAEADDRNOTAVAIL, EADDRNOTAVAIL),
        AlreadyInProgress = SELECT_VALUE(WSAEALREADY, EALREADY),
        ConnectionAborted = SELECT_VALUE(WSAECONNABORTED, EALREADY),
        ConnectionRefused = SELECT_VALUE(WSAECONNREFUSED, ECONNREFUSED),
        ConnectionReset = SELECT_VALUE(WSAECONNRESET, ECONNRESET),
        DestinationAddressRequired = SELECT_VALUE(WSAEDESTADDRREQ, EDESTADDRREQ),
        Disconnecting = SELECT_VALUE(WSAEDISCON, ESHUTDOWN),
        Fault = SELECT_VALUE(WSAEFAULT, EFAULT),
        HostDown = SELECT_VALUE(WSAEHOSTDOWN, EHOSTDOWN),
        HostNotFound = SELECT_VALUE(WSAHOST_NOT_FOUND, ENXIO),
        HostUnreachable = SELECT_VALUE(WSAEHOSTUNREACH, EHOSTUNREACH),
        InProgress = SELECT_VALUE(WSAEINPROGRESS, EINPROGRESS),
        Interrupted = SELECT_VALUE(WSAEINTR, EINTR),
        InvalidArgument = SELECT_VALUE(WSAEINVAL, EINVAL),
        IsConnected = SELECT_VALUE(WSAEISCONN, EISCONN),
        MessageSize = SELECT_VALUE(WSAEMSGSIZE, EMSGSIZE),
        NetworkDown = SELECT_VALUE(WSAENETDOWN, ENETDOWN),
        NetworkReset = SELECT_VALUE(WSAENETRESET, ENETRESET),
        NetworkUnreachable = SELECT_VALUE(WSAENETUNREACH, ENETUNREACH),
        NoBufferSpaceAvailable = SELECT_VALUE(WSAENOBUFS, ENOBUFS),
        NoData = SELECT_VALUE(WSANO_DATA, ENODATA),
        NotConnected = SELECT_VALUE(WSAENOTCONN, ENOTCONN),
        NotSocket = SELECT_VALUE(WSAENOTSOCK, ENOTSOCK),
        OperationNotSupported = SELECT_VALUE(WSAEOPNOTSUPP, EOPNOTSUPP),
        ProtocolFamilyNotSupported = SELECT_VALUE(WSAEPFNOSUPPORT, EPFNOSUPPORT),
        ProtocolNotSupported = SELECT_VALUE(WSAEPROTONOSUPPORT, EPROTONOSUPPORT),
        ProtocolOption = SELECT_VALUE(WSAENOPROTOOPT, ENOPROTOOPT),
        ProtocolType = SELECT_VALUE(WSAEPROTOTYPE, EPROTOTYPE),
        Shutdown = SELECT_VALUE(WSAESHUTDOWN, EPIPE),
        SocketNotSupported = SELECT_VALUE(WSAESOCKTNOSUPPORT, ESOCKTNOSUPPORT),
        TimedOut = SELECT_VALUE(WSAETIMEDOUT, ETIMEDOUT),
        TooManyOpenSockets = SELECT_VALUE(WSAEMFILE, EMFILE),
        TryAgain = SELECT_VALUE(WSATRY_AGAIN, EAGAIN),
        WouldBlock = SELECT_VALUE(WSAEWOULDBLOCK, EWOULDBLOCK),
        AddressTooLong = SELECT_VALUE(WSAENAMETOOLONG, ENAMETOOLONG),
        NoRecovery = SELECT_VALUE(WSANO_RECOVERY, SocketError::UnknownError),
        NotInitialized = SELECT_VALUE(WSANOTINITIALISED, SocketError::UnknownError),
        ProcessLimit = SELECT_VALUE(WSAEPROCLIM, SocketError::UnknownError),
        SystemNotReady = SELECT_VALUE(WSASYSNOTREADY, SocketError::UnknownError),
        TypeNotFound = SELECT_VALUE(WSATYPE_NOT_FOUND, SocketError::UnknownError),
        VersionNotSupported = SELECT_VALUE(WSAVERNOTSUPPORTED, SocketError::UnknownError),
#undef SELECT_VALUE
    };


    enum class SocketFlags
    {
        None = 0,
        OutOfBand = (1 << 0),
        Peek = (1 << 1),
        DontRoute = (1 << 2),
        Partial = (1 << 3),
        MaxIoVectorLength = (1 << 4),
    };
    GX_ENUM_CLASS_FLAGS(SocketFlags);

    enum class SocketEvents
    {
        None = 0,
        Read = (1 << 0),
        Write = (1 << 1),
        ReadClose = (1 << 2),
        Close = (1 << 3),
        Error = (1 << 4),
    };

    enum class PollFlags
    {
        None = 0,
        In = 0x1,
        Pri = 0x2,
        Out = 0x4,
        Err = 0x8,
        Hup = 0x10,
        Nval = 0x20,
        Any = -1,
    };
    GX_ENUM_CLASS_FLAGS(PollFlags);
}
