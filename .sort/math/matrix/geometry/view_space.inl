template <typename Type>
inline auto ViewMatrixScale(Type x_size, Type y_size) -> Matrix<Type, 4, 4> {
    constexpr auto two_positive = MathConstants<Type>::TwoPositive;

    auto result = IdentityMatrix<Type, 4, 4>();

    const auto half_x_size = x_size / two_positive;
    const auto half_y_size = y_size / two_positive;

    result.elements[0][0] = half_x_size;
    result.elements[1][1] = half_y_size;

    return result;
}

template <typename Type>
inline auto ViewMatrixOffsetExtent(Type x_size, Type y_size) -> Matrix<Type, 4, 4> {
    constexpr auto two_positive = MathConstants<Type>::TwoPositive;

    auto result = IdentityMatrix<Type, 4, 4>();

    const auto half_x_size = x_size / two_positive;
    const auto half_y_size = y_size / two_positive;

    result.elements[0][3] = half_x_size;
    result.elements[1][3] = half_y_size;

    return result;
}

template <typename Type>
inline auto ViewMatrixOffsetOrigin(Type x_offset, Type y_offset) -> Matrix<Type, 4, 4> {
    auto result = IdentityMatrix<Type, 4, 4>();

    result.elements[0][3] = x_offset;
    result.elements[1][3] = y_offset;

    return result;
}

template <typename Type>
inline auto ViewMatrixGenerate(Type x_offset, Type y_offset, Type x_size, Type y_size) -> Matrix<Type, 4, 4> {
    auto result = IdentityMatrix<Type, 4, 4>();

    result = result * ViewMatrixOffsetOrigin(x_offset, y_offset);
    result = result * ViewMatrixOffsetExtent(x_size, y_size);
    result = result * ViewMatrixScale(x_size, y_size);

    return result;
}
