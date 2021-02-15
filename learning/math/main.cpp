#include <assert.h>
#include <math.h>
#include <iostream>

template <typename ElementType>
concept Integral = requires(ElementType) {
    std::is_integral_v<ElementType>;
};

template <typename ElementType>
concept Decimal = requires(ElementType) {
    std::is_floating_point_v<ElementType>;
};

template <typename LHSType, typename RHSType>
concept IsComparableEqual = requires(LHSType lhs, RHSType rhs) {
    lhs == rhs;
};

template <typename LHSType, typename RHSType>
concept IsComparableLessThan = requires(LHSType lhs, RHSType rhs) {
    lhs < rhs;
};

template <typename LHSType, typename RHSType>
concept IsComparableLessThanOrEqual = requires(LHSType lhs, RHSType rhs) {
    lhs <= rhs;
};

template <typename LHSType, typename RHSType>
concept IsComparableGreaterThan = requires(LHSType lhs, RHSType rhs) {
    lhs > rhs;
};

template <typename LHSType, typename RHSType>
concept IsComparableGreaterThanOrEqual = requires(LHSType lhs, RHSType rhs) {
    lhs >= rhs;
};

template <typename Type>
concept IsNegatable = requires(Type value) {
    -value;
};

template <typename LHSType, typename RHSType>
concept IsAddable = requires(LHSType lhs, RHSType rhs) {
    lhs + rhs;
};

template <typename LHSType, typename RHSType>
concept IsSubtractable = requires(LHSType lhs, RHSType rhs) {
    lhs + rhs;
};

template <typename LHSType, typename RHSType>
concept IsMultiplicable = requires(LHSType lhs, RHSType rhs) {
    lhs + rhs;
};

template <typename LHSType, typename RHSType>
concept IsDividable = requires(LHSType lhs, RHSType rhs) {
    lhs + rhs;
};

namespace math {
    template <Decimal ElementType>
    struct Constants {
        static constexpr auto Zero    = ElementType {0.0};
        static constexpr auto HalfOne = ElementType {0.5};
        static constexpr auto One     = ElementType {1.0};
        static constexpr auto HalfTwo = ElementType {1.5};
        static constexpr auto Two     = ElementType {2.0};

        static constexpr auto DegreesOneQuarter    = ElementType {90.0};
        static constexpr auto DegreesHalf          = ElementType {180.0};
        static constexpr auto DegreesThreeQuarters = ElementType {270.0};
        static constexpr auto DegreesFull          = ElementType {360.0};

        static constexpr auto Pi = ElementType {M_PI};

        static constexpr auto RadiansOneQuarter    = Pi * HalfOne;
        static constexpr auto RadiansHalf          = Pi * One;
        static constexpr auto RadiansThreeQuarters = Pi * HalfTwo;
        static constexpr auto RadiansFull          = Pi * Two;

        static constexpr auto PositiveZero    = +Zero;
        static constexpr auto PositiveHalfOne = +HalfOne;
        static constexpr auto PositiveOne     = +One;
        static constexpr auto PositiveHalfTwo = +HalfTwo;
        static constexpr auto PositiveTwo     = +Two;

        static constexpr auto PositiveDegreesOneQuarter    = +DegreesOneQuarter;
        static constexpr auto PositiveDegreesHalf          = +DegreesHalf;
        static constexpr auto PositiveDegreesThreeQuarters = +DegreesThreeQuarters;
        static constexpr auto PositiveDegreesFull          = +DegreesFull;

        static constexpr auto PositivePi = +Pi;

        static constexpr auto PositiveRadiansOneQuarter    = +RadiansOneQuarter;
        static constexpr auto PositiveRadiansHalf          = +RadiansHalf;
        static constexpr auto PositiveRadiansThreeQuarters = +RadiansThreeQuarters;
        static constexpr auto PositiveRadiansFull          = +RadiansFull;

        static constexpr auto NegativeZero    = -Zero;
        static constexpr auto NegativeHalfOne = -HalfOne;
        static constexpr auto NegativeOne     = -One;
        static constexpr auto NegativeHalfTwo = -HalfTwo;
        static constexpr auto NegativeTwo     = -Two;

        static constexpr auto NegativeDegreesOneQuarter    = -DegreesOneQuarter;
        static constexpr auto NegativeDegreesHalf          = -DegreesHalf;
        static constexpr auto NegativeDegreesThreeQuarters = -DegreesThreeQuarters;
        static constexpr auto NegativeDegreesFull          = -DegreesFull;

        static constexpr auto NegativePi = -Pi;

        static constexpr auto NegativeRadiansOneQuarter    = -RadiansOneQuarter;
        static constexpr auto NegativeRadiansHalf          = -RadiansHalf;
        static constexpr auto NegativeRadiansThreeQuarters = -RadiansThreeQuarters;
        static constexpr auto NegativeRadiansFull          = -RadiansFull;
    };

    namespace arithmetic {
        template <Integral Type>
        requires IsNegatable<Type> inline auto Negate(Type value) {
            return -value;
        }

        template <Integral LHSType, Integral RHSType>
        requires IsAddable<LHSType, RHSType> inline auto Add(LHSType lhs, RHSType rhs) -> LHSType {
            return lhs + rhs;
        }

        template <Integral LHSType, Integral RHSType>
        requires IsSubtractable<LHSType, RHSType> inline auto Subtract(LHSType lhs, RHSType rhs) -> LHSType {
            return lhs - rhs;
        }

        template <Integral LHSType, Integral RHSType>
        requires IsMultiplicable<LHSType, RHSType> inline auto Multiply(LHSType lhs, RHSType rhs) -> LHSType {
            return lhs * rhs;
        }

        template <Integral LHSType, Integral RHSType>
        requires IsDividable<LHSType, RHSType> inline auto Divide(LHSType lhs, RHSType rhs) -> LHSType {
            return lhs / rhs;
        }
    } // namespace arithmetic

    namespace special {
        template <Decimal ElementType>
        inline auto Floor(ElementType value) -> ElementType {
            if constexpr (std::is_same_v<float, ElementType> == true) {
                return ::floorf(value);
            }

            if constexpr (std::is_same_v<double, ElementType> == true) {
                return ::floor(value);
            }

            return ::floorl(value);
        }

