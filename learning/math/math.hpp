template <typename Type>
concept Arithmetic = requires(Type) {
    std::is_arithmetic_v<Type>;
};

template <typename Type>
concept Decimal = requires(Type) {
    std::is_floating_point_v<Type>;
};

template <Decimal Type>
struct MathConstants {
    static constexpr auto Zero    = Type {0.0};
    static constexpr auto OneHalf = Type {0.5};
    static constexpr auto One     = Type {1.0};
    static constexpr auto TwoHalf = Type {1.5};
    static constexpr auto Two     = Type {2.0};
    static constexpr auto Three   = Type {3.0};
    static constexpr auto Four    = Type {4.0};

    static constexpr auto Epsilon      = Type {1e-4};
    static constexpr auto BelowEpsilon = Epsilon - Type {1e-5};
    static constexpr auto Pi           = Type {M_PI};

    static constexpr auto DegreesOneQuarter    = Type {90.0};
    static constexpr auto DegreesTwoQuarters   = Type {180.0};
    static constexpr auto DegreesThreeQuarters = Type {270.0};
    static constexpr auto DegreesFourQuarters  = Type {320.0};

    static constexpr auto RadiansOneQuarter    = Type {Pi * OneHalf};
    static constexpr auto RadiansTwoQuarters   = Type {Pi * One};
    static constexpr auto RadiansThreeQuarters = Type {Pi * TwoHalf};
    static constexpr auto RadiansFourQuarters  = Type {Pi * Two};
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

constexpr auto VectorSIMDEnabled  = true;
constexpr auto VectorSIMDUseSSE1  = true;
constexpr auto VectorSIMDUseSSE2  = true;
constexpr auto VectorSIMDUseSSE3  = true;
constexpr auto VectorSIMDUseSSSE3 = true;
constexpr auto VectorSIMDUseSSE41 = true;
constexpr auto VectorSIMDUseSSE42 = true;
constexpr auto VectorSIMDUseAVX1  = true;
constexpr auto VectorSIMDUseAVX2  = true;

constexpr auto DefaultTestDimensions = size_t {127};

constexpr auto DefaultBenchSampleCount    = 10;
constexpr auto DefaultBenchIterationCount = 10000000;
constexpr auto DefaultBenchDimensions     = size_t {127};

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
