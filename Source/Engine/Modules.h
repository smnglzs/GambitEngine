#pragma once

// To use modules, the application must define one or more of the below.

#ifdef GB_ALL_MODULES
#define GB_BASE_MODULE
#define GB_SYSTEM_MODULE
#define GB_GRAPHICS_MODULE
#define GB_RUNTIME_MODULE
#endif

#ifdef GB_BASE_MODULE
#include "Base/BaseModule.h"
#endif

#ifdef GB_SYSTEM_MODULE
#include "System/SystemModule.h"
#endif

#ifdef GB_GRAPHICS_MODULE
#include "Graphics/GraphicsModule.h"
#endif

#ifdef GB_RUNTIME_MODULE
#include "Runtime/RuntimeModule.h"
#endif