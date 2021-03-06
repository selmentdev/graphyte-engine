#pragma once
#include <GxBase/Platform/Impl/Detect.hxx>

#if GX_STATIC_BUILD
#define ASSETS_SHADER_API
#else
#if defined(assets_shader_EXPORTS)
#define ASSETS_SHADER_API GX_MODULE_EXPORT
#else
#define ASSETS_SHADER_API GX_MODULE_IMPORT
#endif
#endif
