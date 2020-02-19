#pragma once
#include <Graphyte/Platform.hxx>

#if defined(assets_script_EXPORTS)
#define ASSETS_SCRIPT_API   GX_LIB_EXPORT
#else
#define ASSETS_SCRIPT_API   GX_LIB_IMPORT
#endif
