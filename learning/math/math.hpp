constexpr auto MathSIMDEnabled     = true;
constexpr auto MathSIMDEnableSSE1  = true;
constexpr auto MathSIMDEnableSSE2  = true;
constexpr auto MathSIMDEanbleSSE3  = true;
constexpr auto MathSIMDEnableSSSE3 = true;
constexpr auto MathSIMDEnableSSE41 = true;
constexpr auto MathSIMDEnableSSE42 = true;
constexpr auto MathSIMDEnableAVX1  = true;
constexpr auto MathSIMDEnableAVX2  = true;

template <typename Type>
concept Arithmetic = requires(Type) {
    std::is_arithmetic_v<Type>;
};

template <typename Type>
concept Decimal = requires(Type) {
    std::is_floating_point_v<Type>;
};

enum class Side {
    On,
    Front,
    Back,
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

template <typename Type, size_t Dimensions>
requires detail::SizedVector<Type, Dimensions> struct Vector {
    Type elements[Dimensions];
};

template <typename Type, size_t Rows, size_t Columns>
requires detail::SizedMatrix<Type, Rows, Columns> struct Matrix {
    Type elements[Rows][Columns];
};

template <typename Type, size_t Dimensions>
requires detail::SizedPlane<Type, Dimensions> struct Plane {
    Vector<Type, Dimensions> normal;
    Type                     distance;
};

template <typename Type>
constexpr auto IsSinglePrecision() -> bool {
    return std::is_same_v<Type, float>;
}

template <typename Type>
constexpr auto IsDoublePrecision() -> bool {
    return std::is_same_v<Type, double>;
}
