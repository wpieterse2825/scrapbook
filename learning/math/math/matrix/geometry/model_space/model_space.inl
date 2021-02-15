namespace math::matrix::geometry::model_space::detail {
    template <typename Type>
    inline auto ScaleX(const Matrix<Type, 4, 4>& value, Type scale) -> Matrix<Type, 4, 4>;

    template <typename Type>
    inline auto ScaleY(const Matrix<Type, 4, 4>& value, Type scale) -> Matrix<Type, 4, 4>;

    template <typename Type>
    inline auto ScaleZ(const Matrix<Type, 4, 4>& value, Type scale) -> Matrix<Type, 4, 4>;

    template <typename Type>
    inline auto RotateX(const Matrix<Type, 4, 4>& value, Type radians) -> Matrix<Type, 4, 4>;

    template <typename Type>
    inline auto RotateY(const Matrix<Type, 4, 4>& value, Type radians) -> Matrix<Type, 4, 4>;

    template <typename Type>
    inline auto RotateZ(const Matrix<Type, 4, 4>& value, Type radians) -> Matrix<Type, 4, 4>;

    template <typename Type>
    inline auto TranslateX(const Matrix<Type, 4, 4>& value, Type offset) -> Matrix<Type, 4, 4>;

    template <typename Type>
    inline auto TranslateY(const Matrix<Type, 4, 4>& value, Type offset) -> Matrix<Type, 4, 4>;

    template <typename Type>
    inline auto TranslateZ(const Matrix<Type, 4, 4>& value, Type offset) -> Matrix<Type, 4, 4>;
} // namespace math::matrix::geometry::model_space::detail

namespace math::matrix::geometry::model_space {
    template <typename Type>
    inline auto Create(const Matrix<Type, 4, 4>& value,
                       Type                      scale_x,
                       Type                      scale_y,
                       Type                      scale_z,
                       Type                      rotate_x,
                       Type                      rotate_y,
                       Type                      rotate_z,
                       Type                      translate_x,
                       Type                      translate_y,
                       Type                      translate_z) -> Matrix<Type, 4, 4> {
        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        result = math::matrix::geometry::model_space::detail::ScaleX(result, scale_x);
        result = math::matrix::geometry::model_space::detail::ScaleY(result, scale_y);
        result = math::matrix::geometry::model_space::detail::ScaleZ(result, scale_z);

        result = math::matrix::geometry::model_space::detail::RotateX(result, rotate_x);
        result = math::matrix::geometry::model_space::detail::RotateY(result, rotate_y);
        result = math::matrix::geometry::model_space::detail::RotateZ(result, rotate_z);

        result = math::matrix::geometry::model_space::detail::TranslateX(result, translate_x);
        result = math::matrix::geometry::model_space::detail::TranslateY(result, translate_y);
        result = math::matrix::geometry::model_space::detail::TranslateZ(result, translate_z);

        return math::matrix::Multiply(value, result);
    }

    template <typename Type>
    inline auto Create(Type scale_x,
                       Type scale_y,
                       Type scale_z,
                       Type rotate_x,
                       Type rotate_y,
                       Type rotate_z,
                       Type translate_x,
                       Type translate_y,
                       Type translate_z) -> Matrix<Type, 4, 4> {
        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        return math::matrix::geometry::model_space::Create(
          result, scale_x, scale_y, scale_z, rotate_x, rotate_y, rotate_z, translate_x, translate_y, translate_z);
    }
} // namespace math::matrix::geometry::model_space

namespace math::matrix::geometry::model_space::detail::constants {
    constexpr auto ScaleXRow    = size_t {0};
    constexpr auto ScaleXColumn = size_t {0};
    constexpr auto ScaleYRow    = size_t {1};
    constexpr auto ScaleYColumn = size_t {1};
    constexpr auto ScaleZRow    = size_t {2};
    constexpr auto ScaleZColumn = size_t {2};

