#pragma once

#define NM_CORE_TYPES_IMPLEMENTATION_UNKNOWN 0
#define NM_CORE_TYPES_IMPLEMENTATION_COMMON  1
#define NM_CORE_TYPES_IMPLEMENTATION_X86     2

#if !defined(NM_CORE_TYPES_IMPLEMENTATION)
#    error Please define an implementation to use.
#endif

#if NM_CORE_TYPES_IMPLEMENTATION == NM_CORE_TYPES_IMPLEMENTATION_COMMON
#    include "frameworks/core/types/common/common.hpp"
#endif

#if NM_CORE_TYPES_IMPLEMENTATION == NM_CORE_TYPES_IMPLEMENTATION_X86
#    include "frameworks/core/types/x86/x86.hpp"
#endif

namespace next_mode {
    namespace core::types::detail {
#if NM_CORE_TYPES_IMPLEMENTATION == NM_CORE_TYPES_IMPLEMENTATION_COMMON
        using Auxiliary_Export = Auxiliary_Common_Export;
        using Character_Export = Character_Common_Export;
        using Decimal_Export   = Decimal_Common_Export;
        using Integer_Export   = Integer_Common_Export;
        using Pack_Export      = Pack_Common_Export;
        using Pointer_Export   = Pointer_Common_Export;
#endif

#if NM_CORE_TYPES_IMPLEMENTATION == NM_CORE_TYPES_IMPLEMENTATION_X86
        using Auxiliary_Export = Auxiliary_X86_Export;
        using Character_Export = Character_X86_Export;
        using Decimal_Export   = Decimal_X86_Export;
        using Integer_Export   = Integer_X86_Export;
        using Pack_Export      = Pack_X86_Export;
        using Pointer_Export   = Pointer_X86_Export;
#endif
    } // namespace core::types::detail

    using Signed8            = core::types::detail::Integer_Export::Signed8;
    using Signed16           = core::types::detail::Integer_Export::Signed16;
    using Signed32           = core::types::detail::Integer_Export::Signed32;
    using Signed64           = core::types::detail::Integer_Export::Signed64;
    using Unsigned8          = core::types::detail::Integer_Export::Unsigned8;
    using Unsigned16         = core::types::detail::Integer_Export::Unsigned16;
    using Unsigned32         = core::types::detail::Integer_Export::Unsigned32;
    using Unsigned64         = core::types::detail::Integer_Export::Unsigned64;
    using Decimal32          = core::types::detail::Decimal_Export::Decimal32;
    using Decimal64          = core::types::detail::Decimal_Export::Decimal64;
    using SignedPointer      = core::types::detail::Pointer_Export::SignedPointer;
    using SignedIndex        = core::types::detail::Pointer_Export::SignedIndex;
    using SignedSize         = core::types::detail::Pointer_Export::SignedSize;
    using UnsignedPointer    = core::types::detail::Pointer_Export::UnsignedPointer;
    using UnsignedIndex      = core::types::detail::Pointer_Export::UnsignedIndex;
    using UnsignedSize       = core::types::detail::Pointer_Export::UnsignedSize;
    using ASCIICharacter     = core::types::detail::Character_Export::ASCIICharacter;
    using WideCharacter      = core::types::detail::Character_Export::WideCharacter;
    using UTF8Character      = core::types::detail::Character_Export::UTF8Character;
    using UTF16Character     = core::types::detail::Character_Export::UTF16Character;
    using UTF32Character     = core::types::detail::Character_Export::UTF32Character;
} // namespace next_mode

#include "frameworks/core/types/pack/pack.inl"
