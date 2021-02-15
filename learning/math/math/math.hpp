template <typename Type>
concept Decimal = requires(Type) {
    std::is_floating_point_v<Type>;
};

namespace math {
    template <Decimal Type>
    struct Constants {
        static constexpr auto ZeroNeutral    = Type {0.0};
        static constexpr auto OneHalfNeutral = Type {0.5};
        static constexpr auto OneNeutral     = Type {1.0};
        static constexpr auto TwoHalfNeutral = Type {1.5};
        static constexpr auto TwoNeutral     = Type {2.0};
        static constexpr auto ThreeNeutral   = Type {3.0};
        static constexpr auto FourNeutral    = Type {4.0};

        static constexpr auto PiNeutral = Type {M_PI};

        static constexpr auto DegreesOneQuarterNeutral    = Type {90.0};
        static constexpr auto DegreesTwoQuartersNeutral   = Type {180.0};
        static constexpr auto DegreesThreeQuartersNeutral = Type {270.0};
        static constexpr auto DegreesFourQuartersNeutral  = Type {320.0};

        static constexpr auto RadiansOneQuarterNeutral    = Type {PiNeutral * OneHalfNeutral};
        static constexpr auto RadiansTwoQuartersNeutral   = Type {PiNeutral * OneNeutral};
        static constexpr auto RadiansThreeQuartersNeutral = Type {PiNeutral * TwoHalfNeutral};
        static constexpr auto RadiansFourQuartersNeutral  = Type {PiNeutral * TwoNeutral};

        static constexpr auto ZeroPositive     = +ZeroNeutral;
        static constexpr auto OneHalfPositive  = +OneHalfNeutral;
        static constexpr auto OnePositive      = +OneNeutral;
        static constexpr auto TwoHalvePositive = +TwoHalfNeutral;
        static constexpr auto TwoPositive      = +TwoNeutral;
        static constexpr auto ThreePositive    = +ThreeNeutral;
        static constexpr auto FourPositive     = +FourNeutral;

        static constexpr auto PiPositive = +PiNeutral;

        static constexpr auto DegreesOneQuarterPositive    = +DegreesOneQuarterNeutral;
        static constexpr auto DegreesTwoQuartersPositive   = +DegreesTwoQuartersNeutral;
        static constexpr auto DegreesThreeQuartersPositive = +DegreesThreeQuartersNeutral;
        static constexpr auto DegreesFourQuartersPositive  = +DegreesFourQuartersNeutral;

        static constexpr auto RadiansOneQuarterPositive    = +RadiansOneQuarterNeutral;
        static constexpr auto RadiansTwoQuartersPositive   = +RadiansTwoQuartersNeutral;
        static constexpr auto RadiansThreeQuartersPositive = +RadiansThreeQuartersNeutral;
        static constexpr auto RadiansFourQuartersPositive  = +RadiansFourQuartersNeutral;

        static constexpr auto ZeroNegative     = -ZeroNeutral;
        static constexpr auto OneHalfNegative  = -OneHalfNeutral;
        static constexpr auto OneNegative      = -OneNeutral;
        static constexpr auto TwoHalveNegative = -TwoHalfNeutral;
        static constexpr auto TwoNegative      = -TwoNeutral;
        static constexpr auto ThreeNegative    = -ThreeNeutral;
        static constexpr auto FourNegative     = -FourNeutral;

        static constexpr auto PiNegative = -PiNeutral;

        static constexpr auto DegreesOneQuarterNegative    = -DegreesOneQuarterNeutral;
        static constexpr auto DegreesTwoQuartersNegative   = -DegreesTwoQuartersNeutral;
        static constexpr auto DegreesThreeQuartersNegative = -DegreesThreeQuartersNeutral;
        static constexpr auto DegreesFourQuartersNegative  = -DegreesFourQuartersNeutral;

        static constexpr auto RadiansOneQuarterNegative    = -RadiansOneQuarterNeutral;
        static constexpr auto RadiansTwoQuartersNegative   = -RadiansTwoQuartersNeutral;
        static constexpr auto RadiansThreeQuartersNegative = -RadiansThreeQuartersNeutral;
        static constexpr auto RadiansFourQuartersNegative  = -RadiansFourQuartersNeutral;
    };
} // namespace math

namespace math::arithmetic {
    template <Decimal Type>
    inline auto Affirm(Type value) -> Type;

    template <Decimal Type>
    inline auto Negate(Type value) -> Type;

    template <Decimal Type>
    inline auto Plus(Type lhs, Type rhs) -> Type;

    template <Decimal Type>
    inline auto Minus(Type lhs, Type rhs) -> Type;

    template <Decimal Type>
    inline auto Multiply(Type lhs, Type rhs) -> Type;

    template <Decimal Type>
    inline auto Divide(Type lhs, Type rhs) -> Type;
} // namespace math::arithmetic

namespace math::comparison {
    // TODO(wpieterse): Add epsilon calls for the below functions.
    template <Decimal Type>
    inline auto LessThan(Type lhs, Type rhs) -> bool;

