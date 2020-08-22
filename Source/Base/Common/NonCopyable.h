#pragma once

#include "Base/Export.h"

namespace gb
{
    class GAMBIT_BASE_API NonCopyable
    {
    public:
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator = (const NonCopyable&) = delete;

    protected:
        NonCopyable() = default;
        ~NonCopyable() = default;
    };
}