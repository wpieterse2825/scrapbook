namespace next_mode::core::types::detail {
    template <int Width>
    struct PackMaskIntrinsicTypeUnknown {};

    template <int Width>
    struct PackMaskIntrinsicType {
        using Type = PackMaskIntrinsicTypeUnknown<Width>;
    };

    template <>
    struct PackMaskIntrinsicType<1> {
        using Type = Pack_Export::Pack_Mask8;
    };

    template <>
    struct PackMaskIntrinsicType<2> {
        using Type = Pack_Export::Pack_Mask8;
    };

    template <>
    struct PackMaskIntrinsicType<4> {
        using Type = Pack_Export::Pack_Mask8;
    };

    template <>
    struct PackMaskIntrinsicType<8> {
        using Type = Pack_Export::Pack_Mask8;
    };

    template <>
    struct PackMaskIntrinsicType<16> {
        using Type = Pack_Export::Pack_Mask16;
    };

    template <>
    struct PackMaskIntrinsicType<32> {
        using Type = Pack_Export::Pack_Mask32;
    };

    template <>
    struct PackMaskIntrinsicType<64> {
        using Type = Pack_Export::Pack_Mask64;
    };
} // namespace next_mode::core::types::detail
