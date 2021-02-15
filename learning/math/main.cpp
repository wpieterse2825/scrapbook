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
concept HasAssign = requires(LHSType lhs, RHSType rhs) {
    lhs = rhs;
};

template <typename Type>
concept HasAffirm = requires(Type value) {
    +value;
};

template <typename Type>
concept HasNegate = requires(Type value) {
    -value;
};

template <typename LHSType, typename RHSType>
concept HasPlus = requires(LHSType lhs, RHSType rhs) {
    lhs + rhs;
};

template <typename LHSType, typename RHSType>
concept HasMinus = requires(LHSType lhs, RHSType rhs) {
    lhs - rhs;
};

template <typename LHSType, typename RHSType>
concept HasMultiply = requires(LHSType lhs, RHSType rhs) {
    lhs* rhs;
};

template <typename LHSType, typename RHSType>
concept HasDivide = requires(LHSType lhs, RHSType rhs) {
    lhs / rhs;
};

template <typename LHSType, typename RHSType>
concept HasLessThen = requires(LHSType lhs, RHSType rhs) {
    lhs < rhs;
};

template <typename LHSType, typename RHSType>
concept HasLessThenOrEqual = requires(LHSType lhs, RHSType rhs) {
    lhs <= rhs;
};

template <typename LHSType, typename RHSType>
concept HasGreaterThan = requires(LHSType lhs, RHSType rhs) {
    lhs > rhs;
};

template <typename LHSType, typename RHSType>
concept HasGreaterThanOrEqual = requires(LHSType lhs, RHSType rhs) {
    lhs >= rhs;
};

template <typename LHSType, typename RHSType>
concept HasEqual = requires(LHSType lhs, RHSType rhs) {
    lhs == rhs;
};

namespace math {
    namespace arithmetic {
        template <Integral Type>
        requires HasAffirm<Type> constexpr auto Affirm(Type value) {
            return +value;
        }

        template <Integral Type>
        requires HasNegate<Type> constexpr auto Negate(Type value) {
            return -value;
        }

        template <Integral LHSType, Integral RHSType>
        requires HasPlus<LHSType, RHSType> constexpr auto Plus(LHSType lhs, RHSType rhs) -> LHSType {
            return lhs + rhs;
        }

        template <Integral LHSType, Integral RHSType>
        requires HasMinus<LHSType, RHSType> constexpr auto Minus(LHSType lhs, RHSType rhs) -> LHSType {
            return lhs - rhs;
        }

        template <Integral LHSType, Integral RHSType>
        requires HasMultiply<LHSType, RHSType> constexpr auto Multiply(LHSType lhs, RHSType rhs) -> LHSType {
            return lhs * rhs;
        }

        template <Integral LHSType, Integral RHSType>
        requires HasDivide<LHSType, RHSType> constexpr auto Divide(LHSType lhs, RHSType rhs) -> LHSType {
            return lhs / rhs;
        }
    } // namespace arithmetic

    namespace constants {
        template <Integral Type>
        constexpr auto ZeroNeutral() -> Type {
            return Type {0};
        }

        template <Decimal Type>
        constexpr auto OneHalfNeutral() -> Type {
            return Type {0.5};
        }

        template <Integral Type>
        constexpr auto OneNeutral() -> Type {
            return Type {1};
        }

        template <Decimal Type>
        constexpr auto TwoHalfNeutral() -> Type {
            return Type {1.5};
        }

        template <Integral Type>
        constexpr auto TwoNeutral() -> Type {
            return Type {2};
        }

        template <Integral Type>
        constexpr auto ThreeNeutral() -> Type {
            return Type {3};
        }

        template <Integral Type>
        constexpr auto FourNeutral() -> Type {
            return Type {4};
        }

        template <typename Type>
        constexpr auto ZeroPositive() -> Type {
            constexpr auto zero_positive = math::constants::ZeroNeutral<Type>();

            return math::arithmetic::Affirm(zero_positive);
        }

        template <typename Type>
        constexpr auto OneHalfPositive() -> Type {
            constexpr auto half_one = math::constants::OneHalfNeutral<Type>();

            return math::arithmetic::Affirm(half_one);
        }

        template <typename Type>
        constexpr auto OnePositive() -> Type {
            constexpr auto one_positive = math::constants::OneNeutral<Type>();

            return math::arithmetic::Affirm(one_positive);
        }

        template <typename Type>
        constexpr auto TwoHalvePositive() -> Type {
            constexpr auto half_two = math::constants::TwoHalfNeutral<Type>();

            return math::arithmetic::Affirm(half_two);
        }

        template <typename Type>
        constexpr auto TwoPositive() -> Type {
            constexpr auto two = math::constants::TwoNeutral<Type>();

            return math::arithmetic::Affirm(two);
        }

        template <typename Type>
        constexpr auto ThreePositive() -> Type {
            constexpr auto three = math::constants::ThreeNeutral<Type>();

            return math::arithmetic::Affirm(three);
        }

        template <typename Type>
        constexpr auto FourPositive() -> Type {
            constexpr auto four = math::constants::FourNeutral<Type>();

            return math::arithmetic::Affirm(four);
        }

        template <typename Type>
        constexpr auto ZeroNegative() -> Type {
            constexpr auto zero_positive = math::constants::ZeroNeutral<Type>();

            return math::arithmetic::Negate(zero_positive);
        }

        template <typename Type>
        constexpr auto OneHalfNegative() -> Type {
            constexpr auto half_one = math::constants::OneHalfNeutral<Type>();

            return math::arithmetic::Negate(half_one);
        }

        template <typename Type>
        constexpr auto OneNegative() -> Type {
            constexpr auto one_positive = math::constants::OneNeutral<Type>();

            return math::arithmetic::Negate(one_positive);
        }

        template <typename Type>
        constexpr auto TwoHalveNegative() -> Type {
            constexpr auto half_two = math::constants::TwoHalfNeutral<Type>();

            return math::arithmetic::Negate(half_two);
        }

        template <typename Type>
        constexpr auto TwoNegative() -> Type {
            constexpr auto two = math::constants::TwoNeutral<Type>();

            return math::arithmetic::Negate(two);
        }

        template <typename Type>
        constexpr auto ThreeNegative() -> Type {
            constexpr auto three = math::constants::ThreeNeutral<Type>();

            return math::arithmetic::Negate(three);
        }

        template <typename Type>
        constexpr auto FourNegative() -> Type {
            constexpr auto four = math::constants::FourNeutral<Type>();

            return math::arithmetic::Negate(four);
        }
    } // namespace constants

