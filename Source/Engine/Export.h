#pragma once

#ifdef GAMBIT_ENGINE_EXPORTS
#define GAMBIT_ENGINE_API __declspec(dllexport)
#else
#define GAMBIT_ENGINE_API __declspec(dllimport)
#endif