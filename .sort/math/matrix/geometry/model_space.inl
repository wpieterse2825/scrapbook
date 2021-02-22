template <typename Type>
inline auto ModelMatrixScaleX(Type scale) -> Matrix<Type, 4, 4> {
    auto result = IdentityMatrix<Type, 4, 4>();

    result.elements[0][0] = scale;

    return result;
}

template <typename Type>
inline auto ModelMatrixScaleY(Type scale) -> Matrix<Type, 4, 4> {
    auto result = IdentityMatrix<Type, 4, 4>();

    result.elements[1][1] = scale;

    return result;
}

template <typename Type>
inline auto ModelMatrixScaleZ(Type scale) -> Matrix<Type, 4, 4> {
    auto result = IdentityMatrix<Type, 4, 4>();

    result.elements[2][2] = scale;

    return result;
}

template <typename Type>
inline auto ModelMatrixRotateX(Type radians) -> Matrix<Type, 4, 4> {
    auto result = IdentityMatrix<Type, 4, 4>();

    const auto sine         = SineRadians(radians);
    const auto cosine       = CosineRadians(radians);
    const auto inverse_sine = -sine;

    result.elements[1][1] = cosine;
    result.elements[1][2] = inverse_sine;
    result.elements[2][1] = sine;
    result.elements[2][2] = cosine;

    return result;
}

template <typename Type>
inline auto ModelMatrixRotateY(Type radians) -> Matrix<Type, 4, 4> {
    auto result = IdentityMatrix<Type, 4, 4>();

    const auto sine         = SineRadians(radians);
    const auto cosine       = CosineRadians(radians);
    const auto inverse_sine = -sine;

    result.elements[0][0] = cosine;
    result.elements[0][2] = sine;
    result.elements[2][0] = inverse_sine;
    result.elements[2][2] = cosine;

    return result;
}

template <typename Type>
inline auto ModelMatrixRotateZ(Type radians) -> Matrix<Type, 4, 4> {
    auto result = IdentityMatrix<Type, 4, 4>();

    const auto sine         = SineRadians(radians);
    const auto cosine       = CosineRadians(radians);
    const auto inverse_sine = -sine;

    result.elements[0][0] = cosine;
    result.elements[0][1] = inverse_sine;
    result.elements[1][0] = sine;
    result.elements[1][1] = cosine;

    return result;
}

template <typename Type>
inline auto ModelMatrixTranslateX(Type offset) -> Matrix<Type, 4, 4> {
    auto result = IdentityMatrix<Type, 4, 4>();

    result.elements[0][3] = offset;

    return result;
}

template <typename Type>
inline auto ModelMatrixTranslateY(Type offset) -> Matrix<Type, 4, 4> {
    auto result = IdentityMatrix<Type, 4, 4>();

    result.elements[1][3] = offset;

    return result;
}

template <typename Type>
inline auto ModelMatrixTranslateZ(Type offset) -> Matrix<Type, 4, 4> {
    auto result = IdentityMatrix<Type, 4, 4>();

    result.elements[2][3] = offset;

    return result;
}

template <typename Type>
inline auto ModelMatrixGenerate(Type scale_x,
                                Type scale_y,
                                Type scale_z,
                                Type rotate_x,
                                Type rotate_y,
                                Type rotate_z,
                                Type translate_x,
                                Type translate_y,
                                Type translate_z) -> Matrix<Type, 4, 4> {
    auto result = IdentityMatrix<Type, 4, 4>();

    result = result * ModelMatrixScaleX(scale_x);
    result = result * ModelMatrixScaleY(scale_y);
    result = result * ModelMatrixScaleZ(scale_z);

    result = result * ModelMatrixRotateX(rotate_x);
    result = result * ModelMatrixRotateY(rotate_y);
    result = result * ModelMatrixRotateZ(rotate_z);

    result = result * ModelMatrixTranslateX(translate_x);
    result = result * ModelMatrixTranslateY(translate_y);
    result = result * ModelMatrixTranslateZ(translate_z);

    return result;
}
