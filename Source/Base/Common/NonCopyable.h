#pragma once

#include "Base/Export.h"

namespace gb
{
    class GAMBIT_BASE_API NonCopyable
    {
    public:
        NonCopyable(   const NonCopyable&) = delete;
        void operator=(const NonCopyable&) = delete;

    protected:
        NonCopyable()  = default;
        ~NonCopyable() = default;
    };

    class GAMBIT_BASE_API NoCopyNoMove
    {
    public:
        NoCopyNoMove(  const NoCopyNoMove&  other) = delete;
        NoCopyNoMove(        NoCopyNoMove&& other) = delete;
        void operator=(const NoCopyNoMove&  other) = delete;
        void operator=(      NoCopyNoMove&& other) = delete;

    protected:
        NoCopyNoMove()  = default;
        ~NoCopyNoMove() = default;
    };
}