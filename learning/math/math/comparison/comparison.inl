namespace math::comparison {
    // TODO(wpieterse): Add epsilon calls for the below functions.
    template <Decimal Type>
    inline auto LessThan(Type lhs, Type rhs) -> bool {
        return lhs < rhs;
    }

    template <Decimal Type>
    inline auto LessThanOrEqual(Type lhs, Type rhs) -> bool {
        return lhs <= rhs;
    }

    template <Decimal Type>
    inline auto GreaterThan(Type lhs, Type rhs) -> bool {
        return lhs > rhs;
    }

    template <Decimal Type>
    inline auto GreaterThanOrEqual(Type lhs, Type rhs) -> bool {
        return lhs >= rhs;
    }

    template <Decimal Type>
    inline auto Compare(Type lhs, Type rhs, Type epsilon) -> bool {
        const auto difference              = math::arithmetic::Minus(lhs, rhs);
        const auto absolute_difference     = math::mapping::Absolute(difference);
        const auto is_greater_than_epsilon = math::comparison::GreaterThan(absolute_difference, epsilon);

        if (is_greater_than_epsilon == true) {
            return false;
        }

        return true;
    }

    template <Decimal Type>
    inline auto Equal(Type lhs, Type rhs, Type epsilon) -> bool {
        const auto result = math::comparison::Compare(lhs, rhs, epsilon);

        return result == true;
    }

    template <Decimal Type>
    inline auto NotEqual(Type lhs, Type rhs, Type epsilon) -> bool {
        const auto result = math::comparison::Compare(lhs, rhs, epsilon);

        return result == false;
    }

    template <Decimal Type>
    inline auto Compare(Type lhs, Type rhs) -> bool {
        return lhs == rhs;
    }

    template <Decimal Type>
    inline auto Equal(Type lhs, Type rhs) -> bool {
        const auto result = math::comparison::Compare(lhs, rhs);

        return result == true;
    }

    template <Decimal Type>
    inline auto NotEqual(Type lhs, Type rhs) -> bool {
        const auto result = math::comparison::Compare(lhs, rhs);

        return result == false;
    }
} // namespace math::comparison
