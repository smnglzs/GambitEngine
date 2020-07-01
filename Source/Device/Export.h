#pragma once

#ifdef GAMBIT_DEVICE_EXPORTS
#define GAMBIT_DEVICE_API __declspec(dllexport)
#else
#define GAMBIT_DEVICE_API __declspec(dllimport)
#endif