#pragma once

#include "Base/Common/Export.h"

namespace gb
{
    class GAMBIT_API NonCopyable
    {
    public:
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator = (const NonCopyable&) = delete;

    protected:
        NonCopyable() = default;
        ~NonCopyable() = default;
    };
}