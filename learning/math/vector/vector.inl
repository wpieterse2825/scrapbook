constexpr auto VectorXComponent = size_t {0};
constexpr auto VectorYComponent = size_t {1};
constexpr auto VectorZComponent = size_t {2};
constexpr auto VectorWComponent = size_t {3};

template <typename Type, size_t Dimensions>
inline auto GetDimensions(const Vector<Type, Dimensions>&) -> size_t;

template <typename Type, size_t Dimensions>
inline auto Read(const Vector<Type, Dimensions>& input, const size_t index) -> Type;

template <typename Type, size_t Dimensions>
inline auto Write(Vector<Type, Dimensions>& input, const size_t index, const Type& value) -> void;

template <typename Type, size_t Dimensions>
inline auto VectorFromBroadcast(const Type& input_value) -> Vector<Type, Dimensions>;

template <typename Type, size_t Dimensions>
inline auto VectorFromZero() -> Vector<Type, Dimensions>;

template <typename Type, size_t Dimensions>
inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool;

template <typename Type, size_t Dimensions>
inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool;

template <typename Type, size_t Dimensions>
inline auto Equal(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool;

template <typename Type, size_t Dimensions>
inline auto NotEqual(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool;

template <typename Type, size_t Dimensions>
inline auto Equal(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool;

template <typename Type, size_t Dimensions>
inline auto NotEqual(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool;

template <typename Type, size_t Dimensions>
inline auto Negate(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions>;

template <typename Type, size_t Dimensions>
inline auto Plus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions>;

template <typename Type, size_t Dimensions>
inline auto Minus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions>;

template <typename Type, size_t Dimensions>
inline auto Multiply(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions>;

template <typename Type, size_t Dimensions>
inline auto Divide(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions>;

template <typename Type, size_t Dimensions>
inline auto Divide(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions>;

template <typename Type, size_t Dimensions>
inline auto Truncate(const Vector<Type, Dimensions>& input, const Type& output_length) -> Vector<Type, Dimensions>;

template <typename Type, size_t Dimensions>
inline auto Normalize(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions>;

template <typename Type, size_t Dimensions>
inline auto DotProduct(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Type;

template <typename Type>
inline auto CrossProduct(const Vector<Type, 3>& lhs, const Vector<Type, 3>& rhs) -> Vector<Type, 3>;

template <typename Type, size_t Dimensions>
inline auto Length(const Vector<Type, Dimensions>& input) -> Type;

template <typename Type, size_t Dimensions>
inline auto Clamp(const Vector<Type, Dimensions>& input, const Type& minimum, const Type& maximum) -> Vector<Type, Dimensions>;

template <typename Type, size_t Dimensions>
inline auto Snap(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions>;

template <typename Type, size_t Dimensions>
inline auto Print(const Vector<Type, Dimensions>& input) -> void;

template <typename Type, size_t Dimensions>
inline auto operator==(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool;

template <typename Type, size_t Dimensions>
inline auto operator!=(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool;

template <typename Type, size_t Dimensions>
inline auto operator-(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions>;

template <typename Type, size_t Dimensions>
inline auto operator+(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions>;

template <typename Type, size_t Dimensions>
inline auto operator-(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions>;

template <typename Type, size_t Dimensions>
inline auto operator*(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions>;

template <typename Type, size_t Dimensions>
inline auto operator*(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Type;

template <typename Type, size_t Dimensions>
inline auto operator/(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions>;

template <typename Type, size_t Dimensions>
inline auto operator/(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions>;

namespace detail::vector::general {
    template <typename Type, size_t Dimensions>
    inline auto VectorFromBroadcast(const Type& input_value) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool;

    template <typename Type, size_t Dimensions>
    inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool;

    template <typename Type, size_t Dimensions>
    inline auto Negate(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Plus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Minus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Multiply(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Divide(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Divide(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Truncate(const Vector<Type, Dimensions>& input, const Type& output_length) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto DotProduct(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Type;

    template <typename Type>
    inline auto CrossProduct(const Vector<Type, 3>& lhs, const Vector<Type, 3>& rhs) -> Vector<Type, 3>;

    template <typename Type, size_t Dimensions>
    inline auto Length(const Vector<Type, Dimensions>& input) -> Type;

    template <typename Type, size_t Dimensions>
    inline auto Clamp(const Vector<Type, Dimensions>& input, const Type& minimum, const Type& maximum) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Snap(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions>;
} // namespace detail::vector::general

namespace detail::vector::sse_1 {
    template <typename Type, size_t Dimensions>
    inline auto VectorFromBroadcast(const Type& input_value) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool;

    template <typename Type, size_t Dimensions>
    inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool;

    template <typename Type, size_t Dimensions>
    inline auto Negate(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Plus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Minus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Multiply(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Divide(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Divide(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Truncate(const Vector<Type, Dimensions>& input, const Type& output_length) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto DotProduct(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Type;

    template <typename Type>
    inline auto CrossProduct(const Vector<Type, 3>& lhs, const Vector<Type, 3>& rhs) -> Vector<Type, 3>;

    template <typename Type, size_t Dimensions>
    inline auto Length(const Vector<Type, Dimensions>& input) -> Type;

    template <typename Type, size_t Dimensions>
    inline auto Clamp(const Vector<Type, Dimensions>& input, const Type& minimum, const Type& maximum) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Snap(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions>;
} // namespace detail::vector::sse_1

namespace detail::vector::sse_2 {
    template <typename Type, size_t Dimensions>
    inline auto VectorFromBroadcast(const Type& input_value) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool;

    template <typename Type, size_t Dimensions>
    inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool;

    template <typename Type, size_t Dimensions>
    inline auto Negate(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Plus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Minus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Multiply(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Divide(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Divide(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Truncate(const Vector<Type, Dimensions>& input, const Type& output_length) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto DotProduct(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Type;

    template <typename Type>
    inline auto CrossProduct(const Vector<Type, 3>& lhs, const Vector<Type, 3>& rhs) -> Vector<Type, 3>;

    template <typename Type, size_t Dimensions>
    inline auto Length(const Vector<Type, Dimensions>& input) -> Type;

    template <typename Type, size_t Dimensions>
    inline auto Clamp(const Vector<Type, Dimensions>& input, const Type& minimum, const Type& maximum) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Snap(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions>;
} // namespace detail::vector::sse_2

namespace detail::vector::avx_1 {
    template <typename Type, size_t Dimensions>
    inline auto VectorFromBroadcast(const Type& input_value) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool;

    template <typename Type, size_t Dimensions>
    inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool;

    template <typename Type, size_t Dimensions>
    inline auto Negate(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Plus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Minus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Multiply(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Divide(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Divide(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Truncate(const Vector<Type, Dimensions>& input, const Type& output_length) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto DotProduct(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Type;

    template <typename Type>
    inline auto CrossProduct(const Vector<Type, 3>& lhs, const Vector<Type, 3>& rhs) -> Vector<Type, 3>;

    template <typename Type, size_t Dimensions>
    inline auto Length(const Vector<Type, Dimensions>& input) -> Type;

    template <typename Type, size_t Dimensions>
    inline auto Clamp(const Vector<Type, Dimensions>& input, const Type& minimum, const Type& maximum) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto Snap(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions>;
} // namespace detail::vector::avx_1

template <typename Type, size_t Dimensions>
inline auto GetDimensions(const Vector<Type, Dimensions>&) -> size_t {
    return Dimensions;
}

template <typename Type, size_t Dimensions>
inline auto Read(const Vector<Type, Dimensions>& input, const size_t index) -> Type {
    assert(index < Dimensions);

    return input.elements[index];
}

template <typename Type, size_t Dimensions>
inline auto Write(Vector<Type, Dimensions>& input, const size_t index, const Type& value) -> void {
    assert(index < Dimensions);

    input.elements[index] = value;
}

template <typename Type, size_t Dimensions>
inline auto VectorFromBroadcast(const Type& input_value) -> Vector<Type, Dimensions> {
    constexpr auto simd_enabled       = MathSIMDEnabled;
    constexpr auto simd_enabled_avx_1 = MathSIMDEnableAVX1;
    constexpr auto simd_enabled_sse_2 = MathSIMDEnableSSE2;
    constexpr auto simd_enabled_sse_1 = MathSIMDEnableSSE1;
    constexpr auto simd_use_avx_1     = simd_enabled == true && simd_enabled_avx_1 == true;
    constexpr auto simd_use_sse_2     = simd_enabled == true && simd_enabled_sse_2 == true;
    constexpr auto simd_use_sse_1     = simd_enabled == true && simd_enabled_sse_1 == true;

    if constexpr (simd_use_avx_1 == true) {
        return detail::vector::avx_1::VectorFromBroadcast<Type, Dimensions>(input_value);
    }

    if constexpr (simd_use_sse_2 == true) {
        return detail::vector::sse_2::VectorFromBroadcast<Type, Dimensions>(input_value);
    }

    if constexpr (simd_use_sse_1 == true) {
        return detail::vector::sse_1::VectorFromBroadcast<Type, Dimensions>(input_value);
    }

    return detail::vector::general::VectorFromBroadcast<Type, Dimensions>(input_value);
}

template <typename Type, size_t Dimensions>
inline auto VectorFromZero() -> Vector<Type, Dimensions> {
    constexpr auto zero = MathConstants<Type>::Zero;

    // TODO(wpieterse): Maybe this should just return the stacked vector value. Investigate if that will be a problem.
    return VectorFromBroadcast<Type, Dimensions>(zero);
}

template <typename Type, size_t Dimensions>
inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool {
    constexpr auto simd_enabled       = MathSIMDEnabled;
    constexpr auto simd_enabled_avx_1 = MathSIMDEnableAVX1;
    constexpr auto simd_enabled_sse_2 = MathSIMDEnableSSE2;
    constexpr auto simd_enabled_sse_1 = MathSIMDEnableSSE1;
    constexpr auto simd_use_avx_1     = simd_enabled == true && simd_enabled_avx_1 == true;
    constexpr auto simd_use_sse_2     = simd_enabled == true && simd_enabled_sse_2 == true;
    constexpr auto simd_use_sse_1     = simd_enabled == true && simd_enabled_sse_1 == true;

    if constexpr (simd_use_avx_1 == true) {
        return detail::vector::avx_1::Compare(lhs, rhs, epsilon);
    }

    if constexpr (simd_use_sse_2 == true) {
        return detail::vector::sse_2::Compare(lhs, rhs, epsilon);
    }

    if constexpr (simd_use_sse_1 == true) {
        return detail::vector::sse_1::Compare(lhs, rhs, epsilon);
    }

    return detail::vector::general::Compare(lhs, rhs, epsilon);
}

template <typename Type, size_t Dimensions>
inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
    constexpr auto simd_enabled       = MathSIMDEnabled;
    constexpr auto simd_enabled_avx_1 = MathSIMDEnableAVX1;
    constexpr auto simd_enabled_sse_2 = MathSIMDEnableSSE2;
    constexpr auto simd_enabled_sse_1 = MathSIMDEnableSSE1;
    constexpr auto simd_use_avx_1     = simd_enabled == true && simd_enabled_avx_1 == true;
    constexpr auto simd_use_sse_2     = simd_enabled == true && simd_enabled_sse_2 == true;
    constexpr auto simd_use_sse_1     = simd_enabled == true && simd_enabled_sse_1 == true;

    if constexpr (simd_use_avx_1 == true) {
        return detail::vector::avx_1::Compare(lhs, rhs);
    }

    if constexpr (simd_use_sse_2 == true) {
        return detail::vector::sse_2::Compare(lhs, rhs);
    }

    if constexpr (simd_use_sse_1 == true) {
        return detail::vector::sse_1::Compare(lhs, rhs);
    }

    return detail::vector::general::Compare(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto Equal(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool {
    const auto compare_result = Compare(lhs, rhs, epsilon);

    return compare_result == true;
}

template <typename Type, size_t Dimensions>
inline auto NotEqual(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool {
    const auto compare_result = Compare(lhs, rhs, epsilon);

    return compare_result == false;
}

template <typename Type, size_t Dimensions>
inline auto Equal(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
    const auto compare_result = Compare(lhs, rhs);

    return compare_result == true;
}

template <typename Type, size_t Dimensions>
inline auto NotEqual(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
    const auto compare_result = Compare(lhs, rhs);

    return compare_result == false;
}

template <typename Type, size_t Dimensions>
inline auto Negate(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
    constexpr auto simd_enabled       = MathSIMDEnabled;
    constexpr auto simd_enabled_avx_1 = MathSIMDEnableAVX1;
    constexpr auto simd_enabled_sse_2 = MathSIMDEnableSSE2;
    constexpr auto simd_enabled_sse_1 = MathSIMDEnableSSE1;
    constexpr auto simd_use_avx_1     = simd_enabled == true && simd_enabled_avx_1 == true;
    constexpr auto simd_use_sse_2     = simd_enabled == true && simd_enabled_sse_2 == true;
    constexpr auto simd_use_sse_1     = simd_enabled == true && simd_enabled_sse_1 == true;

    if constexpr (simd_use_avx_1 == true) {
        return detail::vector::avx_1::Negate(input);
    }

    if constexpr (simd_use_sse_2 == true) {
        return detail::vector::sse_2::Negate(input);
    }

    if constexpr (simd_use_sse_1 == true) {
        return detail::vector::sse_1::Negate(input);
    }

    return detail::vector::general::Negate(input);
}

template <typename Type, size_t Dimensions>
inline auto Plus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
    constexpr auto simd_enabled       = MathSIMDEnabled;
    constexpr auto simd_enabled_avx_1 = MathSIMDEnableAVX1;
    constexpr auto simd_enabled_sse_2 = MathSIMDEnableSSE2;
    constexpr auto simd_enabled_sse_1 = MathSIMDEnableSSE1;
    constexpr auto simd_use_avx_1     = simd_enabled == true && simd_enabled_avx_1 == true;
    constexpr auto simd_use_sse_2     = simd_enabled == true && simd_enabled_sse_2 == true;
    constexpr auto simd_use_sse_1     = simd_enabled == true && simd_enabled_sse_1 == true;

    if constexpr (simd_use_avx_1 == true) {
        return detail::vector::avx_1::Plus(lhs, rhs);
    }

    if constexpr (simd_use_sse_2 == true) {
        return detail::vector::sse_2::Plus(lhs, rhs);
    }

    if constexpr (simd_use_sse_1 == true) {
        return detail::vector::sse_1::Plus(lhs, rhs);
    }

    return detail::vector::general::Plus(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto Minus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
    constexpr auto simd_enabled       = MathSIMDEnabled;
    constexpr auto simd_enabled_avx_1 = MathSIMDEnableAVX1;
    constexpr auto simd_enabled_sse_2 = MathSIMDEnableSSE2;
    constexpr auto simd_enabled_sse_1 = MathSIMDEnableSSE1;
    constexpr auto simd_use_avx_1     = simd_enabled == true && simd_enabled_avx_1 == true;
    constexpr auto simd_use_sse_2     = simd_enabled == true && simd_enabled_sse_2 == true;
    constexpr auto simd_use_sse_1     = simd_enabled == true && simd_enabled_sse_1 == true;

    if constexpr (simd_use_avx_1 == true) {
        return detail::vector::avx_1::Minus(lhs, rhs);
    }

    if constexpr (simd_use_sse_2 == true) {
        return detail::vector::sse_2::Minus(lhs, rhs);
    }

    if constexpr (simd_use_sse_1 == true) {
        return detail::vector::sse_1::Minus(lhs, rhs);
    }

    return detail::vector::general::Minus(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto Multiply(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
    constexpr auto simd_enabled       = MathSIMDEnabled;
    constexpr auto simd_enabled_avx_1 = MathSIMDEnableAVX1;
    constexpr auto simd_enabled_sse_2 = MathSIMDEnableSSE2;
    constexpr auto simd_enabled_sse_1 = MathSIMDEnableSSE1;
    constexpr auto simd_use_avx_1     = simd_enabled == true && simd_enabled_avx_1 == true;
    constexpr auto simd_use_sse_2     = simd_enabled == true && simd_enabled_sse_2 == true;
    constexpr auto simd_use_sse_1     = simd_enabled == true && simd_enabled_sse_1 == true;

    if constexpr (simd_use_avx_1 == true) {
        return detail::vector::avx_1::Multiply(lhs, rhs);
    }

    if constexpr (simd_use_sse_2 == true) {
        return detail::vector::sse_2::Multiply(lhs, rhs);
    }

    if constexpr (simd_use_sse_1 == true) {
        return detail::vector::sse_1::Multiply(lhs, rhs);
    }

    return detail::vector::general::Multiply(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto Divide(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
    constexpr auto simd_enabled       = MathSIMDEnabled;
    constexpr auto simd_enabled_avx_1 = MathSIMDEnableAVX1;
    constexpr auto simd_enabled_sse_2 = MathSIMDEnableSSE2;
    constexpr auto simd_enabled_sse_1 = MathSIMDEnableSSE1;
    constexpr auto simd_use_avx_1     = simd_enabled == true && simd_enabled_avx_1 == true;
    constexpr auto simd_use_sse_2     = simd_enabled == true && simd_enabled_sse_2 == true;
    constexpr auto simd_use_sse_1     = simd_enabled == true && simd_enabled_sse_1 == true;

    if constexpr (simd_use_avx_1 == true) {
        return detail::vector::avx_1::Divide(lhs, rhs);
    }

    if constexpr (simd_use_sse_2 == true) {
        return detail::vector::sse_2::Divide(lhs, rhs);
    }

    if constexpr (simd_use_sse_1 == true) {
        return detail::vector::sse_1::Divide(lhs, rhs);
    }

    return detail::vector::general::Divide(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto Divide(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
    constexpr auto simd_enabled       = MathSIMDEnabled;
    constexpr auto simd_enabled_avx_1 = MathSIMDEnableAVX1;
    constexpr auto simd_enabled_sse_2 = MathSIMDEnableSSE2;
    constexpr auto simd_enabled_sse_1 = MathSIMDEnableSSE1;
    constexpr auto simd_use_avx_1     = simd_enabled == true && simd_enabled_avx_1 == true;
    constexpr auto simd_use_sse_2     = simd_enabled == true && simd_enabled_sse_2 == true;
    constexpr auto simd_use_sse_1     = simd_enabled == true && simd_enabled_sse_1 == true;

    if constexpr (simd_use_avx_1 == true) {
        return detail::vector::avx_1::Divide(lhs, rhs);
    }

    if constexpr (simd_use_sse_2 == true) {
        return detail::vector::sse_2::Divide(lhs, rhs);
    }

    if constexpr (simd_use_sse_1 == true) {
        return detail::vector::sse_1::Divide(lhs, rhs);
    }

    return detail::vector::general::Divide(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto Truncate(const Vector<Type, Dimensions>& input, const Type& output_length) -> Vector<Type, Dimensions> {
    constexpr auto simd_enabled       = MathSIMDEnabled;
    constexpr auto simd_enabled_avx_1 = MathSIMDEnableAVX1;
    constexpr auto simd_enabled_sse_2 = MathSIMDEnableSSE2;
    constexpr auto simd_enabled_sse_1 = MathSIMDEnableSSE1;
    constexpr auto simd_use_avx_1     = simd_enabled == true && simd_enabled_avx_1 == true;
    constexpr auto simd_use_sse_2     = simd_enabled == true && simd_enabled_sse_2 == true;
    constexpr auto simd_use_sse_1     = simd_enabled == true && simd_enabled_sse_1 == true;

    if constexpr (simd_use_avx_1 == true) {
        return detail::vector::avx_1::Truncate(input, output_length);
    }

    if constexpr (simd_use_sse_2 == true) {
        return detail::vector::sse_2::Truncate(input, output_length);
    }

    if constexpr (simd_use_sse_1 == true) {
        return detail::vector::sse_1::Truncate(input, output_length);
    }

    return detail::vector::general::Truncate(input, output_length);
}

template <typename Type, size_t Dimensions>
inline auto Normalize(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
    constexpr auto one_positive = MathConstants<Type>::OnePositive;

    return Truncate(input, one_positive);
}

template <typename Type, size_t Dimensions>
inline auto DotProduct(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Type {
    constexpr auto simd_enabled       = MathSIMDEnabled;
    constexpr auto simd_enabled_avx_1 = MathSIMDEnableAVX1;
    constexpr auto simd_enabled_sse_2 = MathSIMDEnableSSE2;
    constexpr auto simd_enabled_sse_1 = MathSIMDEnableSSE1;
    constexpr auto simd_use_avx_1     = simd_enabled == true && simd_enabled_avx_1 == true;
    constexpr auto simd_use_sse_2     = simd_enabled == true && simd_enabled_sse_2 == true;
    constexpr auto simd_use_sse_1     = simd_enabled == true && simd_enabled_sse_1 == true;

    if constexpr (simd_use_avx_1 == true) {
        return detail::vector::avx_1::DotProduct(lhs, rhs);
    }

    if constexpr (simd_use_sse_2 == true) {
        return detail::vector::sse_2::DotProduct(lhs, rhs);
    }

    if constexpr (simd_use_sse_1 == true) {
        return detail::vector::sse_1::DotProduct(lhs, rhs);
    }

    return detail::vector::general::DotProduct(lhs, rhs);
}

template <typename Type>
inline auto CrossProduct(const Vector<Type, 3>& lhs, const Vector<Type, 3>& rhs) -> Vector<Type, 3> {
    constexpr auto simd_enabled       = MathSIMDEnabled;
    constexpr auto simd_enabled_avx_1 = MathSIMDEnableAVX1;
    constexpr auto simd_enabled_sse_2 = MathSIMDEnableSSE2;
    constexpr auto simd_enabled_sse_1 = MathSIMDEnableSSE1;
    constexpr auto simd_use_avx_1     = simd_enabled == true && simd_enabled_avx_1 == true;
    constexpr auto simd_use_sse_2     = simd_enabled == true && simd_enabled_sse_2 == true;
    constexpr auto simd_use_sse_1     = simd_enabled == true && simd_enabled_sse_1 == true;

    if constexpr (simd_use_avx_1 == true) {
        return detail::vector::avx_1::CrossProduct(lhs, rhs);
    }

    if constexpr (simd_use_sse_2 == true) {
        return detail::vector::sse_2::CrossProduct(lhs, rhs);
    }

    if constexpr (simd_use_sse_1 == true) {
        return detail::vector::sse_1::CrossProduct(lhs, rhs);
    }

    return detail::vector::general::CrossProduct(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto Length(const Vector<Type, Dimensions>& input) -> Type {
    constexpr auto simd_enabled       = MathSIMDEnabled;
    constexpr auto simd_enabled_avx_1 = MathSIMDEnableAVX1;
    constexpr auto simd_enabled_sse_2 = MathSIMDEnableSSE2;
    constexpr auto simd_enabled_sse_1 = MathSIMDEnableSSE1;
    constexpr auto simd_use_avx_1     = simd_enabled == true && simd_enabled_avx_1 == true;
    constexpr auto simd_use_sse_2     = simd_enabled == true && simd_enabled_sse_2 == true;
    constexpr auto simd_use_sse_1     = simd_enabled == true && simd_enabled_sse_1 == true;

    if constexpr (simd_use_avx_1 == true) {
        return detail::vector::avx_1::Length(input);
    }

    if constexpr (simd_use_sse_2 == true) {
        return detail::vector::sse_2::Length(input);
    }

    if constexpr (simd_use_sse_1 == true) {
        return detail::vector::sse_1::Length(input);
    }

    return detail::vector::general::Length(input);
}

template <typename Type, size_t Dimensions>
inline auto Clamp(const Vector<Type, Dimensions>& input, const Type& minimum, const Type& maximum) -> Vector<Type, Dimensions> {
    constexpr auto simd_enabled       = MathSIMDEnabled;
    constexpr auto simd_enabled_avx_1 = MathSIMDEnableAVX1;
    constexpr auto simd_enabled_sse_2 = MathSIMDEnableSSE2;
    constexpr auto simd_enabled_sse_1 = MathSIMDEnableSSE1;
    constexpr auto simd_use_avx_1     = simd_enabled == true && simd_enabled_avx_1 == true;
    constexpr auto simd_use_sse_2     = simd_enabled == true && simd_enabled_sse_2 == true;
    constexpr auto simd_use_sse_1     = simd_enabled == true && simd_enabled_sse_1 == true;

    if constexpr (simd_use_avx_1 == true) {
        return detail::vector::avx_1::Clamp(input, minimum, maximum);
    }

    if constexpr (simd_use_sse_2 == true) {
        return detail::vector::sse_2::Clamp(input, minimum, maximum);
    }

    if constexpr (simd_use_sse_1 == true) {
        return detail::vector::sse_1::Clamp(input, minimum, maximum);
    }

    return detail::vector::general::Clamp(input, minimum, maximum);
}

template <typename Type, size_t Dimensions>
inline auto Snap(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
    constexpr auto simd_enabled       = MathSIMDEnabled;
    constexpr auto simd_enabled_avx_1 = MathSIMDEnableAVX1;
    constexpr auto simd_enabled_sse_2 = MathSIMDEnableSSE2;
    constexpr auto simd_enabled_sse_1 = MathSIMDEnableSSE1;
    constexpr auto simd_use_avx_1     = simd_enabled == true && simd_enabled_avx_1 == true;
    constexpr auto simd_use_sse_2     = simd_enabled == true && simd_enabled_sse_2 == true;
    constexpr auto simd_use_sse_1     = simd_enabled == true && simd_enabled_sse_1 == true;

    if constexpr (simd_use_avx_1 == true) {
        return detail::vector::avx_1::Snap(input);
    }

    if constexpr (simd_use_sse_2 == true) {
        return detail::vector::sse_2::Snap(input);
    }

    if constexpr (simd_use_sse_1 == true) {
        return detail::vector::sse_1::Snap(input);
    }

    return detail::vector::general::Snap(input);
}

template <typename Type, size_t Dimensions>
inline auto Print(const Vector<Type, Dimensions>& input) -> void {
    constexpr auto elements_minus_one = Dimensions - 1;

    std::cout << "[ ";

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto can_print_comma = LessThan(index, elements_minus_one);
        const auto output_value    = Read(input, index);

        std::cout << output_value;

        if (can_print_comma == true) {
            std::cout << ", ";
        }
    }

    std::cout << " ]";
    std::cout << std::endl;
}

template <typename Type, size_t Dimensions>
inline auto operator==(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
    return Equal(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator!=(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
    return NotEqual(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator-(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
    return Negate(input);
}

template <typename Type, size_t Dimensions>
inline auto operator+(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
    return Plus(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator-(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
    return Minus(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator*(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
    return Multiply(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator*(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Type {
    return DotProduct(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator/(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
    return Divide(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator/(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
    return Divide(lhs, rhs);
}

namespace detail::vector::internal {
    template <typename Type, size_t Dimensions>
    inline auto VectorFromBroadcastTrailer(const Type& input_value, const size_t& offset, Vector<Type, Dimensions>& output) -> void;

    template <typename Type, size_t Dimensions>
    inline auto
    CompareTrailer(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon, const size_t& offset)
      -> bool;

    template <typename Type, size_t Dimensions>
    inline auto CompareTrailer(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const size_t& offset) -> bool;

    template <typename Type, size_t Dimensions>
    inline auto NegateTrailer(const Vector<Type, Dimensions>& input, const size_t& offset, Vector<Type, Dimensions>& output) -> void;

    template <typename Type, size_t Dimensions>
    inline auto PlusTrailer(const Vector<Type, Dimensions>& lhs,
                            const Vector<Type, Dimensions>& rhs,
                            const size_t&                   offset,
                            Vector<Type, Dimensions>&       output) -> void;

    template <typename Type, size_t Dimensions>
    inline auto MinusTrailer(const Vector<Type, Dimensions>& lhs,
                             const Vector<Type, Dimensions>& rhs,
                             const size_t&                   offset,
                             Vector<Type, Dimensions>&       output) -> void;

    template <typename Type, size_t Dimensions>
    inline auto
    MultiplyTrailer(const Vector<Type, Dimensions>& lhs, const Type& rhs, const size_t& offset, Vector<Type, Dimensions>& output) -> void;

    template <typename Type, size_t Dimensions>
    inline auto DivideTrailer(const Vector<Type, Dimensions>& lhs, const Type& rhs, const size_t& offset, Vector<Type, Dimensions>& output)
      -> void;

    template <typename Type, size_t Dimensions>
    inline auto DivideTrailer(const Vector<Type, Dimensions>& lhs,
                              const Vector<Type, Dimensions>& rhs,
                              const size_t&                   offfset,
                              Vector<Type, Dimensions>&       output) -> void;

    template <typename Type, size_t Dimensions>
    inline auto TruncateTrailer(const Vector<Type, Dimensions>& input, const Type& output_length) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto DotProductTrailer(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Type;

    template <typename Type>
    inline auto CrossProductTrailer(const Vector<Type, 3>& lhs, const Vector<Type, 3>& rhs) -> Vector<Type, 3>;

    template <typename Type, size_t Dimensions>
    inline auto LengthTrailer(const Vector<Type, Dimensions>& input) -> Type;

    template <typename Type, size_t Dimensions>
    inline auto ClampTrailer(const Vector<Type, Dimensions>& input, const Type& minimum, const Type& maximum) -> Vector<Type, Dimensions>;

    template <typename Type, size_t Dimensions>
    inline auto SnapTrailer(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions>;
} // namespace detail::vector::internal

namespace detail::vector::general {
    template <typename Type, size_t Dimensions>
    inline auto VectorFromBroadcast(const Type& input_value) -> Vector<Type, Dimensions> {
        auto output = Vector<Type, Dimensions> {};

        internal::VectorFromBroadcastTrailer(input_value, size_t {0}, output);

        return output;
    }

    template <typename Type, size_t Dimensions>
    inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool {
        return internal::CompareTrailer(lhs, rhs, epsilon, size_t {0});
    }

    template <typename Type, size_t Dimensions>
    inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
        return internal::CompareTrailer(lhs, rhs, size_t {0});
    }

    template <typename Type, size_t Dimensions>
    inline auto Negate(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
        auto output = VectorFromZero<Type, Dimensions>();

        internal::NegateTrailer(input, 0, output);

        return output;
    }

    template <typename Type, size_t Dimensions>
    inline auto Plus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
        auto output = VectorFromZero<Type, Dimensions>();

        internal::PlusTrailer(lhs, rhs, 0, output);

        return output;
    }

    template <typename Type, size_t Dimensions>
    inline auto Minus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
        auto output = VectorFromZero<Type, Dimensions>();

        internal::MinusTrailer(lhs, rhs, 0, output);

        return output;
    }

    template <typename Type, size_t Dimensions>
    inline auto Multiply(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
        auto output = VectorFromZero<Type, Dimensions>();

        internal::MultiplyTrailer(lhs, rhs, 0, output);

        return output;
    }

    template <typename Type, size_t Dimensions>
    inline auto Divide(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
        auto output = VectorFromZero<Type, Dimensions>();

        internal::DivideTrailer(lhs, rhs, 0, output);

        return output;
    }

    template <typename Type, size_t Dimensions>
    inline auto Divide(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
        auto output = VectorFromZero<Type, Dimensions>();

        internal::DivideTrailer(lhs, rhs, 0, output);

        return output;
    }

    template <typename Type, size_t Dimensions>
    inline auto Truncate(const Vector<Type, Dimensions>& input, const Type& output_length) -> Vector<Type, Dimensions> {
        return internal::TruncateTrailer(input, output_length);
    }

    template <typename Type, size_t Dimensions>
    inline auto DotProduct(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Type {
        return internal::DotProductTrailer(lhs, rhs);
    }

    template <typename Type>
    inline auto CrossProduct(const Vector<Type, 3>& lhs, const Vector<Type, 3>& rhs) -> Vector<Type, 3> {
        return internal::CrossProductTrailer(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Length(const Vector<Type, Dimensions>& input) -> Type {
        return internal::LengthTrailer(input);
    }

    template <typename Type, size_t Dimensions>
    inline auto Clamp(const Vector<Type, Dimensions>& input, const Type& minimum, const Type& maximum) -> Vector<Type, Dimensions> {
        return internal::ClampTrailer(input, minimum, maximum);
    }

    template <typename Type, size_t Dimensions>
    inline auto Snap(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
        return internal::SnapTrailer(input);
    }
} // namespace detail::vector::general

namespace detail::vector::sse_1 {
    template <typename Type, size_t Dimensions>
    inline auto VectorFromBroadcast(const Type& input_value) -> Vector<Type, Dimensions> {
        constexpr auto is_single         = IsSinglePrecision<Type>();
        constexpr auto block_size_single = MathSIMDBlockSizeSingleSSE1;
        constexpr auto is_block_single   = GreaterThanOrEqual(Dimensions, block_size_single);
        constexpr auto process_single    = is_single == true && is_block_single == true;

        if constexpr (process_single == true) {
            constexpr auto simd_blocks   = Dimensions / block_size_single;
            constexpr auto trailer_start = (simd_blocks * block_size_single) - 1;

            auto output        = Vector<Type, Dimensions> {};
            auto output_buffer = &output.elements[0];

            const auto broadcast = _mm_set1_ps(input_value);

            for (auto index = size_t {0}; index < simd_blocks; index++) {
                _mm_storeu_ps(output_buffer, broadcast);

                output_buffer += block_size_single;
            }

            internal::VectorFromBroadcastTrailer(input_value, trailer_start, output);

            return output;
        }

        return general::VectorFromBroadcast<Type, Dimensions>(input_value);
    }

    template <typename Type, size_t Dimensions>
    inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool {
        constexpr auto is_single         = IsSinglePrecision<Type>();
        constexpr auto block_size_single = MathSIMDBlockSizeSingleSSE1;
        constexpr auto is_block_single   = GreaterThanOrEqual(Dimensions, block_size_single);
        constexpr auto process_single    = is_single == true && is_block_single == true;

        if constexpr (process_single == true) {
            constexpr auto simd_blocks   = Dimensions / block_size_single;
            constexpr auto trailer_start = (simd_blocks * block_size_single) - 1;

            auto lhs_buffer = &lhs.elements[0];
            auto rhs_buffer = &rhs.elements[0];

            const auto epsilon_simd = _mm_set1_ps(epsilon);
            const auto sign_simd    = _mm_set1_ps(-0.0f);

            for (auto index = size_t {0}; index < simd_blocks; index++) {
                const auto lhs_value           = _mm_loadu_ps(lhs_buffer);
                const auto rhs_value           = _mm_loadu_ps(rhs_buffer);
                const auto difference          = _mm_sub_ps(lhs_value, rhs_value);
                const auto absolute_difference = _mm_and_ps(sign_simd, difference);
                const auto over_epsilon        = _mm_cmpgt_ps(absolute_difference, epsilon_simd);
                const auto over_epsilon_mask   = _mm_movemask_ps(over_epsilon);

                if (over_epsilon_mask != 0) {
                    return false;
                }

                lhs_buffer += block_size_single;
                rhs_buffer += block_size_single;
            }

            return internal::CompareTrailer(lhs, rhs, epsilon, trailer_start);
        }

        return general::Compare(lhs, rhs, epsilon);
    }

    template <typename Type, size_t Dimensions>
    inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
        constexpr auto is_single         = IsSinglePrecision<Type>();
        constexpr auto block_size_single = MathSIMDBlockSizeSingleSSE1;
        constexpr auto is_block_single   = GreaterThanOrEqual(Dimensions, block_size_single);
        constexpr auto process_single    = is_single == true && is_block_single == true;

        if constexpr (process_single == true) {
            constexpr auto simd_blocks   = Dimensions / block_size_single;
            constexpr auto trailer_start = (simd_blocks * block_size_single) - 1;

            auto lhs_buffer = &lhs.elements[0];
            auto rhs_buffer = &rhs.elements[0];

            for (auto index = size_t {0}; index < simd_blocks; index++) {
                const auto lhs_value     = _mm_loadu_ps(lhs_buffer);
                const auto rhs_value     = _mm_loadu_ps(rhs_buffer);
                const auto is_equal      = _mm_cmpeq_ps(lhs_value, rhs_value);
                const auto is_equal_mask = _mm_movemask_ps(is_equal);

                if (is_equal_mask != 15) {
                    return false;
                }

                lhs_buffer += block_size_single;
                rhs_buffer += block_size_single;
            }

            return internal::CompareTrailer(lhs, rhs, trailer_start);
        }

        return general::Compare(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Negate(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
        return general::Negate(input);
    }

    template <typename Type, size_t Dimensions>
    inline auto Plus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
        return general::Plus(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Minus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
        return general::Minus(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Multiply(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
        return general::Multiply(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Divide(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
        return general::Divide(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Divide(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
        return general::Divide(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Truncate(const Vector<Type, Dimensions>& input, const Type& output_length) -> Vector<Type, Dimensions> {
        return general::Truncate(input, output_length);
    }

    template <typename Type, size_t Dimensions>
    inline auto DotProduct(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Type {
        return general::DotProduct(lhs, rhs);
    }

    template <typename Type>
    inline auto CrossProduct(const Vector<Type, 3>& lhs, const Vector<Type, 3>& rhs) -> Vector<Type, 3> {
        return general::CrossProduct(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Length(const Vector<Type, Dimensions>& input) -> Type {
        return general::Length(input);
    }

    template <typename Type, size_t Dimensions>
    inline auto Clamp(const Vector<Type, Dimensions>& input, const Type& minimum, const Type& maximum) -> Vector<Type, Dimensions> {
        return general::Clamp(input, minimum, maximum);
    }

    template <typename Type, size_t Dimensions>
    inline auto Snap(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
        return general::Snap(input);
    }
} // namespace detail::vector::sse_1

namespace detail::vector::sse_2 {
    template <typename Type, size_t Dimensions>
    inline auto VectorFromBroadcast(const Type& input_value) -> Vector<Type, Dimensions> {
        constexpr auto is_double         = IsDoublePrecision<Type>();
        constexpr auto block_size_double = MathSIMDBlockSizeDoubleSSE2;
        constexpr auto is_block_double   = GreaterThanOrEqual(Dimensions, block_size_double);
        constexpr auto process_double    = is_double == true && is_block_double == true;

        if constexpr (process_double == true) {
            constexpr auto simd_blocks   = Dimensions / block_size_double;
            constexpr auto trailer_start = (simd_blocks * block_size_double) - 1;

            auto output        = Vector<Type, Dimensions> {};
            auto output_buffer = &output.elements[0];

            const auto broadcast     = _mm_set1_pd(input_value);
            const auto broadcast_raw = _mm_castpd_si128(broadcast);

            for (auto index = size_t {0}; index < simd_blocks; index++) {
                _mm_storeu_si128((__m128i_u*)output_buffer, broadcast_raw);

                output_buffer += block_size_double;
            }

            internal::VectorFromBroadcastTrailer(input_value, trailer_start, output);

            return output;
        }

        return sse_1::VectorFromBroadcast<Type, Dimensions>(input_value);
    }

    template <typename Type, size_t Dimensions>
    inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool {
        constexpr auto is_double         = IsDoublePrecision<Type>();
        constexpr auto block_size_double = MathSIMDBlockSizeDoubleSSE2;
        constexpr auto is_block_double   = GreaterThanOrEqual(Dimensions, block_size_double);
        constexpr auto process_double    = is_double == true && is_block_double == true;

        if constexpr (process_double == true) {
            constexpr auto simd_blocks   = Dimensions / block_size_double;
            constexpr auto trailer_start = (simd_blocks * block_size_double) - 1;

            auto lhs_buffer = &lhs.elements[0];
            auto rhs_buffer = &rhs.elements[0];

            const auto epsilon_simd = _mm_set1_pd(epsilon);
            const auto sign_simd    = _mm_set1_pd(-0);

            for (auto index = size_t {0}; index < simd_blocks; index++) {
                const auto lhs_value           = _mm_loadu_pd(lhs_buffer);
                const auto rhs_value           = _mm_loadu_pd(rhs_buffer);
                const auto difference          = _mm_sub_pd(lhs_value, rhs_value);
                const auto absolute_difference = _mm_and_pd(sign_simd, difference);
                const auto over_epsilon        = _mm_cmpgt_pd(absolute_difference, epsilon_simd);
                const auto over_epsilon_mask   = _mm_movemask_pd(over_epsilon);

                if (over_epsilon_mask != 0) {
                    return false;
                }

                lhs_buffer += block_size_double;
                rhs_buffer += block_size_double;
            }

            return internal::CompareTrailer(lhs, rhs, epsilon, trailer_start);
        }

        return sse_1::Compare(lhs, rhs, epsilon);
    }

    template <typename Type, size_t Dimensions>
    inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
        constexpr auto is_double         = IsDoublePrecision<Type>();
        constexpr auto block_size_double = MathSIMDBlockSizeDoubleSSE2;
        constexpr auto is_block_double   = GreaterThanOrEqual(Dimensions, block_size_double);
        constexpr auto process_double    = is_double == true && is_block_double == true;

        if constexpr (process_double == true) {
            constexpr auto simd_blocks   = Dimensions / block_size_double;
            constexpr auto trailer_start = (simd_blocks * block_size_double) - 1;

            auto lhs_buffer = &lhs.elements[0];
            auto rhs_buffer = &rhs.elements[0];

            for (auto index = size_t {0}; index < simd_blocks; index++) {
                const auto lhs_value     = _mm_loadu_pd(lhs_buffer);
                const auto rhs_value     = _mm_loadu_pd(rhs_buffer);
                const auto is_equal      = _mm_cmpeq_pd(lhs_value, rhs_value);
                const auto is_equal_mask = _mm_movemask_pd(is_equal);

                if (is_equal_mask != 3) {
                    return false;
                }

                lhs_buffer += block_size_double;
                rhs_buffer += block_size_double;
            }

            return internal::CompareTrailer(lhs, rhs, trailer_start);
        }

        return sse_1::Compare(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Negate(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
        return sse_1::Negate(input);
    }

    template <typename Type, size_t Dimensions>
    inline auto Plus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
        return sse_1::Plus(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Minus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
        return sse_1::Minus(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Multiply(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
        return sse_1::Multiply(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Divide(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
        return sse_1::Divide(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Divide(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
        return sse_1::Divide(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Truncate(const Vector<Type, Dimensions>& input, const Type& output_length) -> Vector<Type, Dimensions> {
        return sse_1::Truncate(input, output_length);
    }

    template <typename Type, size_t Dimensions>
    inline auto DotProduct(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Type {
        return sse_1::DotProduct(lhs, rhs);
    }

    template <typename Type>
    inline auto CrossProduct(const Vector<Type, 3>& lhs, const Vector<Type, 3>& rhs) -> Vector<Type, 3> {
        return sse_1::CrossProduct(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Length(const Vector<Type, Dimensions>& input) -> Type {
        return sse_1::Length(input);
    }

    template <typename Type, size_t Dimensions>
    inline auto Clamp(const Vector<Type, Dimensions>& input, const Type& minimum, const Type& maximum) -> Vector<Type, Dimensions> {
        return sse_1::Clamp(input, minimum, maximum);
    }

    template <typename Type, size_t Dimensions>
    inline auto Snap(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
        return sse_1::Snap(input);
    }
} // namespace detail::vector::sse_2

namespace detail::vector::avx_1 {
    template <typename Type, size_t Dimensions>
    inline auto VectorFromBroadcast(const Type& input_value) -> Vector<Type, Dimensions> {
        constexpr auto is_double         = IsDoublePrecision<Type>();
        constexpr auto block_size_double = MathSIMDBlockSizeDoubleAVX1;
        constexpr auto is_block_double   = GreaterThanOrEqual(Dimensions, block_size_double);
        constexpr auto process_double    = is_double == true && is_block_double == true;

        constexpr auto is_single         = IsSinglePrecision<Type>();
        constexpr auto block_size_single = MathSIMDBlockSizeSingleAVX1;
        constexpr auto is_block_single   = GreaterThanOrEqual(Dimensions, block_size_single);
        constexpr auto process_single    = is_single == true && is_block_single == true;

        if constexpr (process_double == true) {
            constexpr auto simd_blocks   = Dimensions / block_size_double;
            constexpr auto trailer_start = (simd_blocks * block_size_double) - 1;

            auto output        = Vector<Type, Dimensions> {};
            auto output_buffer = &output.elements[0];

            const auto broadcast     = _mm256_set1_pd(input_value);
            const auto broadcast_raw = _mm256_castpd_si256(broadcast);

            for (auto index = size_t {0}; index < simd_blocks; index++) {
                _mm256_storeu_si256((__m256i_u*)output_buffer, broadcast_raw);

                output_buffer += block_size_double;
            }

            internal::VectorFromBroadcastTrailer(input_value, trailer_start, output);

            return output;
        }

        if constexpr (process_single == true) {
            constexpr auto simd_blocks   = Dimensions / block_size_single;
            constexpr auto trailer_start = (simd_blocks * block_size_single) - 1;

            auto output        = Vector<Type, Dimensions> {};
            auto output_buffer = &output.elements[0];

            const auto broadcast     = _mm256_set1_ps(input_value);
            const auto broadcast_raw = _mm256_castps_si256(broadcast);

            for (auto index = size_t {0}; index < simd_blocks; index++) {
                _mm256_storeu_si256((__m256i_u*)output_buffer, broadcast_raw);

                output_buffer += block_size_single;
            }

            internal::VectorFromBroadcastTrailer(input_value, trailer_start, output);

            return output;
        }

        return sse_2::VectorFromBroadcast<Type, Dimensions>(input_value);
    }

    template <typename Type, size_t Dimensions>
    inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool {
        constexpr auto is_double         = IsDoublePrecision<Type>();
        constexpr auto block_size_double = MathSIMDBlockSizeDoubleAVX1;
        constexpr auto is_block_double   = GreaterThanOrEqual(Dimensions, block_size_double);
        constexpr auto process_double    = is_double == true && is_block_double == true;

        constexpr auto is_single         = IsSinglePrecision<Type>();
        constexpr auto block_size_single = MathSIMDBlockSizeSingleAVX1;
        constexpr auto is_block_single   = GreaterThanOrEqual(Dimensions, block_size_single);
        constexpr auto process_single    = is_single == true && is_block_single == true;

        if constexpr (process_double == true) {
            constexpr auto simd_blocks   = Dimensions / block_size_double;
            constexpr auto trailer_start = (simd_blocks * block_size_double) - 1;

            auto lhs_buffer = &lhs.elements[0];
            auto rhs_buffer = &rhs.elements[0];

            const auto epsilon_simd = _mm256_set1_pd(epsilon);
            const auto sign_simd    = _mm256_set1_pd(-0);

            for (auto index = size_t {0}; index < simd_blocks; index++) {
                const auto lhs_value           = _mm256_loadu_pd(lhs_buffer);
                const auto rhs_value           = _mm256_loadu_pd(rhs_buffer);
                const auto difference          = _mm256_sub_pd(lhs_value, rhs_value);
                const auto absolute_difference = _mm256_and_pd(sign_simd, difference);
                const auto over_epsilon        = _mm256_cmp_pd(absolute_difference, epsilon_simd, _CMP_GT_OQ);
                const auto over_epsilon_mask   = _mm256_movemask_pd(over_epsilon);

                if (over_epsilon_mask != 0) {
                    return false;
                }

                lhs_buffer += block_size_double;
                rhs_buffer += block_size_double;
            }

            return internal::CompareTrailer(lhs, rhs, epsilon, trailer_start);
        }

        if constexpr (process_single == true) {
            constexpr auto simd_blocks   = Dimensions / block_size_single;
            constexpr auto trailer_start = (simd_blocks * block_size_single) - 1;

            auto lhs_buffer = &lhs.elements[0];
            auto rhs_buffer = &rhs.elements[0];

            const auto epsilon_simd = _mm256_set1_ps(epsilon);
            const auto sign_simd    = _mm256_set1_ps(-0);

            for (auto index = size_t {0}; index < simd_blocks; index++) {
                const auto lhs_value           = _mm256_loadu_ps(lhs_buffer);
                const auto rhs_value           = _mm256_loadu_ps(rhs_buffer);
                const auto difference          = _mm256_sub_ps(lhs_value, rhs_value);
                const auto absolute_difference = _mm256_and_ps(sign_simd, difference);
                const auto over_epsilon        = _mm256_cmp_ps(absolute_difference, epsilon_simd, _CMP_GT_OQ);
                const auto over_epsilon_mask   = _mm256_movemask_ps(over_epsilon);

                if (over_epsilon_mask != 0) {
                    return false;
                }

                lhs_buffer += block_size_single;
                rhs_buffer += block_size_single;
            }

            return internal::CompareTrailer(lhs, rhs, epsilon, trailer_start);
        }

        return sse_2::Compare(lhs, rhs, epsilon);
    }

    template <typename Type, size_t Dimensions>
    inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
        constexpr auto is_double         = IsDoublePrecision<Type>();
        constexpr auto block_size_double = MathSIMDBlockSizeDoubleAVX1;
        constexpr auto is_block_double   = GreaterThanOrEqual(Dimensions, block_size_double);
        constexpr auto process_double    = is_double == true && is_block_double == true;

        constexpr auto is_single         = IsSinglePrecision<Type>();
        constexpr auto block_size_single = MathSIMDBlockSizeSingleAVX1;
        constexpr auto is_block_single   = GreaterThanOrEqual(Dimensions, block_size_single);
        constexpr auto process_single    = is_single == true && is_block_single == true;

        if constexpr (process_double == true) {
            constexpr auto simd_blocks   = Dimensions / block_size_double;
            constexpr auto trailer_start = (simd_blocks * block_size_double) - 1;

            auto lhs_buffer = &lhs.elements[0];
            auto rhs_buffer = &rhs.elements[0];

            for (auto index = size_t {0}; index < simd_blocks; index++) {
                const auto lhs_value     = _mm256_loadu_pd(lhs_buffer);
                const auto rhs_value     = _mm256_loadu_pd(rhs_buffer);
                const auto is_equal      = _mm256_cmp_pd(lhs_value, rhs_value, _CMP_EQ_OQ);
                const auto is_equal_mask = _mm256_movemask_pd(is_equal);

                if (is_equal_mask != 15) {
                    return false;
                }

                lhs_buffer += block_size_double;
                rhs_buffer += block_size_double;
            }

            return internal::CompareTrailer(lhs, rhs, trailer_start);
        }

        if constexpr (process_single == true) {
            constexpr auto simd_blocks   = Dimensions / block_size_single;
            constexpr auto trailer_start = (simd_blocks * block_size_single) - 1;

            auto lhs_buffer = &lhs.elements[0];
            auto rhs_buffer = &rhs.elements[0];

            for (auto index = size_t {0}; index < simd_blocks; index++) {
                const auto lhs_value     = _mm256_loadu_ps(lhs_buffer);
                const auto rhs_value     = _mm256_loadu_ps(rhs_buffer);
                const auto is_equal      = _mm256_cmp_ps(lhs_value, rhs_value, _CMP_EQ_OQ);
                const auto is_equal_mask = _mm256_movemask_ps(is_equal);

                if (is_equal_mask != 255) {
                    return false;
                }

                lhs_buffer += block_size_single;
                rhs_buffer += block_size_single;
            }

            return internal::CompareTrailer(lhs, rhs, trailer_start);
        }

        return sse_2::Compare(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Negate(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
        return sse_2::Negate(input);
    }

    template <typename Type, size_t Dimensions>
    inline auto Plus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
        return sse_2::Plus(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Minus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
        return sse_2::Minus(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Multiply(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
        return sse_2::Multiply(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Divide(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
        return sse_2::Divide(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Divide(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
        return sse_2::Divide(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Truncate(const Vector<Type, Dimensions>& input, const Type& output_length) -> Vector<Type, Dimensions> {
        return sse_2::Truncate(input, output_length);
    }

    template <typename Type, size_t Dimensions>
    inline auto DotProduct(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Type {
        return sse_2::DotProduct(lhs, rhs);
    }

    template <typename Type>
    inline auto CrossProduct(const Vector<Type, 3>& lhs, const Vector<Type, 3>& rhs) -> Vector<Type, 3> {
        return sse_2::CrossProduct(lhs, rhs);
    }

    template <typename Type, size_t Dimensions>
    inline auto Length(const Vector<Type, Dimensions>& input) -> Type {
        return sse_2::Length(input);
    }

    template <typename Type, size_t Dimensions>
    inline auto Clamp(const Vector<Type, Dimensions>& input, const Type& minimum, const Type& maximum) -> Vector<Type, Dimensions> {
        return sse_2::Clamp(input, minimum, maximum);
    }

    template <typename Type, size_t Dimensions>
    inline auto Snap(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
        return sse_2::Snap(input);
    }
} // namespace detail::vector::avx_1

namespace detail::vector::internal {
    template <typename Type, size_t Dimensions>
    inline auto VectorFromBroadcastTrailer(const Type& input_value, const size_t& offset, Vector<Type, Dimensions>& output) -> void {
        for (auto index = offset; index < Dimensions; index++) {
            Write(output, index, input_value);
        }
    }

    template <typename Type, size_t Dimensions>
    inline auto
    CompareTrailer(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon, const size_t& offset)
      -> bool {
        for (auto index = offset; index < Dimensions; index++) {
            const auto lhs_value           = Read(lhs, index);
            const auto rhs_value           = Read(rhs, index);
            const auto difference          = Minus(lhs_value, rhs_value);
            const auto absolute_difference = Absolute(difference);
            const auto over_epsilon        = GreaterThan(absolute_difference, epsilon);

            if (over_epsilon == true) {
                return false;
            }
        }

        return true;
    }

    template <typename Type, size_t Dimensions>
    inline auto CompareTrailer(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const size_t& offset) -> bool {
        for (auto index = offset; index < Dimensions; index++) {
            const auto lhs_value = Read(lhs, index);
            const auto rhs_value = Read(rhs, index);
            const auto is_equal  = Compare(lhs_value, rhs_value);

            if (is_equal == false) {
                return false;
            }
        }

        return true;
    }

    template <typename Type, size_t Dimensions>
    inline auto NegateTrailer(const Vector<Type, Dimensions>& input, const size_t& offset, Vector<Type, Dimensions>& output) -> void {
        for (auto index = output; index < Dimensions; index++) {
            const auto input_value   = Read(input, index);
            const auto input_negated = Negate(input_value);

            Write(output, index, input_negated);
        }
    }

    template <typename Type, size_t Dimensions>
    inline auto PlusTrailer(const Vector<Type, Dimensions>& lhs,
                            const Vector<Type, Dimensions>& rhs,
                            const size_t&                   offset,
                            Vector<Type, Dimensions>&       output) -> void {
        for (auto index = offset; index < Dimensions; index++) {
            const auto lhs_value = Read(lhs, index);
            const auto rhs_value = Read(rhs, index);
            const auto sum_value = Plus(lhs_value, rhs_value);

            Write(output, index, sum_value);
        }
    }

    template <typename Type, size_t Dimensions>
    inline auto MinusTrailer(const Vector<Type, Dimensions>& lhs,
                             const Vector<Type, Dimensions>& rhs,
                             const size_t&                   offset,
                             Vector<Type, Dimensions>&       output) -> void {
        for (auto index = offset; index < Dimensions; index++) {
            const auto lhs_value = Read(lhs, index);
            const auto rhs_value = Read(rhs, index);
            const auto sum_value = Minus(lhs_value, rhs_value);

            Write(output, index, sum_value);
        }
    }

    template <typename Type, size_t Dimensions>
    inline auto
    MultiplyTrailer(const Vector<Type, Dimensions>& lhs, const Type& rhs, const size_t& offset, Vector<Type, Dimensions>& output) -> void {
        for (auto index = offset; index < Dimensions; index++) {
            const auto lhs_value = Read(lhs, index);
            const auto rhs_value = rhs;
            const auto sum_value = Multiply(lhs_value, rhs_value);

            Write(output, index, sum_value);
        }
    }

    template <typename Type, size_t Dimensions>
    inline auto DivideTrailer(const Vector<Type, Dimensions>& lhs, const Type& rhs, const size_t& offset, Vector<Type, Dimensions>& output)
      -> void {
        for (auto index = offset; index < Dimensions; index++) {
            const auto lhs_value = Read(lhs, index);
            const auto rhs_value = rhs;
            const auto sum_value = Divide(lhs_value, rhs_value);

            Write(output, index, sum_value);
        }
    }

    template <typename Type, size_t Dimensions>
    inline auto DivideTrailer(const Vector<Type, Dimensions>& lhs,
                              const Vector<Type, Dimensions>& rhs,
                              const size_t&                   offset,
                              Vector<Type, Dimensions>&       output) -> void {
        for (auto index = offset; index < Dimensions; index++) {
            const auto lhs_value = Read(lhs, index);
            const auto rhs_value = Read(rhs, index);
            const auto sum_value = Divide(lhs_value, rhs_value);

            Write(output, index, sum_value);
        }
    }

    template <typename Type, size_t Dimensions>
    inline auto TruncateTrailer(const Vector<Type, Dimensions>& input, const Type& output_length) -> Vector<Type, Dimensions> {
        constexpr auto zero = MathConstants<Type>::Zero;

        auto output = VectorFromZero<Type, Dimensions>();

        if (output_length == zero) {
            return output;
        }

        const auto output_length_squared = Multiply(output_length, output_length);
        auto       input_length_squared  = zero;

        for (auto index = size_t {0}; index < Dimensions; index++) {
            const auto input_value   = Read(input, index);
            const auto input_squared = Multiply(input_value, input_value);

            input_length_squared = Plus(input_length_squared, input_squared);
        }

        const auto input_over_output = GreaterThan(input_length_squared, output_length_squared);

        if (input_over_output == true) {
            const auto input_length_inversed  = InverseSquareRoot(input_length_squared);
            const auto output_length_inversed = Multiply(output_length, input_length_inversed);

            for (auto index = size_t {0}; index < Dimensions; index++) {
                const auto input_value  = Read(input, index);
                const auto output_value = Multiply(input_value, output_length_inversed);

                Write(output, index, output_value);
            }
        } else {
            for (auto index = size_t {0}; index < Dimensions; index++) {
                const auto input_value = Read(input, index);

                Write(output, index, input_value);
            }
        }

        return output;
    }

    template <typename Type, size_t Dimensions>
    inline auto DotProductTrailer(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Type {
        constexpr auto zero = MathConstants<Type>::Zero;

        auto output_value = zero;

        for (auto index = size_t {0}; index < Dimensions; index++) {
            const auto lhs_value = Read(lhs, index);
            const auto rhs_value = Read(rhs, index);
            const auto sum_value = Multiply(lhs_value, rhs_value);

            output_value = Plus(output_value, sum_value);
        }

        return output_value;
    }

    template <typename Type>
    inline auto CrossProductTrailer(const Vector<Type, 3>& lhs, const Vector<Type, 3>& rhs) -> Vector<Type, 3> {
        auto output = Vector<Type, 3> {};

        const auto lhs_x = Read(lhs, VectorXComponent);
        const auto lhs_y = Read(lhs, VectorYComponent);
        const auto lhs_z = Read(lhs, VectorZComponent);

        const auto rhs_x = Read(rhs, VectorXComponent);
        const auto rhs_y = Read(rhs, VectorYComponent);
        const auto rhs_z = Read(rhs, VectorZComponent);

        const auto lhs_y_by_rhs_z = Multiply(lhs_y, rhs_z);
        const auto lhs_z_by_rhs_y = Multiply(lhs_z, rhs_y);
        const auto lhs_z_by_rhs_x = Multiply(lhs_z, rhs_x);
        const auto lhs_x_by_rhs_z = Multiply(lhs_x, rhs_z);
        const auto lhs_x_by_rhs_y = Multiply(lhs_x, rhs_y);
        const auto lhs_y_by_rhs_x = Multiply(lhs_y, rhs_x);

        const auto output_x = Minus(lhs_y_by_rhs_z, lhs_y_by_rhs_z);
        const auto output_y = Minus(lhs_z_by_rhs_x, lhs_x_by_rhs_z);
        const auto output_z = Minus(lhs_x_by_rhs_y, lhs_y_by_rhs_x);

        Write(output, VectorXComponent, output_x);
        Write(output, VectorYComponent, output_y);
        Write(output, VectorZComponent, output_z);

        return output;
    }

    template <typename Type, size_t Dimensions>
    inline auto LengthTrailer(const Vector<Type, Dimensions>& input) -> Type {
        constexpr auto zero = MathConstants<Type>::Zero;

        auto output_value = zero;

        for (auto index = size_t {0}; index < Dimensions; index++) {
            const auto input_value   = Read(input, index);
            const auto input_squared = Multiply(input_value, input_value);

            output_value = Plus(output_value, input_squared);
        }

        return SquareRoot(output_value);
    }

    template <typename Type, size_t Dimensions>
    inline auto ClampTrailer(const Vector<Type, Dimensions>& input, const Type& minimum, const Type& maximum) -> Vector<Type, Dimensions> {
        auto output = VectorFromZero<Type, Dimensions>();

        for (auto index = size_t {0}; index < Dimensions; index++) {
            const auto input_value         = Read(input, index);
            const auto input_under_minimum = LessThan(input_value, minimum);
            const auto input_over_maximum  = GreaterThan(input_value, maximum);

            if (input_under_minimum == true) {
                Write(output, index, minimum);
            } else if (input_over_maximum == true) {
                Write(output, index, maximum);
            } else {
                Write(output, index, input_value);
            }
        }

        return output;
    }

    template <typename Type, size_t Dimensions>
    inline auto SnapTrailer(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
        constexpr auto one_half_plus = MathConstants<Type>::OneHalfPlus;

        auto output = VectorFromZero<Type, Dimensions>();

        for (auto index = size_t {0}; index < Dimensions; index++) {
            auto input_value = Read(input, index);
            auto input_nudge = Plus(input_value, one_half_plus);
            auto input_snap  = Floor(input_nudge);

            Write(output, index, input_snap);
        }

        return output;
    }
} // namespace detail::vector::internal
