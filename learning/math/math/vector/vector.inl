template <typename Type, size_t Elements>
inline auto ZeroVector() -> Vector<Type, Elements> {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    auto output = Vector<Type, Elements> {};

    for (auto index = size_t {0}; index < Elements; index++) {
        output.elements[index] = zero_positive;
    }

    return output;
}

template <typename Type, size_t Elements>
inline auto UniformVector(Type input_value) -> Vector<Type, Elements> {
    auto output = Vector<Type, Elements> {};

    for (auto index = size_t {0}; index < Elements; index++) {
        output.elements[index] = input_value;
    }

    return output;
}

template <typename Type, size_t Elements>
inline auto Compare(const Vector<Type, Elements>& lhs, const Vector<Type, Elements>& rhs, Type epsilon) -> bool {
    for (auto index = size_t {0}; index < Elements; index++) {
        const auto lhs_value         = lhs.elements[index];
        const auto rhs_value         = rhs.elements[index];
        const auto difference        = lhs_value - rhs_value;
        const auto absolute_differen = Absolute(difference);

        if (absolute_differen > epsilon) {
            return false;
        }
    }

    return true;
}

template <typename Type, size_t Elements>
inline auto Compare(const Vector<Type, Elements>& lhs, const Vector<Type, Elements>& rhs) -> bool {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    return Compare(lhs, rhs, zero_positive);
}

template <typename Type, size_t Elements>
inline auto Negate(const Vector<Type, Elements>& input) -> Vector<Type, Elements> {
    auto output = Vector<Type, Elements> {};

    for (auto index = size_t {0}; index < Elements; index++) {
        output.elements[index] = -input.elements[index];
    }

    return output;
}

template <typename Type, size_t Elements>
inline auto Plus(const Vector<Type, Elements>& lhs, const Vector<Type, Elements>& rhs) -> Vector<Type, Elements> {
    auto output = Vector<Type, Elements> {};

    for (auto index = size_t {0}; index < Elements; index++) {
        const auto lhs_value = lhs.elements[index];
        const auto rhs_value = rhs.elements[index];
        const auto sum_value = lhs_value + rhs_value;

        output.elements[index] = sum_value;
    }

    return output;
}

template <typename Type, size_t Elements>
inline auto Minus(const Vector<Type, Elements>& lhs, const Vector<Type, Elements>& rhs) -> Vector<Type, Elements> {
    auto output = Vector<Type, Elements> {};

    for (auto index = size_t {0}; index < Elements; index++) {
        const auto lhs_value = lhs.elements[index];
        const auto rhs_value = rhs.elements[index];
        const auto sum_value = lhs_value - rhs_value;

        output.elements[index] = sum_value;
    }

    return output;
}

template <typename Type, size_t Elements>
inline auto Multiply(const Vector<Type, Elements>& lhs, Type rhs) -> Vector<Type, Elements> {
    auto output = Vector<Type, Elements> {};

    for (auto index = size_t {0}; index < Elements; index++) {
        const auto lhs_value = lhs.elements[index];
        const auto rhs_value = rhs;
        const auto sum_value = lhs_value * rhs_value;

        output.elements[index] = sum_value;
    }

    return output;
}

template <typename Type, size_t Elements>
inline auto Divide(const Vector<Type, Elements>& lhs, Type rhs) -> Vector<Type, Elements> {
    auto output = Vector<Type, Elements> {};

    for (auto index = size_t {0}; index < Elements; index++) {
        const auto lhs_value = lhs.elements[index];
        const auto rhs_value = rhs;
        const auto sum_value = lhs_value / rhs_value;

        output.elements[index] = sum_value;
    }

    return output;
}

template <typename Type, size_t Elements>
inline auto Divide(const Vector<Type, Elements>& lhs, const Vector<Type, Elements>& rhs) -> Vector<Type, Elements> {
    auto output = Vector<Type, Elements> {};

    for (auto index = size_t {0}; index < Elements; index++) {
        const auto lhs_value = lhs.elements[index];
        const auto rhs_value = rhs.elements[index];
        const auto sum_value = lhs_value / rhs_value;

        output.elements[index] = sum_value;
    }

    return output;
}

template <typename Type, size_t Elements>
inline auto Truncate(const Vector<Type, Elements>& input, Type output_length) -> Vector<Type, Elements> {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    if (output_length == zero_positive) {
        return ZeroVector<Type, Elements>();
    }

    auto       output                = Vector<Type, Elements> {};
    const auto output_length_squared = output_length * output_length;
    auto       input_length_squared  = zero_positive;

    for (auto index = size_t {0}; index < Elements; index++) {
        const auto input_value   = input.elements[index];
        const auto input_squared = input_value * input_value;

        input_length_squared += input_squared;
    }

    if (input_length_squared > output_length_squared) {
        const auto input_length_inversed  = InverseSquareRoot(input_length_squared);
        const auto output_length_inversed = output_length * input_length_inversed;

        for (auto index = size_t {0}; index < Elements; index++) {
            const auto input_value  = input.elements[index];
            const auto output_value = input_value * output_length_inversed;

            output.elements[index] = output_value;
        }
    } else {
        for (auto index = size_t {0}; index < Elements; index++) {
            output.elements[index] = input.elements[index];
        }
    }

    return output;
}

