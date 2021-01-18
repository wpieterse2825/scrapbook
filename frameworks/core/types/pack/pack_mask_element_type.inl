namespace next_mode::core::types::detail {
    template <int Width>
    struct PackMaskElementType {
        using Type = void;
    };

    template <>
    struct PackMaskElementType<1> {
        using Type = Unsigned8;
    };

    template <>
    struct PackMaskElementType<2> {
        using Type = Unsigned8;
    };

    template <>
    struct PackMaskElementType<4> {
        using Type = Unsigned8;
    };

    template <>
    struct PackMaskElementType<8> {
        using Type = Unsigned8;
    };

    template <>
    struct PackMaskElementType<16> {
        using Type = Unsigned16;
    };

    template <>
    struct PackMaskElementType<32> {
        using Type = Unsigned32;
    };

    template <>
    struct PackMaskElementType<64> {
        using Type = Unsigned64;
    };
} // namespace next_mode::core::types::detail
