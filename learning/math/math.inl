template <Arithmetic Type>
constexpr auto Affirm(const Type& input) -> Type {
    return +input;
}

template <Arithmetic Type>
constexpr auto Negate(const Type& input) -> Type {
    return -input;
}

template <Arithmetic Type>
constexpr auto Plus(const Type& lhs, const Type& rhs) -> Type {
    return lhs + rhs;
}

template <Arithmetic Type>
constexpr auto Minus(const Type& lhs, const Type& rhs) -> Type {
    return lhs - rhs;
}

template <Arithmetic Type>
constexpr auto Multiply(const Type& lhs, const Type& rhs) -> Type {
    return lhs * rhs;
}

template <Arithmetic Type>
constexpr auto Divide(const Type& lhs, const Type& rhs) -> Type {
    return lhs / rhs;
}

template <Arithmetic Type>
constexpr auto Compare(const Type& lhs, const Type& rhs) -> Type {
    return lhs == rhs;
}

template <Arithmetic Type>
constexpr auto Equal(const Type& lhs, const Type& rhs) -> Type {
    const auto compare_result = Compare(lhs, rhs);

    return compare_result == true;
}

template <Arithmetic Type>
constexpr auto NotEqual(const Type& lhs, const Type& rhs) -> Type {
    const auto compare_result = Compare(lhs, rhs);

    return compare_result == false;
}

template <Arithmetic Type>
constexpr auto LessThan(const Type& lhs, const Type& rhs) -> Type {
    return lhs < rhs;
}

template <Arithmetic Type>
constexpr auto LessThanOrEqual(const Type& lhs, const Type& rhs) -> Type {
    return lhs <= rhs;
}

template <Arithmetic Type>
constexpr auto GreaterThan(const Type& lhs, const Type& rhs) -> Type {
    return lhs > rhs;
}

template <Arithmetic Type>
constexpr auto GreaterThanOrEqual(const Type& lhs, const Type& rhs) -> Type {
    return lhs >= rhs;
}

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
    if constexpr (std::is_same_v<Type, float> == true) {
        return ::fabsf(value);
    }

    if constexpr (std::is_same_v<Type, double> == true) {
        return ::fabs(value);
    }

    if constexpr (std::is_same_v<Type, long double> == true) {
        return ::fabsl(value);
    }
}

template <Decimal Type>
inline auto SquareRoot(Type value) -> Type {
    constexpr auto is_float       = std::is_same_v<Type, float>;
    constexpr auto is_double      = std::is_same_v<Type, double>;
    constexpr auto is_long_double = std::is_same_v<Type, long double>;
    constexpr auto is_correct     = is_float | is_double | is_long_double;

    static_assert(is_correct == true);

    if constexpr (is_float == true) {
        return ::sqrtf(value);
    }

    if constexpr (is_double == true) {
        return ::sqrt(value);
    }

    if constexpr (is_long_double == true) {
        return ::sqrtl(value);
    }
}

template <Decimal Type>
inline auto InverseSquareRoot(Type value) -> Type {
    constexpr auto one_positive = MathConstants<Type>::OnePositive;

    const auto square_root = SquareRoot(value);

    return one_positive / square_root;
}

template <Decimal Type>
inline auto DegreesToRadians(Type degrees) -> Type {
    constexpr auto pi                       = MathConstants<Type>::PiPositive;
    constexpr auto degrees_two_quarters     = MathConstants<Type>::DegreesTwoQuartersPositive;
    constexpr auto degrees_to_radians_scale = pi / degrees_two_quarters;

    return degrees * degrees_to_radians_scale;
}

template <Decimal Type>
inline auto RadiansToDegrees(Type radians) -> Type {
    constexpr auto degrees_two_quarters     = MathConstants<Type>::DegreesTwoQuartersPositive;
    constexpr auto pi                       = MathConstants<Type>::PiPositive;
    constexpr auto radians_to_degrees_scale = degrees_two_quarters / pi;

    return radians * radians_to_degrees_scale;
}

template <Decimal Type>
inline auto SineRadians(Type radians) -> Type {
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
inline auto CosineRadians(Type radians) -> Type {
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
inline auto TangentRadians(Type radians) -> Type {
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

template <Decimal Type>
inline auto SineDegrees(Type degrees) -> Type {
    const auto degrees_to_radians = DegreesToRadians(degrees);

    auto result = SineRadians(degrees_to_radians);

    return RadiansToDegrees(result);
}

template <Decimal Type>
inline auto CosineDegrees(Type degrees) -> Type {
    const auto degrees_to_radians = DegreesToRadians(degrees);

    auto result = CosineRadians(degrees_to_radians);

    return RadiansToDegrees(result);
}

template <Decimal Type>
inline auto TangentDegrees(Type degrees) -> Type {
    const auto degrees_to_radians = DegreesToRadians(degrees);

    auto result = TangentRadians(degrees_to_radians);

    return RadiansToDegrees(result);
}
