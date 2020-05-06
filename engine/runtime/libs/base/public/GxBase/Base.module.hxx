#pragma once
#include <GxBase/Platform/Impl/Detect.hxx>

#if GX_STATIC_BUILD
#define BASE_API
#else
#if defined(module_base_EXPORTS)
#define BASE_API    GX_LIB_EXPORT
#else
#define BASE_API    GX_LIB_IMPORT
#endif
#endif
