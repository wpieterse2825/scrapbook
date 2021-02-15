namespace math::arithmetic {
    template <Decimal Type>
    inline auto Affirm(Type value) -> Type {
        return +value;
    }

    template <Decimal Type>
    inline auto Negate(Type value) -> Type {
        return -value;
    }

    template <Decimal Type>
    inline auto Plus(Type lhs, Type rhs) -> Type {
        return lhs + rhs;
    }

    template <Decimal Type>
    inline auto Minus(Type lhs, Type rhs) -> Type {
        return lhs - rhs;
    }

    template <Decimal Type>
    inline auto Multiply(Type lhs, Type rhs) -> Type {
        return lhs * rhs;
    }

    template <Decimal Type>
    inline auto Divide(Type lhs, Type rhs) -> Type {
        return lhs / rhs;
    }
} // namespace math::arithmetic
