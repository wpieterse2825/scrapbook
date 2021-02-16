template <typename Type>
inline auto OrthographicMatrixCenter(Type left, Type right, Type top, Type bottom, Type near, Type far) -> Matrix<Type, 4, 4> {
    constexpr auto two_positive = Constants<Type>::TwoPositive;

    auto result = IdentityMatrix<Type, 4, 4>();

    const auto near_negated = -near;
    const auto far_negated  = -far;

    const auto middle_x_sum     = left + right;
    const auto middle_x_half    = middle_x_sum / two_positive;
    const auto middle_x_negated = -middle_x_half;

    const auto middle_y_sum     = bottom + top;
    const auto middle_y_half    = middle_y_sum / two_positive;
    const auto middle_y_negated = -middle_y_half;

    const auto middle_z_sum     = near_negated + far_negated;
    const auto middle_z_half    = middle_z_sum / two_positive;
    const auto middle_z_negated = -middle_z_half;

    result.elements[0][3] = middle_x_negated;
    result.elements[1][3] = middle_y_negated;
    result.elements[2][3] = middle_z_negated;

    return result;
}

template <typename Type>
inline auto OrthographicMatrixScale(Type left, Type right, Type top, Type bottom, Type near, Type far) -> Matrix<Type, 4, 4> {
    constexpr auto two_positive = Constants<Type>::TwoPositive;

    auto result = IdentityMatrix<Type, 4, 4>();

    const auto scale_x_middle = right - left;
    const auto scale_x_half   = two_positive / scale_x_middle;

    const auto scale_y_middle = top - bottom;
    const auto scale_y_half   = two_positive / scale_y_middle;

    const auto scale_z_middle = far - near;
    const auto scale_z_half   = two_positive / scale_z_middle;

    result.elements[0][0] = scale_x_half;
    result.elements[1][1] = scale_y_half;
    result.elements[2][2] = scale_z_half;

    return result;
}

template <typename Type>
inline auto OrthographicMatrixGenerate(Type left, Type right, Type top, Type bottom, Type near, Type far) -> Matrix<Type, 4, 4> {
    auto result = IdentityMatrix<Type, 4, 4>();

    result = result * OrthographicMatrixCenter(left, right, top, bottom, near, far);
    result = result * OrthographicMatrixScale(left, right, top, bottom, near, far);

    return result;
}