        template <Decimal ElementType>
        inline auto Ceiling(ElementType value) -> ElementType {
            if constexpr (std::is_same_v<float, ElementType> == true) {
                return ::ceilf(value);
            }

            if constexpr (std::is_same_v<double, ElementType> == true) {
                return ::ceil(value);
            }

            return ::ceill(value);
        }

        template <Integral ElementType>
        inline auto Absolute(ElementType value) -> ElementType {
            if constexpr (std::is_same_v<float, ElementType> == true) {
                return ::fabsf(value);
            }

            if constexpr (std::is_same_v<double, ElementType> == true) {
                return ::fabs(value);
            }

            if constexpr (std::is_same_v<long double, ElementType> == true) {
                return ::fabsl(value);
            }

            return ::abs(value);
        }
    } // namespace special

    namespace utilities {
        // TODO(wpieterse): Add epsilon calls for the below functions.
        template <Integral LHSType, Integral RHSType>
        requires IsComparableLessThan<LHSType, RHSType> inline auto LessThan(LHSType lhs, RHSType rhs) -> bool {
            return lhs < rhs;
        }

        template <Integral LHSType, Integral RHSType>
        requires IsComparableLessThanOrEqual<LHSType, RHSType> inline auto LessThanOrEqual(LHSType lhs, RHSType rhs) -> bool {
            return lhs <= rhs;
        }

        template <Integral LHSType, Integral RHSType>
        requires IsComparableGreaterThan<LHSType, RHSType> inline auto GreaterThan(LHSType lhs, RHSType rhs) -> bool {
            return lhs > rhs;
        }

        template <Integral LHSType, Integral RHSType>
        requires IsComparableGreaterThanOrEqual<LHSType, RHSType> inline auto GreaterThanOrEqual(LHSType lhs, RHSType rhs) -> bool {
            return lhs >= rhs;
        }

        template <Decimal LHSType, Decimal RHSType, Decimal EpsilonType>
        inline auto Compare(LHSType lhs, RHSType rhs, EpsilonType epsilon) -> bool {
            auto difference          = arithmetic::Subtract(lhs, rhs);
            auto absolute_difference = special::Absolute(difference);

            if (utilities::GreaterThan(absolute_difference, epsilon) == true) {
                return false;
            }

            return true;
        }

        template <typename LHSType, typename RHSType, typename EpsilonType>
        inline auto Equal(LHSType lhs, RHSType rhs, EpsilonType epsilon) -> bool {
            return Compare(lhs, rhs, epsilon) == true;
        }

        template <typename LHSType, typename RHSType, typename EpsilonType>
        inline auto NotEqual(LHSType lhs, RHSType rhs, EpsilonType epsilon) -> bool {
            return Compare(lhs, rhs, epsilon) == false;
        }

        template <Integral LHSType, Integral RHSType>
        requires IsComparableEqual<LHSType, RHSType> inline auto Compare(LHSType lhs, RHSType rhs) -> bool {
            return lhs == rhs;
        }

        template <typename LHSType, typename RHSType>
        inline auto Equal(LHSType lhs, RHSType rhs) -> bool {
            return Compare(lhs, rhs) == true;
        }

        template <typename LHSType, typename RHSType>
        inline auto NotEqual(LHSType lhs, RHSType rhs) -> bool {
            return Compare(lhs, rhs) == false;
        }
    } // namespace utilities

    namespace trigonometry {
        template <Decimal ElementType>
        inline auto DegreeToRadian(ElementType degree) -> ElementType {
            constexpr auto positive_pi            = Constants<ElementType>::PositivePi;
            constexpr auto positive_degree_half   = Constants<ElementType>::PositiveDegreesHalf;
            auto           degree_to_radian_scale = arithmetic::Divide(positive_pi, positive_degree_half);

            return arithmetic::Multiply(degree, degree_to_radian_scale);
        }

        template <Decimal ElementType>
        inline auto RadianToDegree(ElementType radian) -> ElementType {
            constexpr auto positive_degree_half   = Constants<ElementType>::PositiveDegreesHalf;
            constexpr auto positive_pi            = Constants<ElementType>::PositivePi;
            auto           radian_to_degree_scale = arithmetic::Divide(positive_degree_half, positive_pi);

            return arithmetic::Multiply(radian, radian_to_degree_scale);
        }

        namespace radian {
            template <Decimal ElementType>
            inline auto Sine(ElementType radians) -> ElementType {
                if constexpr (std::is_same_v<float, ElementType> == true) {
                    return ::sinf(radians);
                }

                if constexpr (std::is_same_v<double, ElementType> == true) {
                    return ::sin(radians);
                }

                return ::sinl(radians);
            }

            template <Decimal ElementType>
            inline auto Cosine(ElementType radians) -> ElementType {
                if constexpr (std::is_same_v<float, ElementType> == true) {
                    return ::cosf(radians);
                }

                if constexpr (std::is_same_v<double, ElementType> == true) {
                    return ::cos(radians);
                }

                return ::cosl(radians);
            }

            template <Decimal ElementType>
            inline auto Tangent(ElementType radians) -> ElementType {
                if constexpr (std::is_same_v<float, ElementType> == true) {
                    return ::tanf(radians);
                }

                if constexpr (std::is_same_v<double, ElementType> == true) {
                    return ::tan(radians);
                }

                return ::tanl(radians);
            }
        } // namespace radian

        namespace degrees {
            template <Decimal ElementType>
            inline auto Sine(ElementType degrees) -> ElementType {
                auto degrees_to_radians = math::trigonometry::DegreeToRadian(degrees);

                return math::trigonometry::radian::Sine(degrees_to_radians);
            }

            template <Decimal ElementType>
            inline auto Cosine(ElementType degrees) -> ElementType {
                auto degrees_to_radians = math::trigonometry::DegreeToRadian(degrees);

                return math::trigonometry::radian::Cosine(degrees_to_radians);
            }

            template <Decimal ElementType>
            inline auto Tangent(ElementType degrees) -> ElementType {
                auto degrees_to_radians = math::trigonometry::DegreeToRadian(degrees);

                return math::trigonometry::radian::Tangent(degrees_to_radians);
            }
        } // namespace degrees
    }     // namespace trigonometry

    template <typename ElementType, size_t Elements>
    concept SizedVector = requires(ElementType) {
        std::is_integral_v<ElementType>;
        Elements > 0;
    };