    template <Decimal Type>
    inline auto LessThanOrEqual(Type lhs, Type rhs) -> bool;

    template <Decimal Type>
    inline auto GreaterThan(Type lhs, Type rhs) -> bool;

    template <Decimal Type>
    inline auto GreaterThanOrEqual(Type lhs, Type rhs) -> bool;

    template <Decimal Type>
    inline auto Compare(Type lhs, Type rhs, Type epsilon) -> bool;

    template <Decimal Type>
    inline auto Equal(Type lhs, Type rhs, Type epsilon) -> bool;

    template <Decimal Type>
    inline auto NotEqual(Type lhs, Type rhs, Type epsilon) -> bool;

    template <Decimal Type>
    inline auto Compare(Type lhs, Type rhs) -> bool;

    template <Decimal Type>
    inline auto Equal(Type lhs, Type rhs) -> bool;

    template <Decimal Type>
    inline auto NotEqual(Type lhs, Type rhs) -> bool;
} // namespace math::comparison

namespace math::mapping {
    template <Decimal Type>
    inline auto Floor(Type value) -> Type;

    template <Decimal Type>
    inline auto Ceiling(Type value) -> Type;

    template <Decimal Type>
    inline auto Absolute(Type value) -> Type;
} // namespace math::mapping

namespace math::trigonometry {
    template <Decimal Type>
    inline auto DegreesToRadians(Type degrees) -> Type;

    template <Decimal Type>
    inline auto RadiansToDegrees(Type radians) -> Type;
} // namespace math::trigonometry

namespace math::trigonometry::radians {
    template <Decimal Type>
    inline auto Sine(Type radians) -> Type;

    template <Decimal Type>
    inline auto Cosine(Type radians) -> Type;

    template <Decimal Type>
    inline auto Tangent(Type radians) -> Type;
} // namespace math::trigonometry::radians

namespace math::trigonometry::degrees {
    template <Decimal Type>
    inline auto Sine(Type degrees) -> Type;

    template <Decimal Type>
    inline auto Cosine(Type degrees) -> Type;

    template <Decimal Type>
    inline auto Tangent(Type degrees) -> Type;
} // namespace math::trigonometry::degrees

namespace math {
    namespace detail {
        template <typename Type, size_t Elements>
        concept SizedVector = requires(Type) {
            std::is_floating_point_v<Type>;
            Elements > 0;
        };
    } // namespace detail

    template <typename Type, size_t Elements>
    requires math::detail::SizedVector<Type, Elements> struct Vector {
        Type elements[Elements];
    };
} // namespace math

namespace math::vector {
    template <typename Type, size_t Elements>
    inline auto Read(const Vector<Type, Elements>& value, size_t index) -> Type;

    template <typename Type, size_t Elements>
    inline auto Write(Vector<Type, Elements>& value, size_t index, Type inner_value) -> void;

    template <typename Type, size_t Elements>
    inline auto CreateZero() -> Vector<Type, Elements>;

    template <typename Type, size_t Elements>
    inline auto CreateBroadcast(Type value) -> Vector<Type, Elements>;

    template <typename Type, size_t Elements>
    inline auto Print(const Vector<Type, Elements>& value) -> void;
} // namespace math::vector

namespace math {
    namespace detail {
        template <typename Type, size_t Rows, size_t Columns>
        concept SizedMatrix = requires(Type) {
            std::is_floating_point_v<Type>;
            Rows > 0;
            Columns > 0;
        };
    } // namespace detail

    template <typename Type, size_t Rows, size_t Columns>
    requires math::detail::SizedMatrix<Type, Rows, Columns> struct Matrix {
        Type elements[Rows][Columns];
    };
} // namespace math

namespace math::matrix {
    template <typename Type, size_t Rows, size_t Columns>
    inline auto Read(const Matrix<Type, Rows, Columns>& value, size_t row, size_t column) -> Type;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Write(Matrix<Type, Rows, Columns>& value, size_t row, size_t column, Type inner_value) -> void;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto CreateZero() -> Matrix<Type, Rows, Columns>;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto CreateDiagonal(Type value) -> Matrix<Type, Rows, Columns>;

    template <typename Type, size_t Elements>
    inline auto CreateDiagonal(const Vector<Type, Elements>& value) -> Matrix<Type, Elements, Elements>;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto CreateIdentity() -> Matrix<Type, Rows, Columns>;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Plus(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Rows, Columns>& rhs) -> Matrix<Type, Rows, Columns>;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Minus(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Rows, Columns>& rhs) -> Matrix<Type, Rows, Columns>;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Multiply(const Matrix<Type, Rows, Columns>& lhs, Type rhs) -> Matrix<Type, Rows, Columns>;

