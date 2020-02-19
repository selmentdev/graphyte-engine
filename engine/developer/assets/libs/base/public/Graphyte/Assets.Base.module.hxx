#pragma once
#include <Graphyte/Platform/Impl/Detect.hxx>

#if GRAPHYTE_STATIC_BUILD
#define ASSETS_BASE_API
#else
#if defined(assets_base_EXPORTS)
#define ASSETS_BASE_API     GX_LIB_EXPORT
#else
#define ASSETS_BASE_API     GX_LIB_IMPORT
#endif
#endif
