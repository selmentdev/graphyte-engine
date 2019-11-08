#pragma once
#include <Graphyte/Threading.hxx>


#if GRAPHYTE_PLATFORM_WINDOWS
#include <Graphyte/Threading/Impl.Windows/Windows.Thread.hxx>
#elif GRAPHYTE_PLATFORM_LINUX
#include <Graphyte/Threading/Impl.Linux/Linux.Thread.hxx>
#elif GRAPHYTE_PLATFORM_ANDROID
#include <Graphyte/Threading/Impl.Android/Android.Thread.hxx>
#else
#error "Unknown platform"
#endif
