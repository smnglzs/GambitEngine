#pragma once

#ifdef GAMBIT_EXPORTS
#define GAMBIT_API __declspec(dllexport)
#else
#define GAMBIT_API __declspec(dllimport)
#endif