template <typename Type, size_t Elements>
inline auto Normalize(const Vector<Type, Elements>& input) -> Vector<Type, Elements> {
    constexpr auto one_positive = Constants<Type>::OnePositive;

    return Truncate(input, one_positive);
}

template <typename Type, size_t Elements>
inline auto DotProduct(const Vector<Type, Elements>& lhs, const Vector<Type, Elements>& rhs) -> Type {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    auto output_value = zero_positive;

    for (auto index = size_t {0}; index < Elements; index++) {
        const auto lhs_value = lhs.elements[index];
        const auto rhs_value = rhs.elements[index];
        const auto sum_value = lhs_value * rhs_value;

        output_value += sum_value;
    }

    return output_value;
}

template <typename Type>
inline auto CrossProduct(const Vector<Type, 3>& lhs, const Vector<Type, 3>& rhs) -> Vector<Type, 3> {
    auto output = Vector<Type, 3> {};

    output.elements[0] = lhs.elements[1] * rhs.elements[2] - lhs.elements[2] * rhs.elements[1];
    output.elements[1] = lhs.elements[2] * rhs.elements[0] - lhs.elements[0] * rhs.elements[2];
    output.elements[2] = lhs.elements[0] * rhs.elements[1] - lhs.elements[1] * rhs.elements[0];

    return output;
}

template <typename Type, size_t Elements>
inline auto Length(const Vector<Type, Elements>& input) -> Type {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    auto output_value = zero_positive;

    for (auto index = size_t {0}; index < Elements; index++) {
        const auto input_value   = input.elements[index];
        const auto input_squared = input_value * input_value;

        output_value += input_squared;
    }

    return SquareRoot(output_value);
}

template <typename Type, size_t Elements>
inline auto Clamp(const Vector<Type, Elements>& input, Type minimum, Type maximum) -> Vector<Type, Elements> {
    auto output = Vector<Type, Elements> {};

    for (auto index = size_t {0}; index < Elements; index++) {
        const auto input_value = input.elements[index];
        if (input_value < minimum) {
            output.elements[index] = minimum;
        } else if (input_value > maximum) {
            output.elements[index] = maximum;
        } else {
            output.elements[index] = input_value;
        }
    }

    return output;
}

template <typename Type, size_t Elements>
inline auto Snap(const Vector<Type, Elements>& input) -> Vector<Type, Elements> {
    constexpr auto one_half_plus = Constants<Type>::OneHalfPlus;

    auto output = Vector<Type, Elements> {};

    for (auto index = size_t {0}; index < Elements; index++) {
        auto input_value = input.elements[index];
        auto input_nudge = input_value + one_half_plus;
        auto input_snap  = Floor(input_nudge);

        output.elements[index] = input_snap;
    }

    return output;
}

template <typename Type, size_t Elements>
inline auto Print(const Vector<Type, Elements>& input) -> void {
    constexpr auto elements_minus_one = Elements - 1;

    std::cout << "[ ";

    for (auto index = size_t {0}; index < Elements; index++) {
        std::cout << input.elements[index];

        if (index < elements_minus_one) {
            std::cout << ", ";
        }
    }

    std::cout << " ]";
    std::cout << std::endl;
}

template <typename Type, size_t Elements>
inline auto operator==(const Vector<Type, Elements>& lhs, const Vector<Type, Elements>& rhs) -> bool {
    const auto output_value = Compare(lhs, rhs);

    return output_value == true;
}

template <typename Type, size_t Elements>
inline auto operator!=(const Vector<Type, Elements>& lhs, const Vector<Type, Elements>& rhs) -> bool {
    const auto output_value = Compare(lhs, rhs);

    return output_value == false;
}

template <typename Type, size_t Elements>
inline auto operator-(const Vector<Type, Elements>& input) -> Vector<Type, Elements> {
    return Negate(input);
}

template <typename Type, size_t Elements>
inline auto operator+(const Vector<Type, Elements>& lhs, const Vector<Type, Elements>& rhs) -> Vector<Type, Elements> {
    return Plus(lhs, rhs);
}

template <typename Type, size_t Elements>
inline auto operator-(const Vector<Type, Elements>& lhs, const Vector<Type, Elements>& rhs) -> Vector<Type, Elements> {
    return Minus(lhs, rhs);
}

template <typename Type, size_t Elements>
inline auto operator*(const Vector<Type, Elements>& lhs, Type rhs) -> Vector<Type, Elements> {
    return Multiply(lhs, rhs);
}

template <typename Type, size_t Elements>
inline auto operator*(const Vector<Type, Elements>& lhs, const Vector<Type, Elements>& rhs) -> Type {
    return DotProduct(lhs, rhs);
}

template <typename Type, size_t Elements>
inline auto operator/(const Vector<Type, Elements>& lhs, Type rhs) -> Vector<Type, Elements> {
    return Divide(lhs, rhs);
}

template <typename Type, size_t Elements>
inline auto operator/(const Vector<Type, Elements>& lhs, const Vector<Type, Elements>& rhs) -> Vector<Type, Elements> {
    return Divide(lhs, rhs);
}
