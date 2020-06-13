#pragma once

#ifdef GAMBIT_EXPORTS
	#define GAMBIT_API extern "C" __declspec(dllexport)
#else
	#define GAMBIT_API extern "C" __declspec(dllimport)
#endif

namespace Gambit
{
	GAMBIT_API void CallExample();
}