    template <typename ElementType, size_t Elements>
    requires SizedVector<ElementType, Elements> struct Vector {
        ElementType elements[Elements];
    };

    namespace vector {
        template <typename ElementType, size_t Elements>
        inline auto ElementCount(const Vector<ElementType, Elements>& value) -> size_t {
            (void)value;

            return Elements;
        }

        template <typename ElementType, size_t Elements>
        inline auto ElementsPointer(const Vector<ElementType, Elements>& value) -> const ElementType* {
            return &value.elements[0][0];
        }

        template <typename ElementType, size_t Elements>
        inline auto ElementPointerForIndex(const Vector<ElementType, Elements>& value, size_t index) -> const ElementType* {
            assert(index < Elements);

            auto elements = vector::ElementsPointer(value);

            return &elements[index];
        }

        template <typename ElementType, size_t Elements>
        inline auto Read(const Vector<ElementType, Elements>& value, size_t index) -> ElementType {
            assert(index < Elements);

            return value.elements[index];
        }

        template <typename ElementType, size_t Elements>
        inline auto Write(Vector<ElementType, Elements>& value, size_t index, ElementType inner_value) -> void {
            assert(index < Elements);

            value.elements[index] = inner_value;
        }

        template <typename ElementType, size_t Elements>
        inline auto Zero() -> Vector<ElementType, Elements> {
            constexpr auto positive_zero = Constants<ElementType>::PositiveZero;
            auto           result        = Vector<ElementType, Elements> {};

            for (auto index = size_t {0}; index < Elements; index++) {
                vector::Write(result, index, positive_zero);
            }

            return result;
        }

        template <typename ElementType, size_t Elements>
        inline auto Set(ElementType value) -> Vector<ElementType, Elements> {
            auto result = Vector<ElementType, Elements> {};

            for (auto index = size_t {0}; index < Elements; index++) {
                vector::Write(result, index, value);
            }

            return result;
        }

        template <typename ElementType, size_t Elements>
        inline auto Print(const Vector<ElementType, Elements>& value) -> void {
            constexpr auto elements_minus_one = Elements - 1;

            std::cout << "[ ";

            for (auto index = size_t {0}; index < Elements; index++) {
                auto inner_value = vector::Read(value, index);

                std::cout << inner_value;
                if (utilities::LessThan(index, elements_minus_one) == true) {
                    std::cout << ", ";
                }
            }

            std::cout << " ]";
            std::cout << std::endl;
        }
    } // namespace vector

    template <typename ElementType, size_t Rows, size_t Columns>
    concept SizedMatrix = requires(ElementType) {
        std::is_integral_v<ElementType>;
        Rows > 0;
        Columns > 0;
    };

    template <typename ElementType, size_t Rows, size_t Columns>
    requires SizedMatrix<ElementType, Rows, Columns> struct Matrix {
        ElementType elements[Rows][Columns];
    };

    static constexpr auto TransformMatrixRows    = size_t {4};
    static constexpr auto TransformMatrixColumns = size_t {4};

    template <typename ElementType>
    using TransformMatrix = Matrix<ElementType, TransformMatrixRows, TransformMatrixColumns>;

    static constexpr auto ViewMatrixRows    = size_t {4};
    static constexpr auto ViewMatrixColumns = size_t {4};

    template <typename ElementType>
    using ViewMatrix = Matrix<ElementType, ViewMatrixRows, ViewMatrixColumns>;

    static constexpr auto ProjectionMatrixRows    = size_t {4};
    static constexpr auto ProjectionMatrixColumns = size_t {4};

    template <typename ElementType>
    using ProjectionMatrix = Matrix<ElementType, ProjectionMatrixRows, ProjectionMatrixColumns>;

