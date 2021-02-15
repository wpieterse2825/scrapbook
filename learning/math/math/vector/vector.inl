namespace math::vector {
    template <typename Type, size_t Elements>
    inline auto Read(const Vector<Type, Elements>& value, size_t index) -> Type {
        assert(index < Elements);

        return value.elements[index];
    }

    template <typename Type, size_t Elements>
    inline auto Write(Vector<Type, Elements>& value, size_t index, Type inner_value) -> void {
        assert(index < Elements);

        value.elements[index] = inner_value;
    }

    template <typename Type, size_t Elements>
    inline auto CreateZero() -> Vector<Type, Elements> {
        constexpr auto zero_positive = math::Constants<Type>::ZeroPositive;

        auto result = Vector<Type, Elements> {};

        for (auto index = size_t {0}; index < Elements; index++) {
            math::vector::Write(result, index, zero_positive);
        }

        return result;
    }

    template <typename Type, size_t Elements>
    inline auto CreateBroadcast(Type value) -> Vector<Type, Elements> {
        auto result = Vector<Type, Elements> {};

        for (auto index = size_t {0}; index < Elements; index++) {
            math::vector::Write(result, index, value);
        }

        return result;
    }

    template <typename Type, size_t Elements>
    inline auto Print(const Vector<Type, Elements>& value) -> void {
        constexpr auto elements_minus_one = Elements - 1;

        std::cout << "[ ";

        for (auto index = size_t {0}; index < Elements; index++) {
            const auto can_write_comma = comparison::LessThan(index, elements_minus_one);
            const auto inner_value     = math::vector::Read(value, index);

            std::cout << inner_value;

            if (can_write_comma == true) {
                std::cout << ", ";
            }
        }

        std::cout << " ]";
        std::cout << std::endl;
    }
} // namespace math::vector
