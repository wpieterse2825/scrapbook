namespace math::matrix::geometry::view_space::detail {
    template <typename Type>
    inline auto ScaleToWindow(const Matrix<Type, 4, 4>& value, Type x_size, Type y_size) -> Matrix<Type, 4, 4>;

    template <typename Type>
    inline auto OffsetExtent(const Matrix<Type, 4, 4>& value, Type x_size, Type y_size) -> Matrix<Type, 4, 4>;

    template <typename Type>
    inline auto OffsetOrigin(const Matrix<Type, 4, 4>& value, Type x_offset, Type y_offset) -> Matrix<Type, 4, 4>;
} // namespace math::matrix::geometry::view_space::detail

namespace math::matrix::geometry::view_space {
    template <typename Type>
    inline auto Create(const Matrix<Type, 4, 4>& value, Type x_offset, Type y_offset, Type x_size, Type y_size) -> Matrix<Type, 4, 4> {
        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        result = math::matrix::geometry::view_space::detail::OffsetOrigin(result, x_offset, y_offset);
        result = math::matrix::geometry::view_space::detail::OffsetExtent(result, x_size, y_size);
        result = math::matrix::geometry::view_space::detail::ScaleToWindow(result, x_size, y_size);

        return math::matrix::Multiply(value, result);
    }

    template <typename Type>
    inline auto Create(Type x_offset, Type y_offset, Type x_size, Type y_size) -> Matrix<Type, 4, 4> {
        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        return math::matrix::geometry::view_space::Create(result, x_offset, y_offset, x_size, y_size);
    }
} // namespace math::matrix::geometry::view_space

namespace math::matrix::geometry::view_space::detail::constants {
    constexpr auto ScaleXRow    = size_t {0};
    constexpr auto ScaleXColumn = size_t {0};
    constexpr auto ScaleYRow    = size_t {1};
    constexpr auto ScaleYColumn = size_t {1};

    constexpr auto ExtentXRow    = size_t {0};
    constexpr auto ExtentXColumn = size_t {3};
    constexpr auto ExtentYRow    = size_t {1};
    constexpr auto ExtentYColumn = size_t {3};

    constexpr auto OriginXRow    = size_t {0};
    constexpr auto OriginXColumn = size_t {3};
    constexpr auto OriginYRow    = size_t {1};
    constexpr auto OriginYColumn = size_t {3};
} // namespace math::matrix::geometry::view_space::detail::constants

namespace math::matrix::geometry::view_space::detail {
    template <typename Type>
    inline auto ScaleToWindow(const Matrix<Type, 4, 4>& value, Type x_size, Type y_size) -> Matrix<Type, 4, 4> {
        constexpr auto two_positive   = math::Constants<Type>::TwoPositive;
        constexpr auto scale_x_row    = math::matrix::geometry::view_space::detail::constants::ScaleXRow;
        constexpr auto scale_x_column = math::matrix::geometry::view_space::detail::constants::ScaleXColumn;
        constexpr auto scale_y_row    = math::matrix::geometry::view_space::detail::constants::ScaleYRow;
        constexpr auto scale_y_column = math::matrix::geometry::view_space::detail::constants::ScaleYColumn;

        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        const auto half_x_size = math::arithmetic::Divide(x_size, two_positive);
        const auto half_y_size = math::arithmetic::Divide(y_size, two_positive);

        math::matrix::Write(result, scale_x_row, scale_x_column, half_x_size);
        math::matrix::Write(result, scale_y_row, scale_y_column, half_y_size);

        return math::matrix::Multiply(value, result);
    }

    template <typename Type>
    inline auto OffsetExtent(const Matrix<Type, 4, 4>& value, Type x_size, Type y_size) -> Matrix<Type, 4, 4> {
        constexpr auto two_positive    = math::Constants<Type>::TwoPositive;
        constexpr auto extent_x_row    = math::matrix::geometry::view_space::detail::constants::ExtentXRow;
        constexpr auto extent_x_column = math::matrix::geometry::view_space::detail::constants::ExtentXColumn;
        constexpr auto extent_y_row    = math::matrix::geometry::view_space::detail::constants::ExtentYRow;
        constexpr auto extent_y_column = math::matrix::geometry::view_space::detail::constants::ExtentYColumn;

        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        const auto half_x_size = math::arithmetic::Divide(x_size, two_positive);
        const auto half_y_size = math::arithmetic::Divide(y_size, two_positive);

        math::matrix::Write(result, extent_x_row, extent_x_column, half_x_size);
        math::matrix::Write(result, extent_y_row, extent_y_column, half_y_size);

        return math::matrix::Multiply(value, result);
    }

    template <typename Type>
    inline auto OffsetOrigin(const Matrix<Type, 4, 4>& value, Type x_offset, Type y_offset) -> Matrix<Type, 4, 4> {
        constexpr auto origin_x_row    = math::matrix::geometry::view_space::detail::constants::OriginXRow;
        constexpr auto origin_x_column = math::matrix::geometry::view_space::detail::constants::OriginXColumn;
        constexpr auto origin_y_row    = math::matrix::geometry::view_space::detail::constants::OriginYRow;
        constexpr auto origin_y_column = math::matrix::geometry::view_space::detail::constants::OriginYColumn;

        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        math::matrix::Write(result, origin_x_row, origin_x_column, x_offset);
        math::matrix::Write(result, origin_y_row, origin_y_column, y_offset);

        return math::matrix::Multiply(value, result);
    }
} // namespace math::matrix::geometry::view_space::detail
