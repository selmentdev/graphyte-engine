#pragma once
#include <GxBase/Platform/Impl/Detect.hxx>

#if GX_STATIC_BUILD
#define ASSETS_BASE_API
#else
#if defined(assets_base_EXPORTS)
#define ASSETS_BASE_API     GX_LIB_EXPORT
#else
#define ASSETS_BASE_API     GX_LIB_IMPORT
#endif
#endif
