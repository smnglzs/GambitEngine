#pragma once

#include <cassert>

#if defined(_DEBUG)
#define GB_TODO_IMPL throw std::exception("This function's implementation is incomplete.");
#else
#define GB_TODO_IMPL static_assert(false, "This function's implementation is incomplete.");
#endif