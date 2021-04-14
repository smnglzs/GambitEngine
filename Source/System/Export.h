#pragma once

#ifdef GAMBIT_SYSTEM_EXPORTS
#define GAMBIT_SYSTEM_API __declspec(dllexport)
#else
#define GAMBIT_SYSTEM_API __declspec(dllimport)
#endif