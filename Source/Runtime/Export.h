#pragma once

#ifdef GAMBIT_RUNTIME_EXPORTS
#define GAMBIT_RUNTIME_API __declspec(dllexport)
#else
#define GAMBIT_RUNTIME_API __declspec(dllimport)
#endif