    namespace special {
        template <Decimal ElementType>
        inline auto Floor(ElementType value) -> ElementType {
            constexpr auto is_float       = std::is_same_v<ElementType, float>;
            constexpr auto is_double      = std::is_same_v<ElementType, double>;
            constexpr auto is_long_double = std::is_same_v<ElementType, long double>;
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

        template <Decimal ElementType>
        inline auto Ceiling(ElementType value) -> ElementType {
            constexpr auto is_float       = std::is_same_v<ElementType, float>;
            constexpr auto is_double      = std::is_same_v<ElementType, double>;
            constexpr auto is_long_double = std::is_same_v<ElementType, long double>;
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

        template <Integral ElementType>
        inline auto Absolute(ElementType value) -> ElementType {
            constexpr auto is_float        = std::is_same_v<ElementType, float>;
            constexpr auto is_double       = std::is_same_v<ElementType, double>;
            constexpr auto is_long_double  = std::is_same_v<ElementType, long double>;
            constexpr auto is_long_integer = std::is_same_v<ElementType, long>;
            constexpr auto is_correct      = is_float | is_double | is_long_double | is_long_integer;

            static_assert(is_correct == true);

            if constexpr (is_float == true) {
                return ::fabsf(value);
            }

            if constexpr (is_double == true) {
                return ::fabs(value);
            }

            if constexpr (is_long_double == true) {
                return ::fabsl(value);
            }

            if constexpr (is_long_integer == true) {
                return ::abs(value);
            }
        }
    } // namespace special

    namespace utilities {
        // TODO(wpieterse): Plus epsilon calls for the below functions.
        template <Integral LHSType, Integral RHSType>
        requires HasLessThen<LHSType, RHSType> inline auto LessThan(LHSType lhs, RHSType rhs) -> bool {
            return lhs < rhs;
        }

        template <Integral LHSType, Integral RHSType>
        requires HasLessThenOrEqual<LHSType, RHSType> inline auto LessThanOrEqual(LHSType lhs, RHSType rhs) -> bool {
            return lhs <= rhs;
        }

        template <Integral LHSType, Integral RHSType>
        requires HasGreaterThan<LHSType, RHSType> inline auto GreaterThan(LHSType lhs, RHSType rhs) -> bool {
            return lhs > rhs;
        }

        template <Integral LHSType, Integral RHSType>
        requires HasGreaterThanOrEqual<LHSType, RHSType> inline auto GreaterThanOrEqual(LHSType lhs, RHSType rhs) -> bool {
            return lhs >= rhs;
        }

        template <Decimal LHSType, Decimal RHSType, Decimal EpsilonType>
        inline auto Compare(LHSType lhs, RHSType rhs, EpsilonType epsilon) -> bool {
            const auto difference              = math::arithmetic::Minus(lhs, rhs);
            const auto absolute_difference     = math::special::Absolute(difference);
            const auto is_greater_than_epsilon = math::utilities::GreaterThan(absolute_difference, epsilon);

            if (is_greater_than_epsilon == true) {
                return false;
            }

            return true;
        }

        template <typename LHSType, typename RHSType, typename EpsilonType>
        inline auto Equal(LHSType lhs, RHSType rhs, EpsilonType epsilon) -> bool {
            const auto result = math::utilities::Compare(lhs, rhs, epsilon);

            return result == true;
        }

        template <typename LHSType, typename RHSType, typename EpsilonType>
        inline auto NotEqual(LHSType lhs, RHSType rhs, EpsilonType epsilon) -> bool {
            const auto result = math::utilities::Compare(lhs, rhs, epsilon);

            return result == false;
        }

        template <Integral LHSType, Integral RHSType>
        requires HasEqual<LHSType, RHSType> inline auto Compare(LHSType lhs, RHSType rhs) -> bool {
            return lhs == rhs;
        }

        template <typename LHSType, typename RHSType>
        inline auto Equal(LHSType lhs, RHSType rhs) -> bool {
            const auto result = math::utilities::Compare(lhs, rhs);

            return result == true;
        }

        template <typename LHSType, typename RHSType>
        inline auto NotEqual(LHSType lhs, RHSType rhs) -> bool {
            const auto result = math::utilities::Compare(lhs, rhs);

            return result == false;
        }
    } // namespace utilities

    namespace trigonometry {
        namespace constants {
            template <Decimal Type>
            constexpr auto PiNeutral() -> Type {
                return Type {M_PI};
            }

            template <typename Type>
            constexpr auto PiPositive() -> Type {
                constexpr auto pi = math::trigonometry::constants::PiNeutral<Type>();

                return math::arithmetic::Affirm(pi);
            }

            template <typename Type>
            constexpr auto PiNegative() -> Type {
                constexpr auto pi = math::trigonometry::constants::PiNeutral<Type>();

                return math::arithmetic::Negate(pi);
            }

            template <Integral Type>
            constexpr auto DegreesOneQuarterNeutral() -> Type {
                return Type {90};
            }

            template <Integral Type>
            constexpr auto DegreesOneQuarterPositive() -> Type {
                const auto one_quarter = math::trigonometry::constants::DegreesOneQuarterNeutral<Type>();

                return math::arithmetic::Affirm(one_quarter);
            }

            template <Integral Type>
            constexpr auto DegreesOneQuarterNegative() -> Type {
                const auto one_quarter = math::trigonometry::constants::DegreesOneQuarterNeutral<Type>();

                return math::arithmetic::Negate(one_quarter);
            }

            template <Integral Type>
            constexpr auto DegreesTwoQuartersNeutral() -> Type {
                constexpr auto one_quarter = math::trigonometry::constants::DegreesOneQuarterPositive<Type>();
                constexpr auto two         = math::constants::TwoPositive<Type>();

                return math::arithmetic::Multiply(one_quarter, two);
            }

            template <Integral Type>
            constexpr auto DegreesThreeQuartersNeutral() -> Type {
                constexpr auto one_quarter = math::trigonometry::constants::DegreesOneQuarterPositive<Type>();
                constexpr auto three       = math::constants::ThreePositive<Type>();

                return math::arithmetic::Multiply(one_quarter, three);
            }

            template <Integral Type>
            constexpr auto DegreesFourQuartersNeutral() -> Type {
                constexpr auto one_quarter = math::trigonometry::constants::DegreesOneQuarterPositive<Type>();
                constexpr auto four        = math::constants::FourPositive<Type>();

                return math::arithmetic::Multiply(one_quarter, four);
            }

            template <Integral Type>
            constexpr auto DegreesTwoQuartersPositive() -> Type {
                constexpr auto two_quarters = math::trigonometry::constants::DegreesTwoQuartersNeutral<Type>();

                return math::arithmetic::Affirm(two_quarters);
            }

            template <Integral Type>
            constexpr auto DegreesThreeQuartersPositive() -> Type {
                constexpr auto three_quarters = math::trigonometry::constants::DegreesThreeQuartersNeutral<Type>();

                return math::arithmetic::Affirm(three_quarters);
            }

            template <Integral Type>
            constexpr auto DegreesFourQuartersPositive() -> Type {
                constexpr auto four_quarters = math::trigonometry::constants::DegreesFourQuartersNeutral<Type>();

                return math::arithmetic::Affirm(four_quarters);
            }

            template <Integral Type>
            constexpr auto DegreesTwoQuartersNegative() -> Type {
                constexpr auto two_quarters = math::trigonometry::constants::DegreesTwoQuartersNeutral<Type>();

                return math::arithmetic::Negate(two_quarters);
            }

            template <Integral Type>
            constexpr auto DegreesThreeQuartersNegative() -> Type {
                constexpr auto three_quarters = math::trigonometry::constants::DegreesThreeQuartersNeutral<Type>();

                return math::arithmetic::Negate(three_quarters);
            }

            template <Integral Type>
            constexpr auto DegreesFourQuartersNegative() -> Type {
                constexpr auto four_quarters = math::trigonometry::constants::DegreesFourQuartersNeutral<Type>();

                return math::arithmetic::Negate(four_quarters);
            }

            template <Decimal Type>
            constexpr auto RadiansOneQuarterNeutral() -> Type {
                constexpr auto pi       = math::trigonometry::constants::PiPositive<Type>();
                constexpr auto half_one = math::constants::OneHalfPositive<Type>();

                return math::arithmetic::Multiply(pi, half_one);
            }

            template <Decimal Type>
            constexpr auto RadiansOneQuarterPositive() -> Type {
                constexpr auto one_quarter = math::trigonometry::constants::RadiansOneQuarterNeutral<Type>();

                return math::arithmetic::Affirm(one_quarter);
            }

            template <Decimal Type>
            constexpr auto RadiansOneQuarterNegative() -> Type {
                constexpr auto one_quarter = math::trigonometry::constants::RadiansOneQuarterNeutral<Type>();

                return math::arithmetic::Negate(one_quarter);
            }

            template <Decimal Type>
            constexpr auto RadiansTwoQuartersNeutral() -> Type {
                constexpr auto one_quarter = math::trigonometry::constants::RadiansOneQuarterPositive<Type>();
                constexpr auto two         = math::constants::TwoPositive<Type>();

                return math::arithmetic::Multiply(one_quarter, two);
            }

            template <Decimal Type>
            constexpr auto RadiansThreeQuartersNeutral() -> Type {
                constexpr auto one_quarter = math::trigonometry::constants::RadiansOneQuarterPositive<Type>();
                constexpr auto three       = math::constants::ThreePositive<Type>();

                return math::arithmetic::Multiply(one_quarter, three);
            }

            template <Decimal Type>
            constexpr auto RadiansFourQuartersNeutral() -> Type {
                constexpr auto one_quarter = math::trigonometry::constants::RadiansOneQuarterPositive<Type>();
                constexpr auto four        = math::constants::FourPositive<Type>();

                return math::arithmetic::Multiply(one_quarter, four);
            }

            template <Decimal Type>
            constexpr auto RadiansTwoQuartersPositive() -> Type {
                constexpr auto two_quarters = math::trigonometry::constants::RadiansTwoQuartersNeutral<Type>();

                return math::arithmetic::Affirm(two_quarters);
            }

            template <Decimal Type>
            constexpr auto RadiansThreeQuartersPositive() -> Type {
                constexpr auto three_quarters = math::trigonometry::constants::RadiansThreeQuartersNeutral<Type>();

                return math::arithmetic::Affirm(three_quarters);
            }

            template <Decimal Type>
            constexpr auto RadiansFourQuartersPositive() -> Type {
                constexpr auto four_quarters = math::trigonometry::constants::RadiansFourQuartersNeutral<Type>();

                return math::arithmetic::Affirm(four_quarters);
            }

            template <Decimal Type>
            constexpr auto RadiansTwoQuartersNegative() -> Type {
                constexpr auto two_quarters = math::trigonometry::constants::RadiansTwoQuartersNeutral<Type>();

                return math::arithmetic::Negate(two_quarters);
            }

            template <Decimal Type>
            constexpr auto RadiansThreeQuartersNegative() -> Type {
                constexpr auto three_quarters = math::trigonometry::constants::RadiansThreeQuartersNeutral<Type>();

                return math::arithmetic::Negate(three_quarters);
            }

            template <Decimal Type>
            constexpr auto RadiansFourQuartersNegative() -> Type {
                constexpr auto four_quarters = math::trigonometry::constants::RadiansFourQuartersNeutral<Type>();

                return math::arithmetic::Negate(four_quarters);
            }
        } // namespace constants

        template <Decimal ElementType>
        inline auto DegreesToRadians(ElementType degrees) -> ElementType {
            constexpr auto pi                       = math::trigonometry::constants::PiPositive<ElementType>();
            constexpr auto degrees_two_quarters     = math::trigonometry::constants::DegreesTwoQuartersPositive<ElementType>();
            constexpr auto degrees_to_radians_scale = math::arithmetic::Divide(pi, degrees_two_quarters);

            return math::arithmetic::Multiply(degrees, degrees_to_radians_scale);
        }

        template <Decimal ElementType>
        inline auto RadiansToDegrees(ElementType radians) -> ElementType {
            constexpr auto degrees_two_quarters     = math::trigonometry::constants::DegreesTwoQuartersPositive<ElementType>();
            constexpr auto pi                       = math::trigonometry::constants::PiPositive<ElementType>();
            constexpr auto radians_to_degrees_scale = math::arithmetic::Divide(degrees_two_quarters, pi);

            return math::arithmetic::Multiply(radians, radians_to_degrees_scale);
        }

        namespace radians {
            template <Decimal ElementType>
            inline auto Sine(ElementType radians) -> ElementType {
                constexpr bool is_float       = std::is_same_v<ElementType, float>;
                constexpr bool is_double      = std::is_same_v<ElementType, double>;
                constexpr bool is_long_double = std::is_same_v<ElementType, long double>;
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

            template <Decimal ElementType>
            inline auto Cosine(ElementType radians) -> ElementType {
                constexpr bool is_float       = std::is_same_v<ElementType, float>;
                constexpr bool is_double      = std::is_same_v<ElementType, double>;
                constexpr bool is_long_double = std::is_same_v<ElementType, long double>;
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

            template <Decimal ElementType>
            inline auto Tangent(ElementType radians) -> ElementType {
                constexpr bool is_float       = std::is_same_v<ElementType, float>;
                constexpr bool is_double      = std::is_same_v<ElementType, double>;
                constexpr bool is_long_double = std::is_same_v<ElementType, long double>;
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
        } // namespace radians

        namespace degrees {
            template <Decimal ElementType>
            inline auto Sine(ElementType degrees) -> ElementType {
                const auto degrees_to_radians = math::trigonometry::DegreesToRadians(degrees);

                return math::trigonometry::radians::Sine(degrees_to_radians);
            }

            template <Decimal ElementType>
            inline auto Cosine(ElementType degrees) -> ElementType {
                const auto degrees_to_radians = math::trigonometry::DegreesToRadians(degrees);

                return math::trigonometry::radians::Cosine(degrees_to_radians);
            }

            template <Decimal ElementType>
            inline auto Tangent(ElementType degrees) -> ElementType {
                const auto degrees_to_radians = math::trigonometry::DegreesToRadians(degrees);

                return math::trigonometry::radians::Tangent(degrees_to_radians);
            }
        } // namespace degrees
    }     // namespace trigonometry

    template <typename ElementType, size_t Elements>
    concept SizedVector = requires(ElementType) {
        std::is_integral_v<ElementType>;
        Elements > 0;
    };

    template <typename ElementType, size_t Elements>
    requires math::SizedVector<ElementType, Elements> struct Vector {
        ElementType elements[Elements];
    };

    namespace vector {
        template <typename ElementType, size_t Elements>
        inline auto Read(const math::Vector<ElementType, Elements>& value, size_t index) -> ElementType {
            assert(index < Elements);

            return value.elements[index];
        }

        template <typename VectorType, typename ValueType, size_t Elements>
        requires HasAssign<VectorType, ValueType> inline auto
        Write(Vector<VectorType, Elements>& value, size_t index, ValueType inner_value) -> void {
            assert(index < Elements);

            value.elements[index] = inner_value;
        }

        template <typename ElementType, size_t Elements>
        inline auto CreateZero() -> math::Vector<ElementType, Elements> {
            constexpr auto zero_positive = math::constants::ZeroPositive<ElementType>();

            auto result = math::Vector<ElementType, Elements> {};

            for (auto index = size_t {0}; index < Elements; index++) {
                math::vector::Write(result, index, zero_positive);
            }

            return result;
        }

        template <typename VectorType, typename ValueType, size_t Elements>
        inline auto Set(ValueType value) -> math::Vector<VectorType, Elements> {
            auto result = math::Vector<VectorType, Elements> {};

            for (auto index = size_t {0}; index < Elements; index++) {
                math::vector::Write(result, index, value);
            }

            return result;
        }

        template <typename ElementType, size_t Elements>
        inline auto Print(const math::Vector<ElementType, Elements>& value) -> void {
            constexpr auto elements_minus_one = Elements - 1;

            std::cout << "[ ";

            for (auto index = size_t {0}; index < Elements; index++) {
                const auto can_write_comma = utilities::LessThan(index, elements_minus_one);
                const auto inner_value     = math::vector::Read(value, index);

                std::cout << inner_value;

                if (can_write_comma == true) {
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
    requires math::SizedMatrix<ElementType, Rows, Columns> struct Matrix {
        ElementType elements[Rows][Columns];
    };

    static constexpr auto CartesianMatrixRows    = size_t {4};
    static constexpr auto CartesianMatrixColumns = size_t {4};

    template <typename ElementType>
    using ModelMatrix = math::Matrix<ElementType, math::CartesianMatrixRows, math::CartesianMatrixColumns>;

    template <typename ElementType>
    using ViewMatrix = math::Matrix<ElementType, math::CartesianMatrixRows, math::CartesianMatrixColumns>;

    template <typename ElementType>
    using ProjectionMatrix = math::Matrix<ElementType, math::CartesianMatrixRows, math::CartesianMatrixColumns>;

    namespace matrix {
        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Read(const math::Matrix<ElementType, Rows, Columns>& value, size_t row, size_t column) -> ElementType {
            assert(row < Rows);
            assert(column < Columns);

            return value.elements[row][column];
        }

        template <typename MatrixType, typename ValueType, size_t Rows, size_t Columns>
        requires HasAssign<MatrixType, ValueType> inline auto
        Write(Matrix<MatrixType, Rows, Columns>& value, size_t row, size_t column, const ValueType& inner_value) -> void {
            assert(row < Rows);
            assert(column < Columns);

            value.elements[row][column] = inner_value;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto CreateZero() -> math::Matrix<ElementType, Rows, Columns> {
            constexpr auto zero_positive = math::constants::ZeroPositive<ElementType>();

            auto result = math::Matrix<ElementType, Rows, Columns> {};

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    math::matrix::Write(result, row, column, zero_positive);
                }
            }

            return result;
        }

        template <typename MatrixType, typename ValueType, size_t Rows, size_t Columns>
        inline auto CreateDiagonal(ValueType value) -> math::Matrix<MatrixType, Rows, Columns> {
            constexpr auto zero_positive = math::constants::ZeroPositive<MatrixType>();

            auto result = math::Matrix<MatrixType, Rows, Columns> {};

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    const auto is_diagonal = math::utilities::Equal(row, column);

                    if (is_diagonal == true) {
                        math::matrix::Write(result, row, column, value);
                    } else {
                        math::matrix::Write(result, row, column, zero_positive);
                    }
                }
            }

            return result;
        }

        template <typename ElementType, size_t Elements>
        inline auto CreateDiagonal(const math::Vector<ElementType, Elements>& value) -> math::Matrix<ElementType, Elements, Elements> {
            constexpr auto zero_positive = math::constants::ZeroPositive<ElementType>();

            auto result = math::Matrix<ElementType, Elements, Elements> {};

            for (auto row = size_t {0}; row < Elements; row++) {
                for (auto column = size_t {0}; column < Elements; column++) {
                    const auto is_diagonal = math::utilities::Equal(row, column);

                    if (is_diagonal == true) {
                        const auto inner_value = math::vector::Read(value, row);

                        math::matrix::Write(result, row, column, inner_value);
                    } else {
                        math::matrix::Write(result, row, column, zero_positive);
                    }
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto CreateIdentity() -> math::Matrix<ElementType, Rows, Columns> {
            constexpr auto one_positive = math::constants::OnePositive<ElementType>();

            return math::matrix::CreateDiagonal<ElementType, ElementType, Rows, Columns>(one_positive);
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Plus(const math::Matrix<ElementType, Rows, Columns>& lhs, const math::Matrix<ElementType, Rows, Columns>& rhs)
          -> math::Matrix<ElementType, Rows, Columns> {
            auto result = math::Matrix<ElementType, Rows, Columns> {};

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    const auto lhs_value = math::matrix::Read(lhs, row, column);
                    const auto rhs_value = math::matrix::Read(rhs, row, column);
                    const auto sum       = math::arithmetic::Plus(lhs_value, rhs_value);

                    math::matrix::Write(result, row, column, sum);
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Minus(const math::Matrix<ElementType, Rows, Columns>& lhs, const math::Matrix<ElementType, Rows, Columns>& rhs)
          -> math::Matrix<ElementType, Rows, Columns> {
            auto result = math::Matrix<ElementType, Rows, Columns> {};

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    const auto lhs_value = math::matrix::Read(lhs, row, column);
                    const auto rhs_value = math::matrix::Read(rhs, row, column);
                    const auto sum       = math::arithmetic::Minus(lhs_value, rhs_value);

                    math::matrix::Write(result, row, column, sum);
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Multiply(const math::Matrix<ElementType, Rows, Columns>& lhs, ElementType rhs)
          -> math::Matrix<ElementType, Rows, Columns> {
            auto result = math::Matrix<ElementType, Rows, Columns> {};

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    const auto lhs_value = math::matrix::Read(lhs, row, column);
                    const auto rhs_value = rhs;
                    const auto sum       = math::arithmetic::Multiply(lhs_value, rhs_value);

                    math::matrix::Write(result, row, column, sum);
                }
            }

            return result;
        }

        template <typename ElementType, size_t LHSRows, size_t LHSColumns, size_t RHSRows, size_t RHSColumns>
        inline auto Multiply(const math::Matrix<ElementType, LHSRows, LHSColumns>& lhs,
                             const math::Matrix<ElementType, RHSColumns, RHSRows>& rhs) -> math::Matrix<ElementType, LHSRows, RHSColumns> {
            constexpr auto zero_positive = math::constants::ZeroPositive<ElementType>();

            auto result = math::Matrix<ElementType, LHSRows, RHSColumns> {};

            static_assert(LHSRows == RHSColumns);

            for (auto lhs_rows = size_t {0}; lhs_rows < LHSRows; lhs_rows++) {
                for (auto rhs_columns = size_t {0}; rhs_columns < RHSColumns; rhs_columns++) {
                    math::matrix::Write(result, lhs_rows, rhs_columns, zero_positive);

                    for (auto rhs_rows = size_t {0}; rhs_rows < RHSRows; rhs_rows++) {
                        const auto current_value = math::matrix::Read(result, lhs_rows, rhs_columns);
                        const auto lhs_value     = math::matrix::Read(lhs, lhs_rows, rhs_rows);
                        const auto rhs_value     = math::matrix::Read(rhs, rhs_rows, rhs_columns);
                        const auto sum           = math::arithmetic::Multiply(lhs_value, rhs_value);
                        const auto result_value  = math::arithmetic::Plus(current_value, sum);

                        math::matrix::Write(result, lhs_rows, rhs_columns, result_value);
                    }
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Transpose(const math::Matrix<ElementType, Rows, Columns>& value) -> math::Matrix<ElementType, Columns, Rows> {
            auto result = math::Matrix<ElementType, Columns, Rows> {};

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    const auto inner_value = math::matrix::Read(value, row, column);

                    math::matrix::Write(result, column, row, inner_value);
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Inverse(const math::Matrix<ElementType, Rows, Columns>& value) -> math::Matrix<ElementType, Rows, Columns> {
            auto result = math::Matrix<ElementType, Rows, Columns> {};

            static_assert(Rows == Columns);

            // TODO(wpieterse): Implement me!

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Negate(const math::Matrix<ElementType, Rows, Columns>& value) -> math::Matrix<ElementType, Rows, Columns> {
            auto result = math::Matrix<ElementType, Rows, Columns> {};

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    const auto inner_value   = math::matrix::Read(value, row, column);
                    const auto negated_value = math::arithmetic::Negate(inner_value);

                    math::matrix::Write(result, row, column, negated_value);
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Clamp(const math::Matrix<ElementType, Rows, Columns>& value, ElementType minimum, ElementType maximum)
          -> math::Matrix<ElementType, Rows, Columns> {
            auto result = math::Matrix<ElementType, Rows, Columns> {};

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    const auto inner_value             = math::matrix::Read(value, row, column);
                    const auto is_less_than_minimum    = math::utilities::LessThan(inner_value, minimum);
                    const auto is_greater_than_maximum = math::utilities::GreaterThan(inner_value, maximum);

                    if (is_less_than_minimum == true) {
                        math::matrix::Write(result, row, column, minimum);
                    } else if (is_greater_than_maximum == true) {
                        math::matrix::Write(result, row, column, maximum);
                    } else {
                        math::matrix::Write(result, row, column, inner_value);
                    }
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto ClearLowerTriangle(const math::Matrix<ElementType, Rows, Columns>& value) -> math::Matrix<ElementType, Rows, Columns> {
            auto result = math::Matrix<ElementType, Rows, Columns> {};

            // TODO(wpieterse): Implement me!

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto ClearUpperTriangle(const math::Matrix<ElementType, Rows, Columns>& value) -> math::Matrix<ElementType, Rows, Columns> {
            auto result = math::Matrix<ElementType, Rows, Columns> {};

            // TODO(wpieterse): Implement me!

            return result;
        }

        template <size_t OutRows, size_t OutColumns, typename ElementType, size_t InRows, size_t InColumns>
        inline auto ExtractSubMatrix(const math::Matrix<ElementType, InRows, InColumns>& value)
          -> math::Matrix<ElementType, OutRows, OutColumns> {
            auto result = math::Matrix<ElementType, OutRows, OutColumns> {};

            static_assert(OutRows <= InRows);
            static_assert(OutColumns <= InColumns);

            for (auto row = size_t {0}; row < OutRows; row++) {
                for (auto column = size_t {0}; column < OutColumns; column++) {
                    const auto inner_value = math::matrix::Read(value, row, column);

                    math::matrix::Write(result, row, column, inner_value);
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Difference(const math::Matrix<ElementType, Rows, Columns>& lhs, const math::Matrix<ElementType, Rows, Columns>& rhs)
          -> ElementType {
            constexpr auto zero_positive = math::constants::ZeroPositive<ElementType>();
            constexpr auto one_negative  = math::constants::OneNegative<ElementType>();

            auto result = one_negative;

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    const auto lhs_value              = math::matrix::Read(lhs, row, column);
                    const auto rhs_value              = math::matrix::Read(rhs, row, column);
                    const auto difference             = math::arithmetic::Minus(lhs_value, rhs_value);
                    const auto absolute_difference    = math::special::Absolute(difference);
                    const auto is_less_than_zero      = math::utilities::LessThan(result, zero_positive);
                    const auto is_greater_than_result = math::utilities::GreaterThan(absolute_difference, result);

                    if (is_less_than_zero == true) {
                        result = absolute_difference;
                    }

                    if (is_greater_than_result == true) {
                        result = absolute_difference;
                    }
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Trace(const math::Matrix<ElementType, Rows, Columns>& value) -> ElementType {
            constexpr auto zero_positive = math::constants::ZeroPositive<ElementType>();

            auto result = zero_positive;

            static_assert(Rows == Columns);

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    const auto is_diagonal = math::utilities::Equal(row, column);

                    if (is_diagonal == true) {
                        const auto inner_value = math::matrix::Read(value, row, column);

                        result = math::arithmetic::Plus(result, inner_value);
                    }
                }
            }

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Determinant(const math::Matrix<ElementType, Rows, Columns>& value) -> ElementType {
            constexpr auto zero_positive = math::constants::ZeroPositive<ElementType>();

            auto result = zero_positive;

            static_assert(Rows == Columns);

            // TODO(wpieterse): Implement me!

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Compare(const math::Matrix<ElementType, Rows, Columns>& lhs,
                            const math::Matrix<ElementType, Rows, Columns>& rhs,
                            ElementType                                     epsilon) -> bool {
            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    const auto lhs_value = math::matrix::Read(lhs, row, column);
                    const auto rhs_value = math::matrix::Read(rhs, row, column);
                    const auto is_same   = math::utilities::Compare(lhs_value, rhs_value, epsilon);

                    if (is_same == false) {
                        return false;
                    }
                }
            }

            return true;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Compare(const math::Matrix<ElementType, Rows, Columns>& lhs, const math::Matrix<ElementType, Columns, Rows>& rhs)
          -> bool {
            constexpr auto zero_positive = math::constants::ZeroPositive<ElementType>();

            return math::matrix::Compare(lhs, rhs, zero_positive);
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Equal(const math::Matrix<ElementType, Rows, Columns>& lhs,
                          const math::Matrix<ElementType, Columns, Rows>& rhs,
                          ElementType                                     epsilon) -> bool {
            const auto result = math::matrix::Compare(lhs, rhs, epsilon);

            return result == true;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto NotEqual(const math::Matrix<ElementType, Rows, Columns>& lhs,
                             const math::Matrix<ElementType, Columns, Rows>& rhs,
                             ElementType                                     epsilon) -> bool {
            const auto result = math::matrix::Compare(lhs, rhs, epsilon);

            return result == false;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Equal(const math::Matrix<ElementType, Rows, Columns>& lhs, const math::Matrix<ElementType, Columns, Rows>& rhs)
          -> bool {
            const auto result = math::matrix::Compare(lhs, rhs);

            return result == true;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto NotEqual(const math::Matrix<ElementType, Rows, Columns>& lhs, const math::Matrix<ElementType, Columns, Rows>& rhs)
          -> bool {
            const auto result = math::matrix::Compare(lhs, rhs);

            return result == false;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsZero(const math::Matrix<ElementType, Rows, Columns>& value, ElementType epsilon) -> bool {
            // TODO(wpieterse): Simplify this.

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    const auto inner_value    = math::matrix::Read(value, row, column);
                    const auto absolute_value = math::special::Absolute(inner_value);
                    const auto is_not_zero    = math::utilities::GreaterThan(absolute_value, epsilon);

                    if (is_not_zero == true) {
                        return false;
                    }
                }
            }

            return true;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsZero(const math::Matrix<ElementType, Rows, Columns>& value) -> bool {
            constexpr auto zero_positive = math::constants::ZeroPositive<ElementType>();

            return math::matrix::IsZero(value, zero_positive);
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsDiagonal(const math::Matrix<ElementType, Rows, Columns>& value, ElementType epsilon) -> bool {
            // TODO(wpieterse): Simplify this.

            static_assert(Rows == Columns);

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    const auto is_diagonal = math::utilities::Equal(row, column);

                    if (is_diagonal == false) {
                        const auto inner_value    = math::matrix::Read(value, row, column);
                        const auto absolute_value = math::special::Absolute(inner_value);
                        const auto is_not_zero    = math::utilities::GreaterThan(absolute_value, epsilon);

                        if (is_not_zero == true) {
                            return false;
                        }
                    }
                }
            }

            return true;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsDiagonal(const math::Matrix<ElementType, Rows, Columns>& value) -> bool {
            constexpr auto zero_positive = math::constants::ZeroPositive<ElementType>();

            return math::matrix::IsDiagonal(value, zero_positive);
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsIdentity(const math::Matrix<ElementType, Rows, Columns>& value, ElementType epsilon) -> bool {
            constexpr auto zero_positive = math::constants::ZeroPositive<ElementType>();
            constexpr auto one_positive  = math::constants::OnePositive<ElementType>();

            static_assert(Rows == Columns);

            for (auto row = size_t {0}; row < Rows; row++) {
                for (auto column = size_t {0}; column < Columns; column++) {
                    const auto lhs_value   = math::matrix::Read(value, row, column);
                    const auto is_diagonal = math::utilities::Equal(row, column);
                    auto       rhs_value   = zero_positive;

                    if (is_diagonal == true) {
                        rhs_value = one_positive;
                    }

                    const auto is_correct = math::utilities::Compare(lhs_value, rhs_value, epsilon);

                    if (is_correct == false) {
                        return false;
                    }
                }
            }

            return true;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsIdentity(const math::Matrix<ElementType, Rows, Columns>& value) -> bool {
            constexpr auto zero_positive = math::constants::ZeroPositive<ElementType>();

            return math::matrix::IsIdentity(value, zero_positive);
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsTriDiagonal(const math::Matrix<ElementType, Rows, Columns>& value, ElementType epsilon) -> bool {
            // TODO(wpieterse): Simplify this.

            constexpr auto RowsMinusTwo = Rows - 2;

            static_assert(Rows == Columns);

            for (auto row = size_t {0}; row < RowsMinusTwo; row++) {
                const auto initial_column = row + 2;

                for (auto column = initial_column; column < Columns; column++) {
                    const auto left_value          = math::matrix::Read(value, row, column);
                    const auto absolute_left_value = math::special::Absolute(left_value);
                    const auto is_left_not_zero    = math::utilities::GreaterThan(absolute_left_value, epsilon);

                    if (is_left_not_zero == true) {
                        return false;
                    }

                    const auto right_value          = math::matrix::Read(value, column, row);
                    const auto absolute_right_value = math::special::Absolute(right_value);
                    const auto is_right_not_zero    = math::utilities::GreaterThan(absolute_right_value, epsilon);

                    if (is_right_not_zero == true) {
                        return false;
                    }
                }
            }

            return true;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsTriDiagonal(const math::Matrix<ElementType, Rows, Columns>& value) -> bool {
            constexpr auto zero_positive = math::constants::ZeroPositive<ElementType>();

            return math::matrix::IsTriDiagonal(value, zero_positive);
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsSymmetric(const math::Matrix<ElementType, Rows, Columns>& value, ElementType epsilon) -> bool {
            constexpr auto RowsMinusTwo = Rows - 2;

            static_assert(Rows == Columns);

            for (auto row = size_t {0}; row < RowsMinusTwo; row++) {
                const auto initial_column = row + 2;

                for (auto column = initial_column; column < Columns; column++) {
                    const auto left_value  = math::matrix::Read(value, row, column);
                    const auto right_value = math::matrix::Read(value, column, row);
                    const auto is_same     = math::utilities::Compare(left_value, right_value, epsilon);

                    if (is_same == false) {
                        return false;
                    }
                }
            }

            return true;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto IsSymmetric(const math::Matrix<ElementType, Rows, Columns>& value) -> bool {
            constexpr auto zero_positive = math::constants::ZeroPositive<ElementType>();

            return math::matrix::IsSymmetric(value, zero_positive);
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto RowToVector(const math::Matrix<ElementType, Rows, Columns>& value, size_t row) -> math::Vector<ElementType, Columns> {
            auto result = math::Vector<ElementType, Columns> {};

            // TODO(wpieterse): Implement me!

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto ColumnToVector(const math::Matrix<ElementType, Rows, Columns>& value, size_t column)
          -> math::Vector<ElementType, Rows> {
            auto result = math::Vector<ElementType, Rows> {};

            // TODO(wpieterse): Implement me!

            return result;
        }

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Multiply(const math::Matrix<ElementType, Rows, Columns>& lhs, const math::Vector<ElementType, Columns>& rhs)
          -> math::Vector<ElementType, Columns> {
            constexpr auto zero_positive = math::constants::ZeroPositive<ElementType>();

            auto result = math::Vector<ElementType, Columns> {};

            for (auto row = size_t {0}; row < Rows; row++) {
                math::vector::Write(result, row, zero_positive);

                for (auto column = size_t {0}; column < Columns; column++) {
                    const auto current_value = math::vector::Read(result, row);
                    const auto lhs_value     = math::matrix::Read(lhs, row, column);
                    const auto rhs_value     = math::vector::Read(rhs, column);
                    const auto sum           = math::arithmetic::Multiply(lhs_value, rhs_value);
                    const auto result_value  = math::arithmetic::Plus(current_value, sum);

                    math::vector::Write(result, row, result_value);
                }
            }

            return result;
        }

        namespace cartesian_model {
            template <typename ElementType>
            inline auto CreateIdentity() -> math::ModelMatrix<ElementType> {
                return math::matrix::CreateIdentity<ElementType, CartesianMatrixRows, CartesianMatrixColumns>();
            }

            template <typename ElementType>
            inline auto TranslateOnX(const math::ModelMatrix<ElementType>& value, ElementType offset) -> math::ModelMatrix<ElementType> {
                auto result = math::matrix::cartesian_model::CreateIdentity<ElementType>();

                math::matrix::Write(result, 0, 3, offset);

                return math::matrix::Multiply(value, result);
            }

            template <typename ElementType>
            inline auto TranslateOnY(const math::ModelMatrix<ElementType>& value, ElementType offset) -> math::ModelMatrix<ElementType> {
                auto result = math::matrix::cartesian_model::CreateIdentity<ElementType>();

                math::matrix::Write(result, 1, 3, offset);

                return math::matrix::Multiply(value, result);
            }

            template <typename ElementType>
            inline auto TranslateOnZ(const math::ModelMatrix<ElementType>& value, ElementType offset) -> math::ModelMatrix<ElementType> {
                auto result = math::matrix::cartesian_model::CreateIdentity<ElementType>();

                math::matrix::Write(result, 2, 3, offset);

                return math::matrix::Multiply(value, result);
            }

            template <typename ElementType>
            inline auto TranslateUniformly(const math::ModelMatrix<ElementType>& value, ElementType offset)
              -> math::ModelMatrix<ElementType> {
                auto result = math::matrix::cartesian_model::CreateIdentity<ElementType>();

                math::matrix::Write(result, 0, 3, offset);
                math::matrix::Write(result, 1, 3, offset);
                math::matrix::Write(result, 2, 3, offset);

                return math::matrix::Multiply(value, result);
            }

            template <typename ElementType>
            inline auto TranslateArbitrary(const math::ModelMatrix<ElementType>& value,
                                           ElementType                           x_offset,
                                           ElementType                           y_offset,
                                           ElementType                           z_offset) -> math::ModelMatrix<ElementType> {
                auto result = math::matrix::cartesian_model::CreateIdentity<ElementType>();

                math::matrix::Write(result, 0, 3, x_offset);
                math::matrix::Write(result, 1, 3, y_offset);
                math::matrix::Write(result, 2, 3, z_offset);

                return math::matrix::Multiply(value, result);
            }

            template <typename ElementType>
            inline auto ScaleOnX(const math::ModelMatrix<ElementType>& value, ElementType scale) -> math::ModelMatrix<ElementType> {
                auto result = math::matrix::cartesian_model::CreateIdentity<ElementType>();

                math::matrix::Write(result, 0, 0, scale);

                return math::matrix::Multiply(value, result);
            }

            template <typename ElementType>
            inline auto ScaleOnY(const math::ModelMatrix<ElementType>& value, ElementType scale) -> math::ModelMatrix<ElementType> {
                auto result = math::matrix::cartesian_model::CreateIdentity<ElementType>();

                math::matrix::Write(result, 1, 1, scale);

                return math::matrix::Multiply(value, result);
            }

            template <typename ElementType>
            inline auto ScaleOnZ(const math::ModelMatrix<ElementType>& value, ElementType scale) -> math::ModelMatrix<ElementType> {
                auto result = math::matrix::cartesian_model::CreateIdentity<ElementType>();

                math::matrix::Write(result, 2, 2, scale);

                return math::matrix::Multiply(value, result);
            }

            template <typename ElementType>
            inline auto ScaleUniformly(const math::ModelMatrix<ElementType>& value, ElementType scale) -> math::ModelMatrix<ElementType> {
                auto result = math::matrix::cartesian_model::CreateIdentity<ElementType>();

                math::matrix::Write(result, 0, 0, scale);
                math::matrix::Write(result, 1, 1, scale);
                math::matrix::Write(result, 2, 2, scale);

                return math::matrix::Multiply(value, result);
            }

            template <typename ElementType>
            inline auto
            ScaleArbitrary(const math::ModelMatrix<ElementType>& value, ElementType x_scale, ElementType y_scale, ElementType z_scale)
              -> math::ModelMatrix<ElementType> {
                auto result = math::matrix::cartesian_model::CreateIdentity<ElementType>();

                math::matrix::Write(result, 0, 0, x_scale);
                math::matrix::Write(result, 1, 1, y_scale);
                math::matrix::Write(result, 2, 2, z_scale);

                return math::matrix::Multiply(value, result);
            }

            namespace rotate_radians {
                template <typename ElementType>
                inline auto AroundX(const math::ModelMatrix<ElementType>& value, ElementType radians) -> math::ModelMatrix<ElementType> {
                    auto result = math::matrix::cartesian_model::CreateIdentity<ElementType>();

                    const auto sine         = math::trigonometry::radians::Sine(radians);
                    const auto cosine       = math::trigonometry::radians::Cosine(radians);
                    const auto inverse_sine = math::arithmetic::Negate(sine);

                    math::matrix::Write(result, 1, 1, cosine);
                    math::matrix::Write(result, 1, 2, inverse_sine);
                    math::matrix::Write(result, 2, 1, sine);
                    math::matrix::Write(result, 2, 2, cosine);

                    return math::matrix::Multiply(value, result);
                }

                template <typename ElementType>
                inline auto AroundY(const math::ModelMatrix<ElementType>& value, ElementType radians) -> math::ModelMatrix<ElementType> {
                    auto result = math::matrix::cartesian_model::CreateIdentity<ElementType>();

                    const auto sine         = math::trigonometry::radians::Sine(radians);
                    const auto cosine       = math::trigonometry::radians::Cosine(radians);
                    const auto inverse_sine = math::arithmetic::Negate(sine);

                    math::matrix::Write(result, 0, 0, cosine);
                    math::matrix::Write(result, 0, 2, sine);
                    math::matrix::Write(result, 2, 0, inverse_sine);
                    math::matrix::Write(result, 2, 2, cosine);

                    return math::matrix::Multiply(value, result);
                }

                template <typename ElementType>
                inline auto AroundZ(const math::ModelMatrix<ElementType>& value, ElementType radians) -> math::ModelMatrix<ElementType> {
                    auto result = math::matrix::cartesian_model::CreateIdentity<ElementType>();

                    const auto sine         = math::trigonometry::radians::Sine(radians);
                    const auto cosine       = math::trigonometry::radians::Cosine(radians);
                    const auto inverse_sine = math::arithmetic::Negate(sine);

                    math::matrix::Write(result, 0, 0, cosine);
                    math::matrix::Write(result, 0, 1, inverse_sine);
                    math::matrix::Write(result, 1, 0, sine);
                    math::matrix::Write(result, 1, 1, cosine);

                    return math::matrix::Multiply(value, result);
                }
            } // namespace rotate_radians

            namespace rotate_degrees {
                template <typename ElementType>
                inline auto AroundX(const math::ModelMatrix<ElementType>& value, ElementType degrees) -> math::ModelMatrix<ElementType> {
                    const auto radians = math::trigonometry::DegreesToRadians(degrees);

                    return math::matrix::cartesian_model::rotate_radians::AroundX(value, radians);
                }

                template <typename ElementType>
                inline auto AroundY(const math::ModelMatrix<ElementType>& value, ElementType degrees) -> math::ModelMatrix<ElementType> {
                    const auto radians = math::trigonometry::DegreesToRadians(degrees);

                    return math::matrix::cartesian_model::rotate_radians::AroundY(value, radians);
                }

                template <typename ElementType>
                inline auto AroundZ(const math::ModelMatrix<ElementType>& value, ElementType degrees) -> math::ModelMatrix<ElementType> {
                    const auto radians = math::trigonometry::DegreesToRadians(degrees);

                    return math::matrix::cartesian_model::rotate_radians::AroundZ(value, radians);
                }
            } // namespace rotate_degrees
        }     // namespace cartesian_model

        namespace cartesian_view {
            template <typename ElementType>
            inline auto CreateIdentity() -> math::ViewMatrix<ElementType> {
                return math::matrix::CreateIdentity<ElementType, CartesianMatrixRows, CartesianMatrixColumns>();
            }

            namespace detail {
                template <typename ElementType>
                auto ScaleToWindow(const math::ViewMatrix<ElementType>& value, ElementType width, ElementType height)
                  -> math::ViewMatrix<ElementType> {
                    constexpr auto two_positive = math::constants::TwoPositive<ElementType>();

                    auto result = math::matrix::cartesian_view::CreateIdentity<ElementType>();

                    const auto half_width  = math::arithmetic::Divide(width, two_positive);
                    const auto half_height = math::arithmetic::Divide(height, two_positive);

                    math::matrix::Write(result, 0, 0, half_width);
                    math::matrix::Write(result, 1, 1, half_height);

                    return math::matrix::Multiply(value, result);
                }

                template <typename ElementType>
                auto OffsetExtent(const math::ViewMatrix<ElementType>& value, ElementType width, ElementType height)
                  -> math::ViewMatrix<ElementType> {
                    constexpr auto two_positive = math::constants::TwoPositive<ElementType>();

                    auto result = math::matrix::cartesian_view::CreateIdentity<ElementType>();

                    const auto half_width  = math::arithmetic::Divide(width, two_positive);
                    const auto half_height = math::arithmetic::Divide(height, two_positive);

                    math::matrix::Write(result, 0, 3, half_width);
                    math::matrix::Write(result, 1, 3, half_height);

                    return math::matrix::Multiply(value, result);
                }

                template <typename ElementType>
                auto OffsetOrigin(const math::ViewMatrix<ElementType>& value, ElementType x, ElementType y)
                  -> math::ViewMatrix<ElementType> {
                    auto result = math::matrix::cartesian_view::CreateIdentity<ElementType>();

                    math::matrix::Write(result, 0, 3, x);
                    math::matrix::Write(result, 1, 3, y);

                    return math::matrix::Multiply(value, result);
                }
            } // namespace detail

            template <typename ElementType>
            auto Create(const math::ViewMatrix<ElementType>& value, ElementType x, ElementType y, ElementType width, ElementType height)
              -> math::ViewMatrix<ElementType> {
                auto result = math::matrix::cartesian_view::CreateIdentity<ElementType>();

                result = math::matrix::cartesian_view::detail::OffsetOrigin(result, x, y);
                result = math::matrix::cartesian_view::detail::OffsetExtent(result, width, height);
                result = math::matrix::cartesian_view::detail::ScaleToWindow(result, width, height);

                return math::matrix::Multiply(value, result);
            }
        } // namespace cartesian_view

        namespace cartesian_projection {
            template <typename ElementType>
            inline auto CreateIdentity() -> ProjectionMatrix<ElementType> {
                return math::matrix::CreateIdentity<ElementType, CartesianMatrixRows, CartesianMatrixColumns>();
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
                        constexpr auto two_positive = math::constants::TwoPositive<ElementType>();

                        auto result = math::matrix::cartesian_projection::CreateIdentity<ElementType>();

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

                        math::matrix::Write(result, 0, 3, middle_x_negated);
                        math::matrix::Write(result, 1, 3, middle_y_negated);
                        math::matrix::Write(result, 2, 3, middle_z_negated);

                        return math::matrix::Multiply(value, result);
                    }

                    template <typename ElementType>
                    inline auto ScaleView(const ProjectionMatrix<ElementType>& value,
                                          ElementType                          left,
                                          ElementType                          right,
                                          ElementType                          top,
                                          ElementType                          bottom,
                                          ElementType                          near,
                                          ElementType                          far) -> ProjectionMatrix<ElementType> {
                        constexpr auto two_positive = math::constants::TwoPositive<ElementType>();

                        auto result = math::matrix::cartesian_projection::CreateIdentity<ElementType>();

                        const auto scale_x_middle = math::arithmetic::Minus(right, left);
                        const auto scale_x_half   = math::arithmetic::Divide(two_positive, scale_x_middle);
                        const auto scale_y_middle = math::arithmetic::Minus(top, bottom);
                        const auto scale_y_half   = math::arithmetic::Divide(two_positive, scale_y_middle);
                        const auto scale_z_middle = math::arithmetic::Minus(far, near);
                        const auto scale_z_half   = math::arithmetic::Divide(two_positive, scale_z_middle);

                        math::matrix::Write(result, 0, 0, scale_x_half);
                        math::matrix::Write(result, 1, 2, scale_y_half);
                        math::matrix::Write(result, 2, 2, scale_z_half);

                        return math::matrix::Multiply(value, result);
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
                    auto result = math::matrix::cartesian_projection::CreateIdentity<ElementType>();

                    result = math::matrix::cartesian_projection::orthographic::detail::CenterAboutOrigin(
                      result, left, right, top, bottom, near, far);
                    result =
                      math::matrix::cartesian_projection::orthographic::detail::ScaleView(result, left, right, top, bottom, near, far);

                    return math::matrix::Multiply(value, result);
                }

                template <typename ElementType>
                inline auto CreateCompacted(const ProjectionMatrix<ElementType>& value,
                                            ElementType                          left,
                                            ElementType                          right,
                                            ElementType                          top,
                                            ElementType                          bottom,
                                            ElementType                          near,
                                            ElementType                          far) -> ProjectionMatrix<ElementType> {
                    constexpr auto two_positive = math::constants::TwoPositive<ElementType>();

                    auto result = math::matrix::cartesian_projection::CreateIdentity<ElementType>();

                    const auto middle_x_plus         = right + left;
                    const auto middle_x_plus_negated = -middle_x_plus;
                    const auto middle_x_minus        = right - left;
                    const auto middle_x_half         = two_positive / middle_x_minus;
                    const auto middle_x_divide       = middle_x_plus_negated / middle_x_minus;
                    const auto middle_y_plus         = top + bottom;
                    const auto middle_y_plus_negated = -middle_y_plus;
                    const auto middle_y_minus        = top - bottom;
                    const auto middle_y_half         = two_positive / middle_y_minus;
                    const auto middle_y_divide       = middle_y_plus_negated / middle_y_minus;
                    const auto middle_z_plus         = far + near;
                    const auto middle_z_plus_negated = -middle_z_plus;
                    const auto middle_z_minus        = far - near;
                    const auto middle_z_half         = two_positive / middle_z_minus;
                    const auto middle_z_divide       = middle_z_plus_negated / middle_z_minus;

                    result.elements[0][0] = middle_x_half;
                    result.elements[1][1] = middle_y_half;
                    result.elements[2][2] = middle_z_half;

                    result.elements[0][3] = middle_x_divide;
                    result.elements[1][3] = middle_y_divide;
                    result.elements[2][3] = middle_z_divide;

                    return math::matrix::Multiply(value, result);
                }
            } // namespace orthographic
        }     // namespace cartesian_projection

        template <typename ElementType, size_t Rows, size_t Columns>
        inline auto Print(const math::Matrix<ElementType, Rows, Columns>& value) -> void {
            constexpr auto columns_minus_one = Columns - 1;

            for (auto row = size_t {0}; row < Rows; row++) {
                std::cout << "| ";

                for (auto column = size_t {0}; column < Columns; column++) {
                    const auto can_print_comma = math::utilities::LessThan(column, columns_minus_one);
                    const auto inner_value     = math::matrix::Read(value, row, column);

                    std::cout << inner_value;
                    if (can_print_comma == true) {
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
    auto model = math::matrix::cartesian_model::CreateIdentity<float>();
    model      = math::matrix::cartesian_model::rotate_degrees::AroundX(model, 0.0f);
    model      = math::matrix::cartesian_model::rotate_degrees::AroundY(model, 0.0f);
    model      = math::matrix::cartesian_model::rotate_degrees::AroundZ(model, 0.0f);
    model      = math::matrix::cartesian_model::ScaleOnX(model, 1.0f);
    model      = math::matrix::cartesian_model::ScaleOnY(model, 1.0f);
    model      = math::matrix::cartesian_model::ScaleOnZ(model, 1.0f);
    model      = math::matrix::cartesian_model::TranslateOnX(model, 0.0f);
    model      = math::matrix::cartesian_model::TranslateOnY(model, 0.0f);
    model      = math::matrix::cartesian_model::TranslateOnZ(model, 0.0f);
    math::matrix::Print(model);
    std::cout << std::endl;

    auto view = math::matrix::cartesian_view::CreateIdentity<float>();
    view      = math::matrix::cartesian_view::Create(view, 0.0f, 0.0f, 640.0f, 480.0f);
    math::matrix::Print(view);
    std::cout << std::endl;

    auto projection = math::matrix::cartesian_projection::CreateIdentity<float>();
    projection      = math::matrix::cartesian_projection::orthographic::CreateExpanded(projection, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    math::matrix::Print(projection);
    std::cout << std::endl;

    auto model_view_projection = math::matrix::CreateIdentity<float, 4, 4>();
    model_view_projection      = math::matrix::Multiply(model_view_projection, model);
    model_view_projection      = math::matrix::Multiply(model_view_projection, view);
    model_view_projection      = math::matrix::Multiply(model_view_projection, projection);
    math::matrix::Print(model_view_projection);
    std::cout << std::endl;

    auto vertex = math::vector::CreateZero<float, 4>();
    math::vector::Write(vertex, 0, -0.5f);
    math::vector::Write(vertex, 1, 0.0f);
    math::vector::Write(vertex, 2, 0.0f);
    math::vector::Write(vertex, 3, 1.0f);
    vertex = math::matrix::Multiply(model_view_projection, vertex);
    math::vector::Print(vertex);
    std::cout << std::endl;

    return 0;
}
