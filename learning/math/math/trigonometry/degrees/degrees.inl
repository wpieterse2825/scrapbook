namespace math::trigonometry::degrees {
    template <Decimal Type>
    inline auto Sine(Type degrees) -> Type {
        const auto degrees_to_radians = math::trigonometry::DegreesToRadians(degrees);

        auto result = math::trigonometry::radians::Sine(degrees_to_radians);

        return math::trigonometry::RadiansToDegrees(result);
    }

    template <Decimal Type>
    inline auto Cosine(Type degrees) -> Type {
        const auto degrees_to_radians = math::trigonometry::DegreesToRadians(degrees);

        auto result = math::trigonometry::radians::Cosine(degrees_to_radians);

        return math::trigonometry::RadiansToDegrees(result);
    }

    template <Decimal Type>
    inline auto Tangent(Type degrees) -> Type {
        const auto degrees_to_radians = math::trigonometry::DegreesToRadians(degrees);

        auto result = math::trigonometry::radians::Tangent(degrees_to_radians);

        return math::trigonometry::RadiansToDegrees(result);
    }
} // namespace math::trigonometry::degrees