    template <typename Type, size_t LHSRows, size_t LHSColumns, size_t RHSRows, size_t RHSColumns>
    inline auto Multiply(const Matrix<Type, LHSRows, LHSColumns>& lhs, const Matrix<Type, RHSRows, RHSColumns>& rhs)
      -> Matrix<Type, LHSRows, RHSColumns>;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Transpose(const Matrix<Type, Rows, Columns>& value) -> Matrix<Type, Columns, Rows>;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Inverse(const Matrix<Type, Rows, Columns>& value) -> Matrix<Type, Rows, Columns>;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Negate(const Matrix<Type, Rows, Columns>& value) -> Matrix<Type, Rows, Columns>;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Clamp(const Matrix<Type, Rows, Columns>& value, Type minimum, Type maximum) -> Matrix<Type, Rows, Columns>;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto ClearLowerTriangle(const Matrix<Type, Rows, Columns>& value) -> Matrix<Type, Rows, Columns>;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto ClearUpperTriangle(const Matrix<Type, Rows, Columns>& value) -> Matrix<Type, Rows, Columns>;

    template <size_t OutRows, size_t OutColumns, typename Type, size_t InRows, size_t InColumns>
    inline auto ExtractSubMatrix(const Matrix<Type, InRows, InColumns>& value) -> Matrix<Type, OutRows, OutColumns>;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Difference(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Rows, Columns>& rhs) -> Type;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Trace(const Matrix<Type, Rows, Columns>& value) -> Type;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Determinant(const Matrix<Type, Rows, Columns>& value) -> Type;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Compare(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Rows, Columns>& rhs, Type epsilon) -> bool;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Compare(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Columns, Rows>& rhs) -> bool;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Equal(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Columns, Rows>& rhs, Type epsilon) -> bool;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto NotEqual(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Columns, Rows>& rhs, Type epsilon) -> bool;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Equal(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Columns, Rows>& rhs) -> bool;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto NotEqual(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Columns, Rows>& rhs) -> bool;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsZero(const Matrix<Type, Rows, Columns>& value, Type epsilon) -> bool;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsZero(const Matrix<Type, Rows, Columns>& value) -> bool;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsDiagonal(const Matrix<Type, Rows, Columns>& value, Type epsilon) -> bool;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsDiagonal(const Matrix<Type, Rows, Columns>& value) -> bool;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsIdentity(const Matrix<Type, Rows, Columns>& value, Type epsilon) -> bool;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsIdentity(const Matrix<Type, Rows, Columns>& value) -> bool;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsTriDiagonal(const Matrix<Type, Rows, Columns>& value, Type epsilon) -> bool;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsTriDiagonal(const Matrix<Type, Rows, Columns>& value) -> bool;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsSymmetric(const Matrix<Type, Rows, Columns>& value, Type epsilon) -> bool;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsSymmetric(const Matrix<Type, Rows, Columns>& value) -> bool;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto RowToVector(const Matrix<Type, Rows, Columns>& value, size_t row) -> Vector<Type, Columns>;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto ColumnToVector(const Matrix<Type, Rows, Columns>& value, size_t column) -> Vector<Type, Rows>;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Multiply(const Matrix<Type, Rows, Columns>& lhs, const Vector<Type, Columns>& rhs) -> Vector<Type, Columns>;

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Print(const Matrix<Type, Rows, Columns>& value) -> void;

} // namespace math::matrix

namespace math::matrix::geometry {
    template <typename Type>
    inline auto Create(const Matrix<Type, 4, 4>& value,
                       const Matrix<Type, 4, 4>& model,
                       const Matrix<Type, 4, 4>& view,
                       const Matrix<Type, 4, 4>& projection) -> Matrix<Type, 4, 4>;

    template <typename Type>
    inline auto Create(const Matrix<Type, 4, 4>& model, const Matrix<Type, 4, 4>& view, const Matrix<Type, 4, 4>& projection)
      -> Matrix<Type, 4, 4>;
} // namespace math::matrix::geometry

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
                       Type                      translate_z) -> Matrix<Type, 4, 4>;

    template <typename Type>
    inline auto Create(Type scale_x,
                       Type scale_y,
                       Type scale_z,
                       Type rotate_x,
                       Type rotate_y,
                       Type rotate_z,
                       Type translate_x,
                       Type translate_y,
                       Type translate_z) -> Matrix<Type, 4, 4>;
} // namespace math::matrix::geometry::model_space

namespace math::matrix::geometry::view_space {
    template <typename Type>
    inline auto Create(const Matrix<Type, 4, 4>& value, Type x_offset, Type y_offset, Type x_size, Type y_size) -> Matrix<Type, 4, 4>;

    template <typename Type>
    inline auto Create(Type x_offset, Type y_offset, Type x_size, Type y_size) -> Matrix<Type, 4, 4>;
} // namespace math::matrix::geometry::view_space

namespace math::matrix::geometry::projection_space::orthographic_projection {
    template <typename Type>
    inline auto Create(const Matrix<Type, 4, 4>& value, Type left, Type right, Type top, Type bottom, Type near, Type far)
      -> Matrix<Type, 4, 4>;

    template <typename Type>
    inline auto Create(Type left, Type right, Type top, Type bottom, Type near, Type far) -> Matrix<Type, 4, 4>;
} // namespace math::matrix::geometry::projection_space::orthographic_projection
