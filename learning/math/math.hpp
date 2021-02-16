template <typename Type>
concept Arithmetic = requires(Type) {
    std::is_arithmetic_v<Type>;
};

template <typename Type>
concept Decimal = requires(Type) {
    std::is_floating_point_v<Type>;
};

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

namespace detail {
    template <typename Type, size_t Dimensions>
    concept SizedVector = requires(Type) {
        std::is_floating_point_v<Type>;
        Dimensions > 0;
    };

    template <typename Type, size_t Rows, size_t Columns>
    concept SizedMatrix = requires(Type) {
        std::is_floating_point_v<Type>;
        Rows > 0;
        Columns > 0;
    };

    template <typename Type, size_t Dimensions>
    concept SizedPlane = requires(Type) {
        std::is_floating_point_v<Type>;
        Dimensions > 0;
    };
} // namespace detail

constexpr auto VectorXComponent = size_t {0};
constexpr auto VectorYComponent = size_t {1};
constexpr auto VectorZComponent = size_t {2};
constexpr auto VectorWComponent = size_t {3};

template <typename Type, size_t Dimensions>
requires detail::SizedVector<Type, Dimensions> struct Vector {
    Type elements[Dimensions];
};

template <typename Type, size_t Rows, size_t Columns>
requires detail::SizedMatrix<Type, Rows, Columns> struct Matrix {
    Type elements[Rows][Columns];
};

enum class PlaneType {
    PositiveX = 0,
    PositiveY = 1,
    PositiveZ = 2,
    NegativeX = 3,
    NegativeY = 4,
    NegativeZ = 5,
    TrueAxial = 6,
    ZeroX     = 6,
    ZeroY     = 7,
    ZeroZ     = 8,
    NonAxial  = 9,
};

enum class Side {
    On,
    Front,
    Back,
};

template <typename Type, size_t Dimensions>
requires detail::SizedPlane<Type, Dimensions> struct Plane {
    Vector<Type, Dimensions> normal;
    Type                     distance;
};
