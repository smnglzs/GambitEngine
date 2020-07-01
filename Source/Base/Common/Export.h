#pragma once

#ifdef GAMBIT_BASE_EXPORTS
#define GAMBIT_BASE_API __declspec(dllexport)
#else
#define GAMBIT_BASE_API __declspec(dllimport)
#endif