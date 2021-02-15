namespace math::mapping {
    template <Decimal Type>
    inline auto Floor(Type value) -> Type {
        constexpr auto is_float       = std::is_same_v<Type, float>;
        constexpr auto is_double      = std::is_same_v<Type, double>;
        constexpr auto is_long_double = std::is_same_v<Type, long double>;
        constexpr auto is_correct     = is_float | is_double | is_long_double;

        static_assert(is_correct == true);

        if constexpr (is_float == true) {
            return ::floorf(value);
        }

        if constexpr (is_double == true) {
            return ::floor(value);
        }

        if constexpr (is_long_double == true) {
            return ::floorl(value);
        }
    }

    template <Decimal Type>
    inline auto Ceiling(Type value) -> Type {
        constexpr auto is_float       = std::is_same_v<Type, float>;
        constexpr auto is_double      = std::is_same_v<Type, double>;
        constexpr auto is_long_double = std::is_same_v<Type, long double>;
        constexpr auto is_correct     = is_float | is_double | is_long_double;

        static_assert(is_correct == true);

        if constexpr (is_float == true) {
            return ::ceilf(value);
        }

        if constexpr (is_double == true) {
            return ::ceil(value);
        }

        if constexpr (is_long_double == true) {
            return ::ceill(value);
        }
    }

    template <Decimal Type>
    inline auto Absolute(Type value) -> Type {
        constexpr auto is_float       = std::is_same_v<Type, float>;
        constexpr auto is_double      = std::is_same_v<Type, double>;
        constexpr auto is_long_double = std::is_same_v<Type, long double>;
        constexpr auto is_correct     = is_float | is_double | is_long_double;

        static_assert(is_correct == true);

        if constexpr (is_float == true) {
            return ::fabsf(value);
        }

        if constexpr (is_double == true) {
            return ::fabs(value);
        }

        if constexpr (is_long_double == true) {
            return ::fabsl(value);
        }
    }
} // namespace math::mapping