    constexpr auto RotateXRowTop       = size_t {1};
    constexpr auto RotateXRowBottom    = size_t {2};
    constexpr auto RotateXColumnTop    = size_t {1};
    constexpr auto RotateXColumnBottom = size_t {2};
    constexpr auto RotateYRowTop       = size_t {0};
    constexpr auto RotateYRowBottom    = size_t {2};
    constexpr auto RotateYColumnTop    = size_t {0};
    constexpr auto RotateYColumnBottom = size_t {2};
    constexpr auto RotateZRowTop       = size_t {0};
    constexpr auto RotateZRowBottom    = size_t {1};
    constexpr auto RotateZColumnTop    = size_t {0};
    constexpr auto RotateZColumnBottom = size_t {1};

    constexpr auto TranslateXRow    = size_t {0};
    constexpr auto TranslateXColumn = size_t {3};
    constexpr auto TranslateYRow    = size_t {1};
    constexpr auto TranslateYColumn = size_t {3};
    constexpr auto TranslateZRow    = size_t {2};
    constexpr auto TranslateZColumn = size_t {3};
} // namespace math::matrix::geometry::model_space::detail::constants

namespace math::matrix::geometry::model_space::detail {
    template <typename Type>
    inline auto ScaleX(const Matrix<Type, 4, 4>& value, Type scale) -> Matrix<Type, 4, 4> {
        constexpr auto scale_x_row    = math::matrix::geometry::model_space::detail::constants::ScaleXRow;
        constexpr auto scale_x_column = math::matrix::geometry::model_space::detail::constants::ScaleXColumn;

        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        math::matrix::Write(result, scale_x_row, scale_x_column, scale);

        return math::matrix::Multiply(value, result);
    }

    template <typename Type>
    inline auto ScaleY(const Matrix<Type, 4, 4>& value, Type scale) -> Matrix<Type, 4, 4> {
        constexpr auto scale_y_row    = math::matrix::geometry::model_space::detail::constants::ScaleYRow;
        constexpr auto scale_y_column = math::matrix::geometry::model_space::detail::constants::ScaleYColumn;

        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        math::matrix::Write(result, scale_y_row, scale_y_column, scale);

        return math::matrix::Multiply(value, result);
    }

    template <typename Type>
    inline auto ScaleZ(const Matrix<Type, 4, 4>& value, Type scale) -> Matrix<Type, 4, 4> {
        constexpr auto scale_z_row    = math::matrix::geometry::model_space::detail::constants::ScaleZRow;
        constexpr auto scale_z_column = math::matrix::geometry::model_space::detail::constants::ScaleZColumn;

        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        math::matrix::Write(result, scale_z_row, scale_z_column, scale);

        return math::matrix::Multiply(value, result);
    }

    template <typename Type>
    inline auto RotateX(const Matrix<Type, 4, 4>& value, Type radians) -> Matrix<Type, 4, 4> {
        constexpr auto rotate_x_row_top       = math::matrix::geometry::model_space::detail::constants::RotateXRowTop;
        constexpr auto rotate_x_row_bottom    = math::matrix::geometry::model_space::detail::constants::RotateXRowBottom;
        constexpr auto rotate_x_column_top    = math::matrix::geometry::model_space::detail::constants::RotateXColumnTop;
        constexpr auto rotate_x_column_bottom = math::matrix::geometry::model_space::detail::constants::RotateXColumnBottom;

        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        const auto sine         = math::trigonometry::radians::Sine(radians);
        const auto cosine       = math::trigonometry::radians::Cosine(radians);
        const auto inverse_sine = math::arithmetic::Negate(sine);

        math::matrix::Write(result, rotate_x_row_top, rotate_x_column_top, cosine);
        math::matrix::Write(result, rotate_x_row_top, rotate_x_column_bottom, inverse_sine);
        math::matrix::Write(result, rotate_x_row_bottom, rotate_x_column_top, sine);
        math::matrix::Write(result, rotate_x_row_bottom, rotate_x_column_bottom, cosine);

        return math::matrix::Multiply(value, result);
    }

