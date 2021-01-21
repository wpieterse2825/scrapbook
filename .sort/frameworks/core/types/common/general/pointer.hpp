#pragma once

#include "frameworks/core/types/internal.hpp"

namespace next_mode::core::types::detail {
    struct Pointer_Common_General {
        static constexpr bool Is8BitPlatform   = false;
        static constexpr bool Is16BitPlatform  = false;
        static constexpr bool Is32BitPlatform  = false;
        static constexpr bool Is64BitPlatform  = false;
        static constexpr bool Is128BitPlatform = false;

        using SignedPointer   = void;
        using SignedIndex     = void;
        using SignedSize      = void;
        using UnsignedPointer = void;
        using UnsignedIndex   = void;
        using UnsignedSize    = void;
    };
} // namespace next_mode::core::types::detail
