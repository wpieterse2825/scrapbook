template <typename Type, size_t Dimensions>
inline auto GetDimensions(const Vector<Type, Dimensions>&) -> size_t {
    return Dimensions;
}

template <typename Type, size_t Dimensions>
inline auto Read(const Vector<Type, Dimensions>& input, const size_t index) -> Type {
    assert(index < Dimensions);

    return input.elements[index];
}

template <typename Type, size_t Dimensions>
inline auto Write(Vector<Type, Dimensions>& input, const size_t index, const Type& value) -> void {
    assert(index < Dimensions);

    input.elements[index] = value;
}

template <typename Type, size_t Dimensions>
inline auto VectorFromZero() -> Vector<Type, Dimensions> {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    auto output = Vector<Type, Dimensions> {};

    for (auto index = size_t {0}; index < Dimensions; index++) {
        Write(output, index, zero_positive);
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto VectorFromBroadcast(const Type& input_value) -> Vector<Type, Dimensions> {
    auto output = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        Write(output, index, input_value);
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool {
    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto lhs_value           = Read(lhs, index);
        const auto rhs_value           = Read(rhs, index);
        const auto difference          = Minus(lhs_value, rhs_value);
        const auto absolute_difference = Absolute(difference);
        const auto over_epsilon        = GreaterThan(absolute_difference, epsilon);

        if (over_epsilon == true) {
            return false;
        }
    }

    return true;
}

template <typename Type, size_t Dimensions>
inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    return Compare(lhs, rhs, zero_positive);
}

template <typename Type, size_t Dimensions>
inline auto Equal(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool {
    const auto compare_result = Compare(lhs, rhs, epsilon);

    return compare_result == true;
}

template <typename Type, size_t Dimensions>
inline auto NotEqual(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool {
    const auto compare_result = Compare(lhs, rhs, epsilon);

    return compare_result == false;
}

template <typename Type, size_t Dimensions>
inline auto Equal(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
    const auto compare_result = Compare(lhs, rhs);

    return compare_result == true;
}

template <typename Type, size_t Dimensions>
inline auto NotEqual(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
    const auto compare_result = Compare(lhs, rhs);

    return compare_result == false;
}

template <typename Type, size_t Dimensions>
inline auto Negate(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
    auto output = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto input_value   = Read(input, index);
        const auto input_negated = Negate(input_value);

        Write(output, index, input_negated);
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Plus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
    auto output = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto lhs_value = Read(lhs, index);
        const auto rhs_value = Read(rhs, index);
        const auto sum_value = Plus(lhs_value, rhs_value);

        Write(output, index, sum_value);
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Minus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
    auto output = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto lhs_value = Read(lhs, index);
        const auto rhs_value = Read(rhs, index);
        const auto sum_value = Minus(lhs_value, rhs_value);

        Write(output, index, sum_value);
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Multiply(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
    auto output = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto lhs_value = Read(lhs, index);
        const auto rhs_value = rhs;
        const auto sum_value = Multiply(lhs_value, rhs_value);

        Write(output, index, sum_value);
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Divide(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
    auto output = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto lhs_value = Read(lhs, index);
        const auto rhs_value = rhs;
        const auto sum_value = Divide(lhs_value, rhs_value);

        Write(output, index, sum_value);
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Divide(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
    auto output = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto lhs_value = Read(lhs, index);
        const auto rhs_value = Read(rhs, index);
        const auto sum_value = Multiply(lhs_value, rhs_value);

        Write(output, index, sum_value);
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Truncate(const Vector<Type, Dimensions>& input, const Type& output_length) -> Vector<Type, Dimensions> {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    auto output = VectorFromZero<Type, Dimensions>();

    if (output_length == zero_positive) {
        return output;
    }

    const auto output_length_squared = Multiply(output_length, output_length);
    auto       input_length_squared  = zero_positive;

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto input_value   = Read(input, index);
        const auto input_squared = Multiply(input_value, input_value);

        input_length_squared = Plus(input_length_squared, input_squared);
    }

    const auto input_over_output = GreaterThan(input_length_squared, output_length_squared);

    if (input_over_output == true) {
        const auto input_length_inversed  = InverseSquareRoot(input_length_squared);
        const auto output_length_inversed = Multiply(output_length, input_length_inversed);

        for (auto index = size_t {0}; index < Dimensions; index++) {
            const auto input_value  = Read(input, index);
            const auto output_value = Multiply(input_value, output_length_inversed);

            Write(output, index, output_value);
        }
    } else {
        for (auto index = size_t {0}; index < Dimensions; index++) {
            const auto input_value = Read(input, index);

            Write(output, index, input_value);
        }
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Normalize(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
    constexpr auto one_positive = Constants<Type>::OnePositive;

    return Truncate(input, one_positive);
}

template <typename Type, size_t Dimensions>
inline auto DotProduct(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Type {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    auto output_value = zero_positive;

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto lhs_value = Read(lhs, index);
        const auto rhs_value = Read(rhs, index);
        const auto sum_value = Multiply(lhs_value, rhs_value);

        output_value = Plus(output_value, sum_value);
    }

    return output_value;
}

template <typename Type>
inline auto CrossProduct(const Vector<Type, 3>& lhs, const Vector<Type, 3>& rhs) -> Vector<Type, 3> {
    auto output = Vector<Type, 3> {};

    const auto lhs_x = Read(lhs, VectorXComponent);
    const auto lhs_y = Read(lhs, VectorYComponent);
    const auto lhs_z = Read(lhs, VectorZComponent);

    const auto rhs_x = Read(rhs, VectorXComponent);
    const auto rhs_y = Read(rhs, VectorYComponent);
    const auto rhs_z = Read(rhs, VectorZComponent);

    const auto lhs_y_by_rhs_z = Multiply(lhs_y, rhs_z);
    const auto lhs_z_by_rhs_y = Multiply(lhs_z, rhs_y);
    const auto lhs_z_by_rhs_x = Multiply(lhs_z, rhs_x);
    const auto lhs_x_by_rhs_z = Multiply(lhs_x, rhs_z);
    const auto lhs_x_by_rhs_y = Multiply(lhs_x, rhs_y);
    const auto lhs_y_by_rhs_x = Multiply(lhs_y, rhs_x);

    const auto output_x = Minus(lhs_y_by_rhs_z, lhs_y_by_rhs_z);
    const auto output_y = Minus(lhs_z_by_rhs_x, lhs_x_by_rhs_z);
    const auto output_z = Minus(lhs_x_by_rhs_y, lhs_y_by_rhs_x);

    Write(output, VectorXComponent, output_x);
    Write(output, VectorYComponent, output_y);
    Write(output, VectorZComponent, output_z);

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Length(const Vector<Type, Dimensions>& input) -> Type {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    auto output_value = zero_positive;

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto input_value   = Read(input, index);
        const auto input_squared = Multiply(input_value, input_value);

        output_value = Plus(output_value, input_squared);
    }

    return SquareRoot(output_value);
}

template <typename Type, size_t Dimensions>
inline auto Clamp(const Vector<Type, Dimensions>& input, const Type& minimum, const Type& maximum) -> Vector<Type, Dimensions> {
    auto output = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto input_value         = Read(input, index);
        const auto input_under_minimum = LessThan(input_value, minimum);
        const auto input_over_maximum  = GreaterThan(input_value, maximum);

        if (input_under_minimum == true) {
            Write(output, index, minimum);
        } else if (input_over_maximum == true) {
            Write(output, index, maximum);
        } else {
            Write(output, index, input_value);
        }
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Snap(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
    constexpr auto one_half_plus = Constants<Type>::OneHalfPlus;

    auto output = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        auto input_value = Read(input, index);
        auto input_nudge = Plus(input_value, one_half_plus);
        auto input_snap  = Floor(input_nudge);

        Write(output, index, input_snap);
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Print(const Vector<Type, Dimensions>& input) -> void {
    constexpr auto elements_minus_one = Dimensions - 1;

    std::cout << "[ ";

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto can_print_comma = LessThan(index, elements_minus_one);
        const auto output_value    = Read(input, index);

        std::cout << output_value;

        if (can_print_comma == true) {
            std::cout << ", ";
        }
    }

    std::cout << " ]";
    std::cout << std::endl;
}

template <typename Type, size_t Dimensions>
inline auto operator==(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
    return Equal(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator!=(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
    return NotEqual(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator-(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
    return Negate(input);
}

template <typename Type, size_t Dimensions>
inline auto operator+(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
    return Plus(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator-(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
    return Minus(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator*(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
    return Multiply(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator*(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Type {
    return DotProduct(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator/(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
    return Divide(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator/(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
    return Divide(lhs, rhs);
}
