#pragma once

#include "randoms/foundation/frameworks/core/types/internal.hpp"

namespace next_mode::core::types::detail {
    struct Integer_Common_General {
        using Signed8    = signed char;
        using Signed16   = signed short;
        using Signed32   = signed int;
        using Signed64   = signed long long;
        using Unsigned8  = unsigned char;
        using Unsigned16 = unsigned short;
        using Unsigned32 = unsigned int;
        using Unsigned64 = unsigned long long;
    };
} // namespace next_mode::core::types::detail
