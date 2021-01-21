namespace next_mode::core::types::detail {
    template <typename ElementType, int Width>
    struct PackIntrinsicTypeUnknown {};

    template <typename ElementType, int Width>
    struct PackIntrinsicType {
        using Type = PackIntrinsicTypeUnknown<ElementType, Width>;
    };

    template <>
    struct PackIntrinsicType<Signed8, 1> {
        using Type = Pack_Export::Pack_Signed8_1;
    };

    template <>
    struct PackIntrinsicType<Signed8, 2> {
        using Type = Pack_Export::Pack_Signed8_2;
    };

    template <>
    struct PackIntrinsicType<Signed8, 4> {
        using Type = Pack_Export::Pack_Signed8_4;
    };

    template <>
    struct PackIntrinsicType<Signed8, 8> {
        using Type = Pack_Export::Pack_Signed8_8;
    };

    template <>
    struct PackIntrinsicType<Signed8, 16> {
        using Type = Pack_Export::Pack_Signed8_16;
    };

    template <>
    struct PackIntrinsicType<Signed8, 32> {
        using Type = Pack_Export::Pack_Signed8_32;
    };

    template <>
    struct PackIntrinsicType<Signed8, 64> {
        using Type = Pack_Export::Pack_Signed8_64;
    };

    template <>
    struct PackIntrinsicType<Signed16, 1> {
        using Type = Pack_Export::Pack_Signed16_1;
    };

    template <>
    struct PackIntrinsicType<Signed16, 2> {
        using Type = Pack_Export::Pack_Signed16_2;
    };

    template <>
    struct PackIntrinsicType<Signed16, 4> {
        using Type = Pack_Export::Pack_Signed16_4;
    };

    template <>
    struct PackIntrinsicType<Signed16, 8> {
        using Type = Pack_Export::Pack_Signed16_8;
    };

    template <>
    struct PackIntrinsicType<Signed16, 16> {
        using Type = Pack_Export::Pack_Signed16_16;
    };

    template <>
    struct PackIntrinsicType<Signed16, 32> {
        using Type = Pack_Export::Pack_Signed16_32;
    };

    template <>
    struct PackIntrinsicType<Signed32, 1> {
        using Type = Pack_Export::Pack_Signed32_1;
    };

    template <>
    struct PackIntrinsicType<Signed32, 2> {
        using Type = Pack_Export::Pack_Signed32_2;
    };

    template <>
    struct PackIntrinsicType<Signed32, 4> {
        using Type = Pack_Export::Pack_Signed32_4;
    };

    template <>
    struct PackIntrinsicType<Signed32, 8> {
        using Type = Pack_Export::Pack_Signed32_8;
    };

    template <>
    struct PackIntrinsicType<Signed32, 16> {
        using Type = Pack_Export::Pack_Signed32_16;
    };

    template <>
    struct PackIntrinsicType<Signed64, 1> {
        using Type = Pack_Export::Pack_Signed64_1;
    };

    template <>
    struct PackIntrinsicType<Signed64, 2> {
        using Type = Pack_Export::Pack_Signed64_2;
    };

    template <>
    struct PackIntrinsicType<Signed64, 4> {
        using Type = Pack_Export::Pack_Signed64_4;
    };

    template <>
    struct PackIntrinsicType<Signed64, 8> {
        using Type = Pack_Export::Pack_Signed64_8;
    };

    template <>
    struct PackIntrinsicType<Unsigned8, 1> {
        using Type = Pack_Export::Pack_Unsigned8_1;
    };

    template <>
    struct PackIntrinsicType<Unsigned8, 2> {
        using Type = Pack_Export::Pack_Unsigned8_2;
    };

    template <>
    struct PackIntrinsicType<Unsigned8, 4> {
        using Type = Pack_Export::Pack_Unsigned8_4;
    };

    template <>
    struct PackIntrinsicType<Unsigned8, 8> {
        using Type = Pack_Export::Pack_Unsigned8_8;
    };

    template <>
    struct PackIntrinsicType<Unsigned8, 16> {
        using Type = Pack_Export::Pack_Unsigned8_16;
    };

    template <>
    struct PackIntrinsicType<Unsigned8, 32> {
        using Type = Pack_Export::Pack_Unsigned8_32;
    };

    template <>
    struct PackIntrinsicType<Unsigned8, 64> {
        using Type = Pack_Export::Pack_Unsigned8_64;
    };

    template <>
    struct PackIntrinsicType<Unsigned16, 1> {
        using Type = Pack_Export::Pack_Unsigned16_1;
    };

    template <>
    struct PackIntrinsicType<Unsigned16, 2> {
        using Type = Pack_Export::Pack_Unsigned16_2;
    };

    template <>
    struct PackIntrinsicType<Unsigned16, 4> {
        using Type = Pack_Export::Pack_Unsigned16_4;
    };

    template <>
    struct PackIntrinsicType<Unsigned16, 8> {
        using Type = Pack_Export::Pack_Unsigned16_8;
    };

    template <>
    struct PackIntrinsicType<Unsigned16, 16> {
        using Type = Pack_Export::Pack_Unsigned16_16;
    };

    template <>
    struct PackIntrinsicType<Unsigned16, 32> {
        using Type = Pack_Export::Pack_Unsigned16_32;
    };

    template <>
    struct PackIntrinsicType<Unsigned32, 1> {
        using Type = Pack_Export::Pack_Unsigned32_1;
    };

    template <>
    struct PackIntrinsicType<Unsigned32, 2> {
        using Type = Pack_Export::Pack_Unsigned32_2;
    };

    template <>
    struct PackIntrinsicType<Unsigned32, 4> {
        using Type = Pack_Export::Pack_Unsigned32_4;
    };

    template <>
    struct PackIntrinsicType<Unsigned32, 8> {
        using Type = Pack_Export::Pack_Unsigned32_8;
    };

    template <>
    struct PackIntrinsicType<Unsigned32, 16> {
        using Type = Pack_Export::Pack_Unsigned32_16;
    };

    template <>
    struct PackIntrinsicType<Unsigned64, 1> {
        using Type = Pack_Export::Pack_Unsigned64_1;
    };

    template <>
    struct PackIntrinsicType<Unsigned64, 2> {
        using Type = Pack_Export::Pack_Unsigned64_2;
    };

    template <>
    struct PackIntrinsicType<Unsigned64, 4> {
        using Type = Pack_Export::Pack_Unsigned64_4;
    };

    template <>
    struct PackIntrinsicType<Unsigned64, 8> {
        using Type = Pack_Export::Pack_Unsigned64_8;
    };

    template <>
    struct PackIntrinsicType<Decimal32, 1> {
        using Type = Pack_Export::Pack_Decimal32_1;
    };

    template <>
    struct PackIntrinsicType<Decimal32, 2> {
        using Type = Pack_Export::Pack_Decimal32_2;
    };

    template <>
    struct PackIntrinsicType<Decimal32, 4> {
        using Type = Pack_Export::Pack_Decimal32_4;
    };

    template <>
    struct PackIntrinsicType<Decimal32, 8> {
        using Type = Pack_Export::Pack_Decimal32_8;
    };

    template <>
    struct PackIntrinsicType<Decimal32, 16> {
        using Type = Pack_Export::Pack_Decimal32_16;
    };

    template <>
    struct PackIntrinsicType<Decimal64, 1> {
        using Type = Pack_Export::Pack_Decimal64_1;
    };

    template <>
    struct PackIntrinsicType<Decimal64, 2> {
        using Type = Pack_Export::Pack_Decimal64_2;
    };

    template <>
    struct PackIntrinsicType<Decimal64, 4> {
        using Type = Pack_Export::Pack_Decimal64_4;
    };

    template <>
    struct PackIntrinsicType<Decimal64, 8> {
        using Type = Pack_Export::Pack_Decimal64_8;
    };
} // namespace next_mode::core::types::detail
