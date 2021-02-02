#define NM_CORE_SIMD_IMPLEMENTATION_UNKNOWN 0
#define NM_CORE_SIMD_IMPLEMENTATION_COMMON  1
#define NM_CORE_SIMD_IMPLEMENTATION_X86     2

#if !defined(NM_CORE_SIMD_IMPLEMENTATION)
#    error Please define an implementation to use.
#endif

#if NM_CORE_SIMD_IMPLEMENTATION == NM_CORE_SIMD_IMPLEMENTATION_COMMON
#    include "randoms/foundation/frameworks/core/simd/common/common.hpp"
#endif

#if NM_CORE_SIMD_IMPLEMENTATION == NM_CORE_SIMD_IMPLEMENTATION_X86
#    include "randoms/foundation/frameworks/core/simd/x86/x86.hpp"
#endif

namespace next_mode {
    namespace core::simd::detail {
#if NM_CORE_SIMD_IMPLEMENTATION == NM_CORE_SIMD_IMPLEMENTATION_COMMON
        using Arithmetic_Export      = Arithmetic_Common_Export;
        using BitManipulation_Export = BitManipulation_Common_Export;
        using Cast_Export            = Cast_Common_Export;
        using Compare_Export         = Compare_Common_Export;
        using Convert_Export         = Convert_Common_Export;
        using Cryptography_Export    = Cryptography_Common_Export;
        using Load_Export            = Load_Common_Export;
        using Logical_Export         = Logical_Common_Export;
        using Mask_Export            = Mask_Common_Export;
        using Math_Export            = Math_Common_Export;
        using Miscellaneous_Export   = Miscellaneous_Common_Export;
        using Move_Export            = Move_Common_Export;
        using Random_Export          = Random_Common_Export;
        using Set_Export             = Set_Common_Export;
        using Statistics_Export      = Statistics_Common_Export;
        using Store_Export           = Store_Common_Export;
        using String_Export          = String_Common_Export;
        using Swizzle_Export         = Swizzle_Common_Export;
        using Trigonometry_Export    = Trigonometry_Common_Export;
#endif

#if NM_CORE_SIMD_IMPLEMENTATION == NM_CORE_SIMD_IMPLEMENTATION_X86
        using Arithmetic_Export      = Arithmetic_X86_Export;
        using BitManipulation_Export = BitManipulation_X86_Export;
        using Cast_Export            = Cast_X86_Export;
        using Compare_Export         = Compare_X86_Export;
        using Convert_Export         = Convert_X86_Export;
        using Cryptography_Export    = Cryptography_X86_Export;
        using Load_Export            = Load_X86_Export;
        using Logical_Export         = Logical_X86_Export;
        using Mask_Export            = Mask_X86_Export;
        using Math_Export            = Math_X86_Export;
        using Miscellaneous_Export   = Miscellaneous_X86_Export;
        using Move_Export            = Move_X86_Export;
        using Random_Export          = Random_X86_Export;
        using Set_Export             = Set_X86_Export;
        using Statistics_Export      = Statistics_X86_Export;
        using Store_Export           = Store_X86_Export;
        using String_Export          = String_X86_Export;
        using Swizzle_Export         = Swizzle_X86_Export;
        using Trigonometry_Export    = Trigonometry_X86_Export;
#endif
    } // namespace core::simd::detail
} // namespace next_mode
