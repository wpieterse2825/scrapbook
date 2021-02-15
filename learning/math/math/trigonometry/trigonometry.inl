namespace math::trigonometry {
    template <Decimal Type>
    inline auto DegreesToRadians(Type degrees) -> Type {
        constexpr auto pi                       = math::Constants<Type>::PiPositive;
        constexpr auto degrees_two_quarters     = math::Constants<Type>::DegreesTwoQuartersPositive;
        constexpr auto degrees_to_radians_scale = math::arithmetic::Divide(pi, degrees_two_quarters);

        return math::arithmetic::Multiply(degrees, degrees_to_radians_scale);
    }

    template <Decimal Type>
    inline auto RadiansToDegrees(Type radians) -> Type {
        constexpr auto degrees_two_quarters     = math::Constants<Type>::DegreesTwoQuartersPositive;
        constexpr auto pi                       = math::Constants<Type>::PiPositive;
        constexpr auto radians_to_degrees_scale = math::arithmetic::Divide(degrees_two_quarters, pi);

        return math::arithmetic::Multiply(radians, radians_to_degrees_scale);
    }
} // namespace math::trigonometry
