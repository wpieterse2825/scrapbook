namespace math::trigonometry::radians {
    template <Decimal Type>
    inline auto Sine(Type radians) -> Type {
        constexpr bool is_float       = std::is_same_v<Type, float>;
        constexpr bool is_double      = std::is_same_v<Type, double>;
        constexpr bool is_long_double = std::is_same_v<Type, long double>;
        constexpr bool is_correct     = is_float | is_double | is_long_double;

        static_assert(is_correct == true);

        if constexpr (is_float == true) {
            return ::sinf(radians);
        }

        if constexpr (is_double == true) {
            return ::sin(radians);
        }

        if constexpr (is_long_double == true) {
            return ::sinl(radians);
        }
    }

    template <Decimal Type>
    inline auto Cosine(Type radians) -> Type {
        constexpr bool is_float       = std::is_same_v<Type, float>;
        constexpr bool is_double      = std::is_same_v<Type, double>;
        constexpr bool is_long_double = std::is_same_v<Type, long double>;
        constexpr bool is_correct     = is_float | is_double | is_long_double;

        static_assert(is_correct == true);

        if constexpr (is_float == true) {
            return ::cosf(radians);
        }

        if constexpr (is_double == true) {
            return ::cos(radians);
        }

        if constexpr (is_long_double == true) {
            return ::cosl(radians);
        }
    }

    template <Decimal Type>
    inline auto Tangent(Type radians) -> Type {
        constexpr bool is_float       = std::is_same_v<Type, float>;
        constexpr bool is_double      = std::is_same_v<Type, double>;
        constexpr bool is_long_double = std::is_same_v<Type, long double>;
        constexpr bool is_correct     = is_float | is_double | is_long_double;

        static_assert(is_correct == true);

        if constexpr (is_float == true) {
            return ::tanf(radians);
        }

        if constexpr (is_double == true) {
            return ::tan(radians);
        }

        if constexpr (is_long_double == true) {
            return ::tanl(radians);
        }
    }
} // namespace math::trigonometry::radians