    template <typename Type>
    inline auto RotateY(const Matrix<Type, 4, 4>& value, Type radians) -> Matrix<Type, 4, 4> {
        constexpr auto rotate_y_row_top       = math::matrix::geometry::model_space::detail::constants::RotateYRowTop;
        constexpr auto rotate_y_row_bottom    = math::matrix::geometry::model_space::detail::constants::RotateYRowBottom;
        constexpr auto rotate_y_column_top    = math::matrix::geometry::model_space::detail::constants::RotateYColumnTop;
        constexpr auto rotate_y_column_bottom = math::matrix::geometry::model_space::detail::constants::RotateYColumnBottom;

        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        const auto sine         = math::trigonometry::radians::Sine(radians);
        const auto cosine       = math::trigonometry::radians::Cosine(radians);
        const auto inverse_sine = math::arithmetic::Negate(sine);

        math::matrix::Write(result, rotate_y_row_top, rotate_y_column_top, cosine);
        math::matrix::Write(result, rotate_y_row_top, rotate_y_column_bottom, sine);
        math::matrix::Write(result, rotate_y_row_bottom, rotate_y_column_top, inverse_sine);
        math::matrix::Write(result, rotate_y_row_bottom, rotate_y_column_bottom, cosine);

        return math::matrix::Multiply(value, result);
    }

    template <typename Type>
    inline auto RotateZ(const Matrix<Type, 4, 4>& value, Type radians) -> Matrix<Type, 4, 4> {
        constexpr auto rotate_z_row_top       = math::matrix::geometry::model_space::detail::constants::RotateZRowTop;
        constexpr auto rotate_z_row_bottom    = math::matrix::geometry::model_space::detail::constants::RotateZRowBottom;
        constexpr auto rotate_z_column_top    = math::matrix::geometry::model_space::detail::constants::RotateZColumnTop;
        constexpr auto rotate_z_column_bottom = math::matrix::geometry::model_space::detail::constants::RotateZColumnBottom;

        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        const auto sine         = math::trigonometry::radians::Sine(radians);
        const auto cosine       = math::trigonometry::radians::Cosine(radians);
        const auto inverse_sine = math::arithmetic::Negate(sine);

        math::matrix::Write(result, rotate_z_row_top, rotate_z_column_top, cosine);
        math::matrix::Write(result, rotate_z_row_top, rotate_z_column_bottom, inverse_sine);
        math::matrix::Write(result, rotate_z_row_bottom, rotate_z_column_top, sine);
        math::matrix::Write(result, rotate_z_row_bottom, rotate_z_column_bottom, cosine);

        return math::matrix::Multiply(value, result);
    }

    template <typename Type>
    inline auto TranslateX(const Matrix<Type, 4, 4>& value, Type offset) -> Matrix<Type, 4, 4> {
        constexpr auto translate_x_row    = math::matrix::geometry::model_space::detail::constants::TranslateXRow;
        constexpr auto translate_x_column = math::matrix::geometry::model_space::detail::constants::TranslateXColumn;

        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        math::matrix::Write(result, translate_x_row, translate_x_column, offset);

        return math::matrix::Multiply(value, result);
    }

    template <typename Type>
    inline auto TranslateY(const Matrix<Type, 4, 4>& value, Type offset) -> Matrix<Type, 4, 4> {
        constexpr auto translate_y_row    = math::matrix::geometry::model_space::detail::constants::TranslateYRow;
        constexpr auto translate_y_column = math::matrix::geometry::model_space::detail::constants::TranslateYColumn;

        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        math::matrix::Write(result, translate_y_row, translate_y_column, offset);

        return math::matrix::Multiply(value, result);
    }

    template <typename Type>
    inline auto TranslateZ(const Matrix<Type, 4, 4>& value, Type offset) -> Matrix<Type, 4, 4> {
        constexpr auto translate_z_row    = math::matrix::geometry::model_space::detail::constants::TranslateZRow;
        constexpr auto translate_z_column = math::matrix::geometry::model_space::detail::constants::TranslateZColumn;

        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        math::matrix::Write(result, translate_z_row, translate_z_column, offset);

        return math::matrix::Multiply(value, result);
    }
} // namespace math::matrix::geometry::model_space::detail
