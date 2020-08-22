#pragma once

#ifdef GAMBIT_GRAPHICS_EXPORTS
#define GAMBIT_GRAPHICS_API __declspec(dllexport)
#else
#define GAMBIT_GRAPHICS_API __declspec(dllimport)
#endif