    namespace matrix {
        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto RowCount(const Matrix<ElementType, Rows, Columns>& value) -> size_t {
            (void)value;

            return Rows;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto ColumnCount(const Matrix<ElementType, Rows, Columns>& value) -> size_t {
            (void)value;

            return Columns;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto ElementsPointer(const Matrix<ElementType, Rows, Columns>& value) -> const ElementType* {
            return &value.elements[0][0];
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto ElementPointerForRow(const Matrix<ElementType, Rows, Columns>& value, size_t row) -> const ElementType* {
            assert(row < Rows);

            auto elements = matrix::ElementsPointer(value);

            return &elements[row][0];
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto ElementPointerForRowAndColumn(const Matrix<ElementType, Rows, Columns>& value, size_t row, size_t column)
          -> const ElementType* {
            assert(row < Rows);
            assert(column < Columns);

            auto elements = matrix::ElementsPointer(value);

            return &elements[row][column];
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Read(const Matrix<ElementType, Rows, Columns>& value, size_t row, size_t column) -> ElementType {
            assert(row < Rows);
            assert(column < Columns);

            return value.elements[row][column];
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Write(Matrix<ElementType, Rows, Columns>& value, size_t row, size_t column, ElementType inner_value) -> void {
            assert(row < Rows);
            assert(column < Columns);

            value.elements[row][column] = inner_value;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Zero() -> Matrix<ElementType, Rows, Columns> {
            constexpr auto positive_zero = Constants<ElementType>::PositiveZero;
            auto           result        = Matrix<ElementType, Rows, Columns> {};

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    matrix::Write(result, row, column, positive_zero);
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Diagonal(ElementType value) -> Matrix<ElementType, Rows, Columns> {
            constexpr auto positive_zero = Constants<ElementType>::PositiveZero;
            auto           result        = Matrix<ElementType, Rows, Columns> {};

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    if (utilities::Equal(row, column) == true) {
                        matrix::Write(result, row, column, value);
                    } else {
                        matrix::Write(result, row, column, positive_zero);
                    }
                }
            }

            return result;
        }

        template <typename ElementType, size_t Elements>
        inline auto Diagonal(const Vector<ElementType, Elements>& value) -> Matrix<ElementType, Elements, Elements> {
            constexpr auto positive_zero = Constants<ElementType>::PositiveZero;
            auto           result        = Matrix<ElementType, Elements, Elements> {};

            for (auto row = size_t {0}; row < Elements; row++) {
                for (auto column = size_t {0}; column < Elements; column++) {
                    auto inner_value = positive_zero;

                    if (utilities::Equal(row, column) == true) {
                        inner_value = vector::Read(value, row);
                    }

                    matrix::Write(result, row, column, inner_value);
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Identity() -> Matrix<ElementType, Rows, Columns> {
            constexpr auto positive_one = Constants<ElementType>::PositiveOne;

            return matrix::Diagonal<ElementType, Rows, Columns>(positive_one);
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Add(const Matrix<ElementType, Rows, Columns>& lhs, const Matrix<ElementType, Rows, Columns>& rhs)
          -> Matrix<ElementType, Rows, Columns> {
            auto result = Matrix<ElementType, Rows, Columns> {};

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    auto lhs_value = matrix::Read(lhs, row, column);
                    auto rhs_value = matrix::Read(rhs, row, column);
                    auto sum       = arithmetic::Add(lhs_value, rhs_value);

                    matrix::Write(result, row, column, sum);
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Subtract(const Matrix<ElementType, Rows, Columns>& lhs, const Matrix<ElementType, Rows, Columns>& rhs)
          -> Matrix<ElementType, Rows, Columns> {
            auto result = Matrix<ElementType, Rows, Columns> {};

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    auto lhs_value = matrix::Read(lhs, row, column);
                    auto rhs_value = matrix::Read(rhs, row, column);
                    auto sum       = arithmetic::Subtract(lhs_value, rhs_value);

                    matrix::Write(result, row, column, sum);
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Multiply(const Matrix<ElementType, Rows, Columns>& lhs, ElementType rhs) -> Matrix<ElementType, Rows, Columns> {
            auto result = Matrix<ElementType, Rows, Columns> {};

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    auto lhs_value = matrix::Read(lhs, row, column);
                    auto rhs_value = rhs;
                    auto sum       = arithmetic::Multiply(lhs_value, rhs_value);

                    matrix::Write(result, row, column, sum);
                }
            }

            return result;
        }

        template <typename ElementType, size_t LHSRows, size_t LHSColumns, size_t RHSRows, size_t RHSColumns>
        inline auto Multiply(const Matrix<ElementType, LHSRows, LHSColumns>& lhs, const Matrix<ElementType, RHSColumns, RHSRows>& rhs)
          -> Matrix<ElementType, LHSRows, RHSColumns> {
            auto result         = Matrix<ElementType, LHSRows, RHSColumns> {};
            auto lhs_pointer    = &lhs.elements[0][0];
            auto rhs_base       = &rhs.elements[0][0];
            auto result_pointer = &result.elements[0][0];

            static_assert(LHSRows == RHSColumns);

            for (auto row = size_t {0}; row < LHSRows; row++) {
                for (auto column = size_t {0}; column < RHSColumns; column++) {
                    auto rhs_pointer = rhs_base + column;
                    auto sum         = lhs_pointer[0] * rhs_pointer[0];

                    for (auto inner_index = size_t {1}; inner_index < LHSColumns; inner_index++) {
                        rhs_pointer += RHSColumns;

                        sum += lhs_pointer[inner_index] * rhs_pointer[0];
                    }

                    *result_pointer = sum;

                    result_pointer++;
                }

                lhs_pointer += LHSColumns;
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Transpose(const Matrix<ElementType, Rows, Columns>& value) -> Matrix<ElementType, Columns, Rows> {
            auto result = Matrix<ElementType, Columns, Rows> {};

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    auto inner_value = matrix::Read(value, row, column);

                    matrix::Write(result, column, row, inner_value);
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Inverse(const Matrix<ElementType, Rows, Columns>& value) -> Matrix<ElementType, Rows, Columns> {
            auto result = Matrix<ElementType, Rows, Columns> {};

            static_assert(Rows == Columns);

            // TODO(wpieterse): Implement me!

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Negate(const Matrix<ElementType, Rows, Columns>& value) -> Matrix<ElementType, Rows, Columns> {
            auto result = Matrix<ElementType, Rows, Columns> {};

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    auto inner_value   = matrix::Read(value, row, column);
                    auto negated_value = arithmetic::Negate(inner_value);

                    matrix::Write(result, row, column, negated_value);
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Clamp(const Matrix<ElementType, Rows, Columns>& value, ElementType minimum, ElementType maximum)
          -> Matrix<ElementType, Rows, Columns> {
            auto result = Matrix<ElementType, Rows, Columns> {};

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    auto inner_value = matrix::Read(value, row, column);

                    if (utilities::LessThan(inner_value, minimum) == true) {
                        inner_value = minimum;
                    } else if (utilities::GreaterThan(inner_value, maximum) == true) {
                        inner_value = maximum;
                    }

                    matrix::Write(result, row, column, inner_value);
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto ClearLowerTriangle(const Matrix<ElementType, Rows, Columns>& value) -> Matrix<ElementType, Rows, Columns> {
            auto result = Matrix<ElementType, Rows, Columns> {};

            // TODO(wpieterse): Implement me!

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto ClearUpperTriangle(const Matrix<ElementType, Rows, Columns>& value) -> Matrix<ElementType, Rows, Columns> {
            auto result = Matrix<ElementType, Rows, Columns> {};

            // TODO(wpieterse): Implement me!

            return result;
        }

        template <size_t OutRows, size_t OutColumns, typename ElementType, size_t InRows, size_t InColumns>
        inline auto ExtractSubMatrix(const Matrix<ElementType, InRows, InColumns>& value) -> Matrix<ElementType, OutRows, OutColumns> {
            auto result = Matrix<ElementType, OutRows, OutColumns> {};

            static_assert(OutRows <= InRows);
            static_assert(OutColumns <= InColumns);

            for (auto row = size_t {0}; row < OutRows; row++) {
                for (auto column = size_t {0}; column < OutColumns; column++) {
                    auto inner_value = matrix::Read(value, row, column);

                    matrix::Write(result, row, column, inner_value);
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Difference(const Matrix<ElementType, Rows, Columns>& lhs, const Matrix<ElementType, Columns, Rows>& rhs)
          -> ElementType {
            constexpr auto positive_zero = Constants<ElementType>::PositiveZero;
            constexpr auto negative_one  = Constants<ElementType>::NegativeOne;
            auto           result        = negative_one;

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    auto lhs_value           = matrix::Read(lhs, row, column);
                    auto rhs_value           = matrix::Read(rhs, row, column);
                    auto difference          = arithmetic::Subtract(lhs_value, rhs_value);
                    auto absolute_difference = special::Absolute(difference);

                    if (utilities::LessThan(result, positive_zero) == true) {
                        result = absolute_difference;
                    }

                    if (utilities::GreaterThan(absolute_difference, result) == true) {
                        result = absolute_difference;
                    }
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Trace(const Matrix<ElementType, Rows, Columns>& value) -> ElementType {
            constexpr auto positive_zero = Constants<ElementType>::PositiveZero;
            auto           result        = positive_zero;

            static_assert(Rows == Columns);

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    if (utilities::Equal(row, column) == true) {
                        auto inner_value = matrix::Read(value, row, column);

                        result = arithmetic::Add(result, inner_value);
                    }
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Determinant(const Matrix<ElementType, Rows, Columns>& value) -> ElementType {
            constexpr auto positive_zero = Constants<ElementType>::PositiveZero;
            auto           result        = positive_zero;

            static_assert(Rows == Columns);

            // TODO(wpieterse): Implement me!

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto
        Compare(const Matrix<ElementType, Rows, Columns>& lhs, const Matrix<ElementType, Columns, Rows>& rhs, ElementType epsilon) -> bool {
            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    auto lhs_value = matrix::Read(lhs, row, column);
                    auto rhs_value = matrix::Read(rhs, row, column);

                    if (utilities::Compare(lhs_value, rhs_value, epsilon) == false) {
                        return false;
                    }
                }
            }

            return true;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Compare(const Matrix<ElementType, Rows, Columns>& lhs, const Matrix<ElementType, Columns, Rows>& rhs) -> bool {
            constexpr auto positive_zero = Constants<ElementType>::PositiveZero;

            return matrix::Compare(lhs, rhs, positive_zero);
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Equal(const Matrix<ElementType, Rows, Columns>& lhs, const Matrix<ElementType, Columns, Rows>& rhs, ElementType epsilon)
          -> bool {
            return matrix::Compare(lhs, rhs, epsilon) == true;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Equal(const Matrix<ElementType, Rows, Columns>& lhs, const Matrix<ElementType, Columns, Rows>& rhs) -> bool {
            return matrix::Compare(lhs, rhs) == true;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto NotEqual(const Matrix<ElementType, Rows, Columns>& lhs,
                             const Matrix<ElementType, Columns, Rows>& rhs,
                             ElementType                               epsilon) -> bool {
            return matrix::Compare(lhs, rhs, epsilon) == false;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto NotEqual(const Matrix<ElementType, Rows, Columns>& lhs, const Matrix<ElementType, Columns, Rows>& rhs) -> bool {
            return matrix::Compare(lhs, rhs) == false;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsZero(const Matrix<ElementType, Rows, Columns>& value, ElementType epsilon) -> bool {
            // TODO(wpieterse): Simplify this.

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    auto inner_value    = matrix::Read(value, row, column);
                    auto absolute_value = special::Absolute(inner_value);

                    if (utilities::GreaterThan(absolute_value, epsilon) == true) {
                        return false;
                    }
                }
            }

            return true;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsZero(const Matrix<ElementType, Rows, Columns>& value) -> bool {
            constexpr auto positive_zero = Constants<ElementType>::PositiveZero;

            return matrix::IsZero(value, positive_zero);
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsDiagonal(const Matrix<ElementType, Rows, Columns>& value, ElementType epsilon) -> bool {
            // TODO(wpieterse): Simplify this.

            static_assert(Rows == Columns);

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    if (utilities::NotEqual(row, column) == true) {
                        auto inner_value    = matrix::Read(value, row, column);
                        auto absolute_value = special::Absolute(inner_value);

                        if (utilities::GreaterThan(absolute_value, epsilon) == true) {
                            return false;
                        }
                    }
                }
            }

            return true;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsDiagonal(const Matrix<ElementType, Rows, Columns>& value) -> bool {
            constexpr auto positive_zero = Constants<ElementType>::PositiveZero;

            return matrix::IsDiagonal(value, positive_zero);
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsIdentity(const Matrix<ElementType, Rows, Columns>& value, ElementType epsilon) -> bool {
            constexpr auto positive_zero = Constants<ElementType>::PositiveZero;
            constexpr auto positive_one  = Constants<ElementType>::PositiveOne;

            static_assert(Rows == Columns);

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    auto lhs_value = matrix::Read(value, row, column);
                    auto rhs_value = positive_zero;

                    if (utilities::Equal(row, column) == true) {
                        rhs_value = positive_one;
                    }

                    if (utilities::Compare(lhs_value, rhs_value, epsilon) == false) {
                        return false;
                    }
                }
            }

            return true;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsIdentity(const Matrix<ElementType, Rows, Columns>& value) -> bool {
            constexpr auto positive_zero = Constants<ElementType>::PositiveZero;

            return matrix::IsIdentity(value, positive_zero);
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsTriDiagonal(const Matrix<ElementType, Rows, Columns>& value, ElementType epsilon) -> bool {
            // TODO(wpieterse): Simplify this.

            constexpr auto RowsMinusTwo = Rows - 2;

            static_assert(Rows == Columns);

            for (auto row = size_t {0}; row < RowsMinusTwo; row++) {
                auto initial_column = row + 2;

                for (auto column = initial_column; column < Columns; column++) {
                    auto left_value          = matrix::Read(value, row, column);
                    auto absolute_left_value = special::Absolute(left_value);

                    if (utilities::GreaterThan(absolute_left_value, epsilon) == true) {
                        return false;
                    }

                    auto right_value          = matrix::Read(value, column, row);
                    auto absolute_right_value = special::Absolute(right_value);

                    if (utilities::GreaterThan(absolute_right_value, epsilon) == true) {
                        return false;
                    }
                }
            }

            return true;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsTriDiagonal(const Matrix<ElementType, Rows, Columns>& value) -> bool {
            constexpr auto positive_zero = Constants<ElementType>::PositiveZero;

            return matrix::IsTriDiagonal(value, positive_zero);
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsSymmetric(const Matrix<ElementType, Rows, Columns>& value, ElementType epsilon) -> bool {
            constexpr auto RowsMinusTwo = Rows - 2;

            static_assert(Rows == Columns);

            for (auto row = size_t {0}; row < RowsMinusTwo; row++) {
                auto initial_column = row + 2;

                for (auto column = initial_column; column < Columns; column++) {
                    auto left_value  = matrix::Read(value, row, column);
                    auto right_value = matrix::Read(value, column, row);

                    if (utilities::Compare(left_value, right_value, epsilon) == false) {
                        return false;
                    }
                }
            }

            return true;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsSymmetric(const Matrix<ElementType, Rows, Columns>& value) -> bool {
            constexpr auto positive_zero = Constants<ElementType>::PositiveZero;

            return matrix::IsSymmetric(value, positive_zero);
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto RowToVector(const Matrix<ElementType, Rows, Columns>& value, size_t row) -> Vector<ElementType, Columns> {
            auto result = Vector<ElementType, Columns> {};

            // TODO(wpieterse): Implement me!

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto ColumnToVector(const Matrix<ElementType, Rows, Columns>& value, size_t column) -> Vector<ElementType, Rows> {
            auto result = Vector<ElementType, Rows> {};

            // TODO(wpieterse): Implement me!

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Multiply(const Matrix<ElementType, Rows, Columns>& lhs, const Vector<ElementType, Columns>& rhs)
          -> Vector<ElementType, Columns> {
            auto result = Vector<ElementType, Columns> {};

            int                i, j;
            const ElementType *mPtr, *vPtr;
            ElementType*       dstPtr;

            mPtr   = &lhs.elements[0][0];
            vPtr   = &rhs.elements[0];
            dstPtr = &result.elements[0];
            for (i = 0; i < Rows; i++) {
                ElementType sum = mPtr[0] * vPtr[0];
                for (j = 1; j < Columns; j++) {
                    sum += mPtr[j] * vPtr[j];
                }
                dstPtr[i] = sum;
                mPtr += Columns;
            }

            return result;
        }

        namespace transform {
            template <typename ElementType>
            inline auto Identity() -> TransformMatrix<ElementType> {
                return matrix::Identity<ElementType, TransformMatrixRows, TransformMatrixColumns>();
            }

            template <typename ElementType>
            inline auto TranslateOnX(const TransformMatrix<ElementType>& value, ElementType offset) -> TransformMatrix<ElementType> {
                auto result = matrix::transform::Identity<ElementType>();

                matrix::Write(result, 0, 3, offset);

                return matrix::Multiply(value, result);
            }

            template <typename ElementType>
            inline auto TranslateOnY(const TransformMatrix<ElementType>& value, ElementType offset) -> TransformMatrix<ElementType> {
                auto result = matrix::transform::Identity<ElementType>();

                matrix::Write(result, 1, 3, offset);

                return matrix::Multiply(value, result);
            }

            template <typename ElementType>
            inline auto TranslateOnZ(const TransformMatrix<ElementType>& value, ElementType offset) -> TransformMatrix<ElementType> {
                auto result = matrix::transform::Identity<ElementType>();

                matrix::Write(result, 2, 3, offset);

                return matrix::Multiply(value, result);
            }

            template <typename ElementType>
            inline auto TranslateUniformly(const TransformMatrix<ElementType>& value, ElementType offset) -> TransformMatrix<ElementType> {
                auto result = matrix::transform::Identity<ElementType>();

                matrix::Write(result, 0, 3, offset);
                matrix::Write(result, 1, 3, offset);
                matrix::Write(result, 2, 3, offset);

                return matrix::Multiply(value, result);
            }

            template <typename ElementType>
            inline auto
            TranslateArbitrary(const TransformMatrix<ElementType>& value, ElementType x_offset, ElementType y_offset, ElementType z_offset)
              -> TransformMatrix<ElementType> {
                auto result = matrix::transform::Identity<ElementType>();

                matrix::Write(result, 0, 3, x_offset);
                matrix::Write(result, 1, 3, y_offset);
                matrix::Write(result, 2, 3, z_offset);

                return matrix::Multiply(value, result);
            }

            template <typename ElementType>
            inline auto ScaleOnX(const TransformMatrix<ElementType>& value, ElementType scale) -> TransformMatrix<ElementType> {
                auto result = matrix::transform::Identity<ElementType>();

                matrix::Write(result, 0, 0, scale);

                return matrix::Multiply(value, result);
            }

            template <typename ElementType>
            inline auto ScaleOnY(const TransformMatrix<ElementType>& value, ElementType scale) -> TransformMatrix<ElementType> {
                auto result = matrix::transform::Identity<ElementType>();

                matrix::Write(result, 1, 1, scale);

                return matrix::Multiply(value, result);
            }

            template <typename ElementType>
            inline auto ScaleOnZ(const TransformMatrix<ElementType>& value, ElementType scale) -> TransformMatrix<ElementType> {
                auto result = matrix::transform::Identity<ElementType>();

                matrix::Write(result, 2, 2, scale);

                return matrix::Multiply(value, result);
            }

            template <typename ElementType>
            inline auto ScaleUniformly(const TransformMatrix<ElementType>& value, ElementType scale) -> TransformMatrix<ElementType> {
                auto result = matrix::transform::Identity<ElementType>();

                matrix::Write(result, 0, 0, scale);
                matrix::Write(result, 1, 1, scale);
                matrix::Write(result, 2, 2, scale);

                return matrix::Multiply(value, result);
            }

            template <typename ElementType>
            inline auto
            ScaleArbitrary(const TransformMatrix<ElementType>& value, ElementType x_scale, ElementType y_scale, ElementType z_scale)
              -> TransformMatrix<ElementType> {
                auto result = matrix::transform::Identity<ElementType>();

                matrix::Write(result, 0, 0, x_scale);
                matrix::Write(result, 1, 1, y_scale);
                matrix::Write(result, 2, 2, z_scale);

                return matrix::Multiply(value, result);
            }

            namespace rotate_radians {
                template <typename ElementType>
                inline auto AroundX(const TransformMatrix<ElementType>& value, ElementType radians) -> TransformMatrix<ElementType> {
                    auto result       = matrix::transform::Identity<ElementType>();
                    auto sine         = trigonometry::radian::Sine(radians);
                    auto cosine       = trigonometry::radian::Cosine(radians);
                    auto inverse_sine = arithmetic::Negate(sine);

                    matrix::Write(result, 1, 1, cosine);
                    matrix::Write(result, 1, 2, inverse_sine);
                    matrix::Write(result, 2, 1, sine);
                    matrix::Write(result, 2, 2, cosine);

                    return matrix::Multiply(value, result);
                }

                template <typename ElementType>
                inline auto AroundY(const TransformMatrix<ElementType>& value, ElementType radians) -> TransformMatrix<ElementType> {
                    auto result       = matrix::transform::Identity<ElementType>();
                    auto sine         = trigonometry::radian::Sine(radians);
                    auto cosine       = trigonometry::radian::Cosine(radians);
                    auto inverse_sine = arithmetic::Negate(sine);

                    matrix::Write(result, 0, 0, cosine);
                    matrix::Write(result, 0, 2, sine);
                    matrix::Write(result, 2, 0, inverse_sine);
                    matrix::Write(result, 2, 2, cosine);

                    return matrix::Multiply(value, result);
                }

                template <typename ElementType>
                inline auto AroundZ(const TransformMatrix<ElementType>& value, ElementType radians) -> TransformMatrix<ElementType> {
                    auto result       = matrix::transform::Identity<ElementType>();
                    auto sine         = trigonometry::radian::Sine(radians);
                    auto cosine       = trigonometry::radian::Cosine(radians);
                    auto inverse_sine = arithmetic::Negate(sine);

                    matrix::Write(result, 0, 0, cosine);
                    matrix::Write(result, 0, 1, inverse_sine);
                    matrix::Write(result, 1, 0, sine);
                    matrix::Write(result, 1, 1, cosine);

                    return matrix::Multiply(value, result);
                }
            } // namespace rotate_radians

            namespace rotate_degrees {
                template <typename ElementType>
                inline auto AroundX(const TransformMatrix<ElementType>& value, ElementType degrees) -> TransformMatrix<ElementType> {
                    auto radians = trigonometry::DegreeToRadian(degrees);

                    return matrix::transform::rotate_radians::AroundX(value, radians);
                }

                template <typename ElementType>
                inline auto AroundY(const TransformMatrix<ElementType>& value, ElementType degrees) -> TransformMatrix<ElementType> {
                    auto radians = trigonometry::DegreeToRadian(degrees);

                    return matrix::transform::rotate_radians::AroundY(value, radians);
                }

                template <typename ElementType>
                inline auto AroundZ(const TransformMatrix<ElementType>& value, ElementType degrees) -> TransformMatrix<ElementType> {
                    auto radians = trigonometry::DegreeToRadian(degrees);

                    return matrix::transform::rotate_radians::AroundZ(value, radians);
                }
            } // namespace rotate_degrees
        }     // namespace transform

        namespace projection {
            template <typename ElementType>
            inline auto Identity() -> ProjectionMatrix<ElementType> {
                return matrix::Identity<ElementType, ProjectionMatrixRows, ProjectionMatrixColumns>();
            }

            namespace orthographic {
                namespace detail {
                    template <typename ElementType>
                    inline auto CenterAboutOrigin(const ProjectionMatrix<ElementType>& value,
                                                  ElementType                          left,
                                                  ElementType                          right,
                                                  ElementType                          top,
                                                  ElementType                          bottom,
                                                  ElementType                          near,
                                                  ElementType                          far) -> ProjectionMatrix<ElementType> {
                        constexpr auto positive_two = Constants<ElementType>::PositiveTwo;
                        auto           result       = matrix::projection::Identity<ElementType>();

                        auto middle_x_sum     = left + right;
                        auto middle_x_half    = middle_x_sum / positive_two;
                        auto middle_x_negated = -middle_x_half;

                        auto middle_y_sum     = bottom + top;
                        auto middle_y_half    = middle_y_sum / positive_two;
                        auto middle_y_negated = -middle_y_half;

                        auto near_negated = -near;
                        auto far_negated  = -far;

                        auto middle_z_sum     = near_negated + far_negated;
                        auto middle_z_half    = middle_z_sum / positive_two;
                        auto middle_z_negated = -middle_z_half;

                        result.elements[0][3] = middle_x_negated;
                        result.elements[1][3] = middle_y_negated;
                        result.elements[2][3] = middle_z_negated;

                        return matrix::Multiply(value, result);
                    }

                    template <typename ElementType>
                    inline auto ScaleView(const ProjectionMatrix<ElementType>& value,
                                          ElementType                          left,
                                          ElementType                          right,
                                          ElementType                          top,
                                          ElementType                          bottom,
                                          ElementType                          near,
                                          ElementType                          far) -> ProjectionMatrix<ElementType> {
                        constexpr auto positive_two = Constants<ElementType>::PositiveTwo;
                        auto           result       = matrix::projection::Identity<ElementType>();

                        auto scale_x_middle = right - left;
                        auto scale_x_half   = positive_two / scale_x_middle;

                        auto scale_y_middle = top - bottom;
                        auto scale_y_half   = positive_two / scale_y_middle;

                        auto scale_z_middle = far - near;
                        auto scale_z_half   = positive_two / scale_z_middle;

                        result.elements[0][0] = scale_x_half;
                        result.elements[1][1] = scale_y_half;
                        result.elements[2][2] = scale_z_half;

                        return matrix::Multiply(value, result);
                    }
                } // namespace detail

                template <typename ElementType>
                inline auto CreateExpanded(const ProjectionMatrix<ElementType>& value,
                                           ElementType                          left,
                                           ElementType                          right,
                                           ElementType                          top,
                                           ElementType                          bottom,
                                           ElementType                          near,
                                           ElementType                          far) -> ProjectionMatrix<ElementType> {
                    auto result = matrix::projection::Identity<ElementType>();

                    result = matrix::projection::orthographic::detail::CenterAboutOrigin(result, left, right, top, bottom, near, far);
                    result = matrix::projection::orthographic::detail::ScaleView(result, left, right, top, bottom, near, far);

                    return matrix::Multiply(value, result);
                }

                template <typename ElementType>
                inline auto CreateCompacted(const ProjectionMatrix<ElementType>& value,
                                            ElementType                          left,
                                            ElementType                          right,
                                            ElementType                          top,
                                            ElementType                          bottom,
                                            ElementType                          near,
                                            ElementType                          far) -> ProjectionMatrix<ElementType> {
                    constexpr auto positive_two = Constants<ElementType>::PositiveTwo;
                    auto           result       = matrix::projection::Identity<ElementType>();

                    auto middle_x_plus         = right + left;
                    auto middle_x_plus_negated = -middle_x_plus;
                    auto middle_x_minus        = right - left;
                    auto middle_x_half         = positive_two / middle_x_minus;
                    auto middle_x_divide       = middle_x_plus_negated / middle_x_minus;

                    auto middle_y_plus         = top + bottom;
                    auto middle_y_plus_negated = -middle_y_plus;
                    auto middle_y_minus        = top - bottom;
                    auto middle_y_half         = positive_two / middle_y_minus;
                    auto middle_y_divide       = middle_y_plus_negated / middle_y_minus;

                    auto middle_z_plus         = far + near;
                    auto middle_z_plus_negated = -middle_z_plus;
                    auto middle_z_minus        = far - near;
                    auto middle_z_half         = positive_two / middle_z_minus;
                    auto middle_z_divide       = middle_z_plus_negated / middle_z_minus;

                    result.elements[0][0] = middle_x_half;
                    result.elements[1][1] = middle_y_half;
                    result.elements[2][2] = middle_z_half;

                    result.elements[0][3] = middle_x_divide;
                    result.elements[1][3] = middle_y_divide;
                    result.elements[2][3] = middle_z_divide;

                    return matrix::Multiply(value, result);
                }
            } // namespace orthographic
        }     // namespace projection

        namespace view {
            template <typename ElementType>
            inline auto Identity() -> ViewMatrix<ElementType> {
                return matrix::Identity<ElementType, ViewMatrixRows, ViewMatrixColumns>();
            }

            namespace detail {
                template <typename ElementType>
                auto ScaleToWindow(const ViewMatrix<ElementType>& value, ElementType width, ElementType height) -> ViewMatrix<ElementType> {
                    constexpr auto positive_two = Constants<ElementType>::PositiveTwo;
                    auto           result       = matrix::view::Identity<ElementType>();

                    auto half_width  = width / positive_two;
                    auto half_height = height / positive_two;

                    result.elements[0][0] = half_width;
                    result.elements[1][1] = half_height;

                    return matrix::Multiply(value, result);
                }

                template <typename ElementType>
                auto OffsetExtent(const ViewMatrix<ElementType>& value, ElementType width, ElementType height) -> ViewMatrix<ElementType> {
                    constexpr auto positive_two = Constants<ElementType>::PositiveTwo;
                    auto           result       = matrix::view::Identity<ElementType>();

                    auto half_width  = width / positive_two;
                    auto half_height = height / positive_two;

                    result.elements[0][3] = half_width;
                    result.elements[1][3] = half_height;

                    return matrix::Multiply(value, result);
                }

                template <typename ElementType>
                auto OffsetOrigin(const ViewMatrix<ElementType>& value, ElementType x, ElementType y) -> ViewMatrix<ElementType> {
                    auto result = matrix::view::Identity<ElementType>();

                    result.elements[0][3] = x;
                    result.elements[1][3] = y;

                    return matrix::Multiply(value, result);
                }
            } // namespace detail

            template <typename ElementType>
            auto Create(const ViewMatrix<ElementType>& value, ElementType x, ElementType y, ElementType width, ElementType height)
              -> ViewMatrix<ElementType> {
                auto result = matrix::view::Identity<ElementType>();

                result = matrix::view::detail::ScaleToWindow(result, width, height);
                result = matrix::view::detail::OffsetExtent(result, width, height);
                result = matrix::view::detail::OffsetOrigin(result, x, y);

                return matrix::Multiply(value, result);
            }
        } // namespace view

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Print(const Matrix<ElementType, Rows, Columns>& value) -> void {
            constexpr auto columns_minus_one = Columns - 1;

            for (auto row = size_t {0}; row < Rows; row++) {
                std::cout << "| ";

                for (auto column = size_t {0}; column < Columns; column++) {
                    auto inner_value = matrix::Read(value, row, column);

                    std::cout << inner_value;
                    if (utilities::LessThan(column, columns_minus_one) == true) {
                        std::cout << ", ";
                    }
                }

                std::cout << " |";
                std::cout << std::endl;
            }
        }
    } // namespace matrix
} // namespace math

int main() {
    auto model = math::matrix::transform::Identity<float>();

    model = math::matrix::transform::rotate_degrees::AroundX(model, 0.0f);
    model = math::matrix::transform::rotate_degrees::AroundY(model, 0.0f);
    model = math::matrix::transform::rotate_degrees::AroundZ(model, 0.0f);
    model = math::matrix::transform::ScaleOnX(model, 1.0f);
    model = math::matrix::transform::ScaleOnY(model, 1.0f);
    model = math::matrix::transform::ScaleOnZ(model, 1.0f);
    model = math::matrix::transform::TranslateOnX(model, 0.0f);
    model = math::matrix::transform::TranslateOnY(model, 0.0f);
    model = math::matrix::transform::TranslateOnZ(model, 0.0f);

    math::matrix::Print(model);
    std::cout << std::endl;

    auto view = math::matrix::view::Identity<float>();

    view = math::matrix::view::Create(view, 0.0f, 0.0f, 640.0f, 480.0f);

    math::matrix::Print(view);
    std::cout << std::endl;

    auto projection = math::matrix::projection::Identity<float>();

    projection = math::matrix::projection::orthographic::CreateExpanded(projection, -5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f);

    math::matrix::Print(projection);
    std::cout << std::endl;

    auto mvp = math::matrix::Identity<float, 4, 4>();

    mvp = math::matrix::Multiply(mvp, model);
    mvp = math::matrix::Multiply(mvp, view);
    mvp = math::matrix::Multiply(mvp, projection);

    math::matrix::Print(mvp);
    std::cout << std::endl;

    auto v1 = math::vector::Zero<float, 4>();

    v1.elements[0] = 1.0f;
    v1.elements[1] = 0.0f;
    v1.elements[2] = 0.0f;
    v1.elements[3] = 1.0f;

    v1 = math::matrix::Multiply(mvp, v1);

    math::vector::Print(v1);
    std::cout << std::endl;

    return 0;
}
