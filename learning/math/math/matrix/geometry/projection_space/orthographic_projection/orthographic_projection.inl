namespace math::matrix::geometry::projection_space::orthographic_projection::detail {
    template <typename Type>
    inline auto CenterAboutOrigin(const Matrix<Type, 4, 4>& value, Type left, Type right, Type top, Type bottom, Type near, Type far)
      -> Matrix<Type, 4, 4>;

    template <typename Type>
    inline auto ScaleView(const Matrix<Type, 4, 4>& value, Type left, Type right, Type top, Type bottom, Type near, Type far)
      -> Matrix<Type, 4, 4>;
} // namespace math::matrix::geometry::projection_space::orthographic_projection::detail

namespace math::matrix::geometry::projection_space::orthographic_projection {
    template <typename Type>
    inline auto Create(const Matrix<Type, 4, 4>& value, Type left, Type right, Type top, Type bottom, Type near, Type far)
      -> Matrix<Type, 4, 4> {
        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        result = math::matrix::geometry::projection_space::orthographic_projection::detail::CenterAboutOrigin(
          result, left, right, top, bottom, near, far);
        result =
          math::matrix::geometry::projection_space::orthographic_projection::detail::ScaleView(result, left, right, top, bottom, near, far);

        return math::matrix::Multiply(value, result);
    }

    template <typename Type>
    inline auto Create(Type left, Type right, Type top, Type bottom, Type near, Type far) -> Matrix<Type, 4, 4> {
        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        return math::matrix::geometry::projection_space::orthographic_projection::Create(result, left, right, top, bottom, near, far);
    }
} // namespace math::matrix::geometry::projection_space::orthographic_projection

namespace math::matrix::geometry::projection_space::orthographic_projection::detail::constants {
    constexpr auto OriginXRow    = size_t {0};
    constexpr auto OriginXColumn = size_t {3};
    constexpr auto OriginYRow    = size_t {1};
    constexpr auto OriginYColumn = size_t {3};
    constexpr auto OriginZRow    = size_t {2};
    constexpr auto OriginZColumn = size_t {3};

    constexpr auto ScaleXRow    = size_t {0};
    constexpr auto ScaleXColumn = size_t {0};
    constexpr auto ScaleYRow    = size_t {1};
    constexpr auto ScaleYColumn = size_t {1};
    constexpr auto ScaleZRow    = size_t {2};
    constexpr auto ScaleZColumn = size_t {2};
} // namespace math::matrix::geometry::projection_space::orthographic_projection::detail::constants

namespace math::matrix::geometry::projection_space::orthographic_projection::detail {
    template <typename Type>
    inline auto CenterAboutOrigin(const Matrix<Type, 4, 4>& value, Type left, Type right, Type top, Type bottom, Type near, Type far)
      -> Matrix<Type, 4, 4> {
        constexpr auto two_positive = math::Constants<Type>::TwoPositive;
        constexpr auto origin_x_row = math::matrix::geometry::projection_space::orthographic_projection::detail::constants::OriginXRow;
        constexpr auto origin_x_column =
          math::matrix::geometry::projection_space::orthographic_projection::detail::constants::OriginXColumn;
        constexpr auto origin_y_row = math::matrix::geometry::projection_space::orthographic_projection::detail::constants::OriginYRow;
        constexpr auto origin_y_column =
          math::matrix::geometry::projection_space::orthographic_projection::detail::constants::OriginYColumn;
        constexpr auto origin_z_row = math::matrix::geometry::projection_space::orthographic_projection::detail::constants::OriginZRow;
        constexpr auto origin_z_column =
          math::matrix::geometry::projection_space::orthographic_projection::detail::constants::OriginZColumn;

        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        const auto middle_x_sum     = math::arithmetic::Plus(left, right);
        const auto middle_x_half    = math::arithmetic::Divide(middle_x_sum, two_positive);
        const auto middle_x_negated = math::arithmetic::Negate(middle_x_half);
        const auto middle_y_sum     = math::arithmetic::Plus(bottom, top);
        const auto middle_y_half    = math::arithmetic::Divide(middle_y_sum, two_positive);
        const auto middle_y_negated = math::arithmetic::Negate(middle_y_half);
        const auto near_negated     = math::arithmetic::Negate(near);
        const auto far_negated      = math::arithmetic::Negate(far);
        const auto middle_z_sum     = math::arithmetic::Plus(near_negated, far_negated);
        const auto middle_z_half    = math::arithmetic::Divide(middle_z_sum, two_positive);
        const auto middle_z_negated = math::arithmetic::Negate(middle_z_half);

        math::matrix::Write(result, origin_x_row, origin_x_column, middle_x_negated);
        math::matrix::Write(result, origin_y_row, origin_y_column, middle_y_negated);
        math::matrix::Write(result, origin_z_row, origin_z_column, middle_z_negated);

        return math::matrix::Multiply(value, result);
    }

    template <typename Type>
    inline auto ScaleView(const Matrix<Type, 4, 4>& value, Type left, Type right, Type top, Type bottom, Type near, Type far)
      -> Matrix<Type, 4, 4> {
        constexpr auto two_positive   = math::Constants<Type>::TwoPositive;
        constexpr auto scale_x_row    = math::matrix::geometry::projection_space::orthographic_projection::detail::constants::ScaleXRow;
        constexpr auto scale_x_column = math::matrix::geometry::projection_space::orthographic_projection::detail::constants::ScaleXColumn;
        constexpr auto scale_y_row    = math::matrix::geometry::projection_space::orthographic_projection::detail::constants::ScaleYRow;
        constexpr auto scale_y_column = math::matrix::geometry::projection_space::orthographic_projection::detail::constants::ScaleYColumn;
        constexpr auto scale_z_row    = math::matrix::geometry::projection_space::orthographic_projection::detail::constants::ScaleZRow;
        constexpr auto scale_z_column = math::matrix::geometry::projection_space::orthographic_projection::detail::constants::ScaleZColumn;

        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        const auto scale_x_middle = math::arithmetic::Minus(right, left);
        const auto scale_x_half   = math::arithmetic::Divide(two_positive, scale_x_middle);
        const auto scale_y_middle = math::arithmetic::Minus(top, bottom);
        const auto scale_y_half   = math::arithmetic::Divide(two_positive, scale_y_middle);
        const auto scale_z_middle = math::arithmetic::Minus(far, near);
        const auto scale_z_half   = math::arithmetic::Divide(two_positive, scale_z_middle);

        math::matrix::Write(result, scale_x_row, scale_x_column, scale_x_half);
        math::matrix::Write(result, scale_y_row, scale_y_column, scale_y_half);
        math::matrix::Write(result, scale_z_row, scale_z_column, scale_z_half);

        return math::matrix::Multiply(value, result);
    }
} // namespace math::matrix::geometry::projection_space::orthographic_projection::detail
