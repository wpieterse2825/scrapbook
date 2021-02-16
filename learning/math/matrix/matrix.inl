template <typename Type, size_t Rows, size_t Columns>
inline auto ZeroMatrix() -> Matrix<Type, Rows, Columns> {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    auto result = Matrix<Type, Rows, Columns> {};

    for (auto row = size_t {0}; row < Rows; row++) {
        for (auto column = size_t {0}; column < Columns; column++) {
            result.elements[row][column] = zero_positive;
        }
    }

    return result;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto DiagonalMatrix(Type value) -> Matrix<Type, Rows, Columns> {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    auto result = Matrix<Type, Rows, Columns> {};

    for (auto row = size_t {0}; row < Rows; row++) {
        for (auto column = size_t {0}; column < Columns; column++) {
            if (row == column) {
                result.elements[row][column] = value;
            } else {
                result.elements[row][column] = zero_positive;
            }
        }
    }

    return result;
}

template <typename Type, size_t Elements>
inline auto DiagonalMatrix(const Vector<Type, Elements>& value) -> Matrix<Type, Elements, Elements> {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    auto result = Matrix<Type, Elements, Elements> {};

    for (auto row = size_t {0}; row < Elements; row++) {
        for (auto column = size_t {0}; column < Elements; column++) {
            if (row == column) {
                result.elements[row][column] = value.elements[row];
            } else {
                result.elements[row][column] = zero_positive;
            }
        }
    }

    return result;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto IdentityMatrix() -> Matrix<Type, Rows, Columns> {
    constexpr auto one_positive = Constants<Type>::OnePositive;

    return DiagonalMatrix<Type, Rows, Columns>(one_positive);
}

template <typename Type, size_t Rows, size_t Columns>
inline auto Compare(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Rows, Columns>& rhs, Type epsilon) -> bool {
    for (auto row = size_t {0}; row < Rows; row++) {
        for (auto column = size_t {0}; column < Columns; column++) {
            const auto lhs_value           = lhs.elements[row][column];
            const auto rhs_value           = rhs.elements[row][column];
            const auto difference          = lhs_value - rhs_value;
            const auto absolute_difference = Absolute(difference);

            if (absolute_difference > epsilon) {
                return false;
            }
        }
    }

    return true;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto Compare(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Columns, Rows>& rhs) -> bool {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    return Compare(lhs, rhs, zero_positive);
}

template <typename Type, size_t Rows, size_t Columns>
inline auto Negate(const Matrix<Type, Rows, Columns>& value) -> Matrix<Type, Rows, Columns> {
    auto result = Matrix<Type, Rows, Columns> {};

    for (auto row = size_t {0}; row < Rows; row++) {
        for (auto column = size_t {0}; column < Columns; column++) {
            result.elements[row][column] = -value.elements[row][column];
        }
    }

    return result;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto Plus(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Rows, Columns>& rhs) -> Matrix<Type, Rows, Columns> {
    auto result = Matrix<Type, Rows, Columns> {};

    for (auto row = size_t {0}; row < Rows; row++) {
        for (auto column = size_t {0}; column < Columns; column++) {
            const auto lhs_value = lhs.elements[row][column];
            const auto rhs_value = rhs.elements[row][column];
            const auto sum       = lhs_value + rhs_value;

            result.elements[row][column] = sum;
        }
    }

    return result;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto Minus(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Rows, Columns>& rhs) -> Matrix<Type, Rows, Columns> {
    auto result = Matrix<Type, Rows, Columns> {};

    for (auto row = size_t {0}; row < Rows; row++) {
        for (auto column = size_t {0}; column < Columns; column++) {
            const auto lhs_value = lhs.elements[row][column];
            const auto rhs_value = rhs.elements[row][column];
            const auto sum       = lhs_value - rhs_value;

            result.elements[row][column] = sum;
        }
    }

    return result;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto Multiply(const Matrix<Type, Rows, Columns>& lhs, Type rhs) -> Matrix<Type, Rows, Columns> {
    auto result = Matrix<Type, Rows, Columns> {};

    for (auto row = size_t {0}; row < Rows; row++) {
        for (auto column = size_t {0}; column < Columns; column++) {
            const auto lhs_value = lhs.elements[row][column];
            const auto rhs_value = rhs;
            const auto sum       = lhs_value * rhs_value;

            result.elements[row][column] = sum;
        }
    }

    return result;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto Multiply(const Matrix<Type, Rows, Columns>& lhs, const Vector<Type, Columns>& rhs) -> Vector<Type, Columns> {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    auto result = Vector<Type, Columns> {};

    for (auto row = size_t {0}; row < Rows; row++) {
        result.elements[row] = zero_positive;

        for (auto column = size_t {0}; column < Columns; column++) {
            const auto current_value = result.elements[row];
            const auto lhs_value     = lhs.elements[row][column];
            const auto rhs_value     = rhs.elements[column];
            const auto sum           = lhs_value * rhs_value;
            const auto result_value  = current_value + sum;

            result.elements[row] = result_value;
        }
    }

    return result;
}

template <typename Type, size_t LHSRows, size_t LHSColumns, size_t RHSRows, size_t RHSColumns>
inline auto Multiply(const Matrix<Type, LHSRows, LHSColumns>& lhs, const Matrix<Type, RHSRows, RHSColumns>& rhs)
  -> Matrix<Type, LHSRows, RHSColumns> {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    auto result = Matrix<Type, LHSRows, RHSColumns> {};

    static_assert(LHSRows == RHSColumns);

    for (auto lhs_rows = size_t {0}; lhs_rows < LHSRows; lhs_rows++) {
        for (auto rhs_columns = size_t {0}; rhs_columns < RHSColumns; rhs_columns++) {
            result.elements[lhs_rows][rhs_columns] = zero_positive;

            for (auto rhs_rows = size_t {0}; rhs_rows < RHSRows; rhs_rows++) {
                const auto current_value = result.elements[lhs_rows][rhs_columns];
                const auto lhs_value     = lhs.elements[lhs_rows][rhs_rows];
                const auto rhs_value     = rhs.elements[rhs_rows][rhs_columns];
                const auto sum           = lhs_value * rhs_value;
                const auto result_value  = current_value + sum;

                result.elements[lhs_rows][rhs_columns] = result_value;
            }
        }
    }

    return result;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto Transpose(const Matrix<Type, Rows, Columns>& value) -> Matrix<Type, Columns, Rows> {
    auto result = Matrix<Type, Columns, Rows> {};

    for (auto row = size_t {0}; row < Rows; row++) {
        for (auto column = size_t {0}; column < Columns; column++) {
            result.elemenets[column][row] = value.elements[row][column];
        }
    }

    return result;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto Inverse(const Matrix<Type, Rows, Columns>& value) -> Matrix<Type, Rows, Columns> {
    auto result = Matrix<Type, Rows, Columns> {};

    static_assert(Rows == Columns);

    // TODO(wpieterse): Implement me!

    return result;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto Determinant(const Matrix<Type, Rows, Columns>& value) -> Type {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    auto result = zero_positive;

    static_assert(Rows == Columns);

    // TODO(wpieterse): Implement me!

    return result;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto Trace(const Matrix<Type, Rows, Columns>& value) -> Type {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    auto result = zero_positive;

    static_assert(Rows == Columns);

    for (auto row = size_t {0}; row < Rows; row++) {
        for (auto column = size_t {0}; column < Columns; column++) {
            if (row == column) {
                result += value.elements[row][column];
            }
        }
    }

    return result;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto Difference(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Rows, Columns>& rhs) -> Type {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;
    constexpr auto one_negative  = Constants<Type>::OneNegative;

    auto result = one_negative;

    for (auto row = size_t {0}; row < Rows; row++) {
        for (auto column = size_t {0}; column < Columns; column++) {
            const auto lhs_value           = lhs.elements[row][column];
            const auto rhs_value           = rhs.elements[row][column];
            const auto difference          = lhs_value - rhs_value;
            const auto absolute_difference = Absolute(difference);

            if (result < zero_positive) {
                result = absolute_difference;
            }

            if (absolute_difference > result) {
                result = absolute_difference;
            }
        }
    }

    return result;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto Clamp(const Matrix<Type, Rows, Columns>& value, Type minimum, Type maximum) -> Matrix<Type, Rows, Columns> {
    auto result = Matrix<Type, Rows, Columns> {};

    for (auto row = size_t {0}; row < Rows; row++) {
        for (auto column = size_t {0}; column < Columns; column++) {
            const auto inner_value = value.elements[row][column];

            if (inner_value < minimum) {
                result.elements[row][column] = minimum;
            } else if (inner_value > maximum) {
                result.elements[row][column] = maximum;
            } else {
                result.elements[row][column] = inner_value;
            }
        }
    }

    return result;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto ClearLowerTriangle(const Matrix<Type, Rows, Columns>& value) -> Matrix<Type, Rows, Columns> {
    auto result = Matrix<Type, Rows, Columns> {};

    // TODO(wpieterse): Implement me!

    return result;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto ClearUpperTriangle(const Matrix<Type, Rows, Columns>& value) -> Matrix<Type, Rows, Columns> {
    auto result = Matrix<Type, Rows, Columns> {};

    // TODO(wpieterse): Implement me!

    return result;
}

template <size_t OutRows, size_t OutColumns, typename Type, size_t InRows, size_t InColumns>
inline auto ExtractSubMatrix(const Matrix<Type, InRows, InColumns>& value) -> Matrix<Type, OutRows, OutColumns> {
    auto result = Matrix<Type, OutRows, OutColumns> {};

    static_assert(OutRows <= InRows);
    static_assert(OutColumns <= InColumns);

    for (auto row = size_t {0}; row < OutRows; row++) {
        for (auto column = size_t {0}; column < OutColumns; column++) {
            result.elements[row][column] = value.elements[row][column];
        }
    }

    return result;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto RowToVector(const Matrix<Type, Rows, Columns>& value, size_t row) -> Vector<Type, Columns> {
    auto result = Vector<Type, Columns> {};

    // TODO(wpieterse): Implement me!

    return result;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto ColumnToVector(const Matrix<Type, Rows, Columns>& value, size_t column) -> Vector<Type, Rows> {
    auto result = Vector<Type, Rows> {};

    // TODO(wpieterse): Implement me!

    return result;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto IsZero(const Matrix<Type, Rows, Columns>& value, Type epsilon) -> bool {
    for (auto row = size_t {0}; row < Rows; row++) {
        for (auto column = size_t {0}; column < Columns; column++) {
            const auto inner_value    = value.elements[row][column];
            const auto absolute_value = Absolute(inner_value);

            if (absolute_value > epsilon) {
                return false;
            }
        }
    }

    return true;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto IsZero(const Matrix<Type, Rows, Columns>& value) -> bool {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    return IsZero(value, zero_positive);
}

template <typename Type, size_t Rows, size_t Columns>
inline auto IsDiagonal(const Matrix<Type, Rows, Columns>& value, Type epsilon) -> bool {
    // TODO(wpieterse): Simplify this.

    static_assert(Rows == Columns);

    for (auto row = size_t {0}; row < Rows; row++) {
        for (auto column = size_t {0}; column < Columns; column++) {
            if (row != column) {
                const auto inner_value    = value.elements[row][column];
                const auto absolute_value = Absolute(inner_value);

                if (absolute_value > epsilon) {
                    return false;
                }
            }
        }
    }

    return true;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto IsDiagonal(const Matrix<Type, Rows, Columns>& value) -> bool {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    return IsDiagonal(value, zero_positive);
}

template <typename Type, size_t Rows, size_t Columns>
inline auto IsIdentity(const Matrix<Type, Rows, Columns>& value, Type epsilon) -> bool {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;
    constexpr auto one_positive  = Constants<Type>::OnePositive;

    static_assert(Rows == Columns);

    for (auto row = size_t {0}; row < Rows; row++) {
        for (auto column = size_t {0}; column < Columns; column++) {
            const auto lhs_value = value.elements[row][column];
            auto       rhs_value = zero_positive;

            if (row == column) {
                rhs_value = one_positive;
            }

            const auto difference          = lhs_value - rhs_value;
            const auto absolute_difference = Absolute(difference);

            if (absolute_difference > epsilon) {
                return false;
            }
        }
    }

    return true;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto IsIdentity(const Matrix<Type, Rows, Columns>& value) -> bool {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    return IsIdentity(value, zero_positive);
}

template <typename Type, size_t Rows, size_t Columns>
inline auto IsSymmetric(const Matrix<Type, Rows, Columns>& value, Type epsilon) -> bool {
    constexpr auto RowsMinusTwo = Rows - 2;

    static_assert(Rows == Columns);

    for (auto row = size_t {0}; row < RowsMinusTwo; row++) {
        const auto initial_column = row + 2;

        for (auto column = initial_column; column < Columns; column++) {
            const auto left_value          = value.elements[row][column];
            const auto right_value         = value.elements[column][row];
            const auto difference          = left_value - right_value;
            const auto absolute_difference = Absolute(difference);

            if (absolute_difference > epsilon) {
                return false;
            }
        }
    }

    return true;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto IsSymmetric(const Matrix<Type, Rows, Columns>& value) -> bool {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    return IsSymmetric(value, zero_positive);
}

template <typename Type, size_t Rows, size_t Columns>
inline auto IsTriDiagonal(const Matrix<Type, Rows, Columns>& value, Type epsilon) -> bool {
    constexpr auto RowsMinusTwo = Rows - 2;

    static_assert(Rows == Columns);

    for (auto row = size_t {0}; row < RowsMinusTwo; row++) {
        const auto initial_column = row + 2;

        for (auto column = initial_column; column < Columns; column++) {
            const auto left_value          = value.elements[row][column];
            const auto absolute_left_value = Absolute(left_value);

            if (absolute_left_value > epsilon) {
                return false;
            }

            const auto right_value          = value.elements[column][row];
            const auto absolute_right_value = Absolute(right_value);

            if (absolute_right_value > epsilon) {
                return false;
            }
        }
    }

    return true;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto IsTriDiagonal(const Matrix<Type, Rows, Columns>& value) -> bool {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    return IsTriDiagonal(value, zero_positive);
}

template <typename Type, size_t Rows, size_t Columns>
inline auto Print(const Matrix<Type, Rows, Columns>& value) -> void {
    constexpr auto columns_minus_one = Columns - 1;

    for (auto row = size_t {0}; row < Rows; row++) {
        std::cout << "| ";

        for (auto column = size_t {0}; column < Columns; column++) {
            std::cout << value.elements[row][column];

            if (column < columns_minus_one) {
                std::cout << ", ";
            }
        }

        std::cout << " |";
        std::cout << std::endl;
    }
}

template <typename Type, size_t Rows, size_t Columns>
inline auto operator==(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Columns, Rows>& rhs) -> bool {
    const auto result = Compare(lhs, rhs);

    return result == true;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto operator!=(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Columns, Rows>& rhs) -> bool {
    const auto result = Compare(lhs, rhs);

    return result == false;
}

template <typename Type, size_t Rows, size_t Columns>
inline auto operator-(const Matrix<Type, Rows, Columns>& value) -> Matrix<Type, Rows, Columns> {
    return Negate(value);
}

template <typename Type, size_t Rows, size_t Columns>
inline auto operator+(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Rows, Columns>& rhs) -> Matrix<Type, Rows, Columns> {
    return Plus(lhs, rhs);
}

template <typename Type, size_t Rows, size_t Columns>
inline auto operator-(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Rows, Columns>& rhs) -> Matrix<Type, Rows, Columns> {
    return Minus(lhs, rhs);
}

template <typename Type, size_t Rows, size_t Columns>
inline auto operator*(const Matrix<Type, Rows, Columns>& lhs, Type rhs) -> Matrix<Type, Rows, Columns> {
    return Multiply(lhs, rhs);
}

template <typename Type, size_t Rows, size_t Columns>
inline auto operator*(Type lhs, const Matrix<Type, Rows, Columns>& rhs) -> Matrix<Type, Rows, Columns> {
    return Multiply(rhs, lhs);
}

template <typename Type, size_t Rows, size_t Columns>
inline auto operator*(const Matrix<Type, Rows, Columns>& lhs, const Vector<Type, Columns>& rhs) -> Vector<Type, Columns> {
    return Multiply(lhs, rhs);
}

template <typename Type, size_t Rows, size_t Columns>
inline auto operator*(const Vector<Type, Columns>& rhs, const Matrix<Type, Rows, Columns>& lhs) -> Vector<Type, Columns> {
    return Multiply(rhs, lhs);
}

template <typename Type, size_t LHSRows, size_t LHSColumns, size_t RHSRows, size_t RHSColumns>
inline auto operator*(const Matrix<Type, LHSRows, LHSColumns>& lhs, const Matrix<Type, RHSRows, RHSColumns>& rhs)
  -> Matrix<Type, LHSRows, RHSColumns> {
    return Multiply(lhs, rhs);
}
