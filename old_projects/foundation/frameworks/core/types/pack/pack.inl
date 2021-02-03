#include "randoms/foundation/frameworks/core/types/pack/pack_intrinsic_type.inl"
#include "randoms/foundation/frameworks/core/types/pack/pack_array_type.inl"
#include "randoms/foundation/frameworks/core/types/pack/pack_mask_intrinsic_type.inl"
#include "randoms/foundation/frameworks/core/types/pack/pack_mask_element_type.inl"

namespace next_mode {
    template <typename ElementTypeI, int WidthI>
    struct Pack {
        using ElementType   = ElementTypeI;
        using IntrinsicType = typename core::types::detail::PackIntrinsicType<ElementTypeI, WidthI>::Type;
        using ArrayType     = typename core::types::detail::PackArrayType<ElementTypeI, WidthI>::Type;

        static constexpr auto Width = WidthI;

        union {
            IntrinsicType intrinsic;
            ArrayType     elements;
        };

        Pack()
          : elements {ElementTypeI {0}} {
        }

        Pack(IntrinsicType intrinsic)
          : intrinsic {intrinsic} {
        }

        operator const IntrinsicType&() const {
            return this->intrinsic;
        }

        operator IntrinsicType&() {
            return this->intrinsic;
        }
    };

    using Pack_Signed8_1     = Pack<Signed8, 1>;
    using Pack_Signed8_2     = Pack<Signed8, 2>;
    using Pack_Signed8_4     = Pack<Signed8, 4>;
    using Pack_Signed8_8     = Pack<Signed8, 8>;
    using Pack_Signed8_16    = Pack<Signed8, 16>;
    using Pack_Signed8_32    = Pack<Signed8, 32>;
    using Pack_Signed8_64    = Pack<Signed8, 64>;
    using Pack_Signed16_1    = Pack<Signed16, 1>;
    using Pack_Signed16_2    = Pack<Signed16, 2>;
    using Pack_Signed16_4    = Pack<Signed16, 4>;
    using Pack_Signed16_8    = Pack<Signed16, 8>;
    using Pack_Signed16_16   = Pack<Signed16, 16>;
    using Pack_Signed16_32   = Pack<Signed16, 32>;
    using Pack_Signed32_1    = Pack<Signed32, 1>;
    using Pack_Signed32_2    = Pack<Signed32, 2>;
    using Pack_Signed32_4    = Pack<Signed32, 4>;
    using Pack_Signed32_8    = Pack<Signed32, 8>;
    using Pack_Signed32_16   = Pack<Signed32, 16>;
    using Pack_Signed64_1    = Pack<Signed64, 1>;
    using Pack_Signed64_2    = Pack<Signed64, 2>;
    using Pack_Signed64_4    = Pack<Signed64, 4>;
    using Pack_Signed64_8    = Pack<Signed64, 8>;
    using Pack_Unsigned8_1   = Pack<Unsigned8, 1>;
    using Pack_Unsigned8_2   = Pack<Unsigned8, 2>;
    using Pack_Unsigned8_4   = Pack<Unsigned8, 4>;
    using Pack_Unsigned8_8   = Pack<Unsigned8, 8>;
    using Pack_Unsigned8_16  = Pack<Unsigned8, 16>;
    using Pack_Unsigned8_32  = Pack<Unsigned8, 32>;
    using Pack_Unsigned8_64  = Pack<Unsigned8, 64>;
    using Pack_Unsigned16_1  = Pack<Unsigned16, 1>;
    using Pack_Unsigned16_2  = Pack<Unsigned16, 2>;
    using Pack_Unsigned16_4  = Pack<Unsigned16, 4>;
    using Pack_Unsigned16_8  = Pack<Unsigned16, 8>;
    using Pack_Unsigned16_16 = Pack<Unsigned16, 16>;
    using Pack_Unsigned16_32 = Pack<Unsigned16, 32>;
    using Pack_Unsigned32_1  = Pack<Unsigned32, 1>;
    using Pack_Unsigned32_2  = Pack<Unsigned32, 2>;
    using Pack_Unsigned32_4  = Pack<Unsigned32, 4>;
    using Pack_Unsigned32_8  = Pack<Unsigned32, 8>;
    using Pack_Unsigned32_16 = Pack<Unsigned32, 16>;
    using Pack_Unsigned64_1  = Pack<Unsigned64, 1>;
    using Pack_Unsigned64_2  = Pack<Unsigned64, 2>;
    using Pack_Unsigned64_4  = Pack<Unsigned64, 4>;
    using Pack_Unsigned64_8  = Pack<Unsigned64, 8>;
    using Pack_Decimal32_1   = Pack<Decimal32, 1>;
    using Pack_Decimal32_2   = Pack<Decimal32, 2>;
    using Pack_Decimal32_4   = Pack<Decimal32, 4>;
    using Pack_Decimal32_8   = Pack<Decimal32, 8>;
    using Pack_Decimal32_16  = Pack<Decimal32, 16>;
    using Pack_Decimal64_1   = Pack<Decimal64, 1>;
    using Pack_Decimal64_2   = Pack<Decimal64, 2>;
    using Pack_Decimal64_4   = Pack<Decimal64, 4>;
    using Pack_Decimal64_8   = Pack<Decimal64, 8>;
    using Pack_Mask8         = core::types::detail::Pack_Export::Pack_Mask8;
    using Pack_Mask16        = core::types::detail::Pack_Export::Pack_Mask16;
    using Pack_Mask32        = core::types::detail::Pack_Export::Pack_Mask32;
    using Pack_Mask64        = core::types::detail::Pack_Export::Pack_Mask64;
} // namespace next_mode
