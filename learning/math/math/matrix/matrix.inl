namespace math::matrix {
    template <typename Type, size_t Rows, size_t Columns>
    inline auto Read(const Matrix<Type, Rows, Columns>& value, size_t row, size_t column) -> Type {
        assert(row < Rows);
        assert(column < Columns);

        return value.elements[row][column];
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Write(Matrix<Type, Rows, Columns>& value, size_t row, size_t column, Type inner_value) -> void {
        assert(row < Rows);
        assert(column < Columns);

        value.elements[row][column] = inner_value;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto CreateZero() -> Matrix<Type, Rows, Columns> {
        constexpr auto zero_positive = math::Constants<Type>::ZeroPositive;

        auto result = Matrix<Type, Rows, Columns> {};

        for (auto row = size_t {0}; row < Rows; row++) {
            for (auto column = size_t {0}; column < Columns; column++) {
                math::matrix::Write(result, row, column, zero_positive);
            }
        }

        return result;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto CreateDiagonal(Type value) -> Matrix<Type, Rows, Columns> {
        constexpr auto zero_positive = math::Constants<Type>::ZeroPositive;

        auto result = Matrix<Type, Rows, Columns> {};

        for (auto row = size_t {0}; row < Rows; row++) {
            for (auto column = size_t {0}; column < Columns; column++) {
                const auto is_diagonal = math::comparison::Equal(row, column);

                if (is_diagonal == true) {
                    math::matrix::Write(result, row, column, value);
                } else {
                    math::matrix::Write(result, row, column, zero_positive);
                }
            }
        }

        return result;
    }

    template <typename Type, size_t Elements>
    inline auto CreateDiagonal(const Vector<Type, Elements>& value) -> Matrix<Type, Elements, Elements> {
        constexpr auto zero_positive = math::Constants<Type>::ZeroPositive;

        auto result = Matrix<Type, Elements, Elements> {};

        for (auto row = size_t {0}; row < Elements; row++) {
            for (auto column = size_t {0}; column < Elements; column++) {
                const auto is_diagonal = math::comparison::Equal(row, column);

                if (is_diagonal == true) {
                    const auto inner_value = math::vector::Read(value, row);

                    math::matrix::Write(result, row, column, inner_value);
                } else {
                    math::matrix::Write(result, row, column, zero_positive);
                }
            }
        }

        return result;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto CreateIdentity() -> Matrix<Type, Rows, Columns> {
        constexpr auto one_positive = math::Constants<Type>::OnePositive;

        return math::matrix::CreateDiagonal<Type, Rows, Columns>(one_positive);
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Plus(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Rows, Columns>& rhs) -> Matrix<Type, Rows, Columns> {
        auto result = Matrix<Type, Rows, Columns> {};

        for (auto row = size_t {0}; row < Rows; row++) {
            for (auto column = size_t {0}; column < Columns; column++) {
                const auto lhs_value = math::matrix::Read(lhs, row, column);
                const auto rhs_value = math::matrix::Read(rhs, row, column);
                const auto sum       = math::arithmetic::Plus(lhs_value, rhs_value);

                math::matrix::Write(result, row, column, sum);
            }
        }

        return result;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Minus(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Rows, Columns>& rhs) -> Matrix<Type, Rows, Columns> {
        auto result = Matrix<Type, Rows, Columns> {};

        for (auto row = size_t {0}; row < Rows; row++) {
            for (auto column = size_t {0}; column < Columns; column++) {
                const auto lhs_value = math::matrix::Read(lhs, row, column);
                const auto rhs_value = math::matrix::Read(rhs, row, column);
                const auto sum       = math::arithmetic::Minus(lhs_value, rhs_value);

                math::matrix::Write(result, row, column, sum);
            }
        }

        return result;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Multiply(const Matrix<Type, Rows, Columns>& lhs, Type rhs) -> Matrix<Type, Rows, Columns> {
        auto result = Matrix<Type, Rows, Columns> {};

        for (auto row = size_t {0}; row < Rows; row++) {
            for (auto column = size_t {0}; column < Columns; column++) {
                const auto lhs_value = math::matrix::Read(lhs, row, column);
                const auto rhs_value = rhs;
                const auto sum       = math::arithmetic::Multiply(lhs_value, rhs_value);

                math::matrix::Write(result, row, column, sum);
            }
        }

        return result;
    }

    template <typename Type, size_t LHSRows, size_t LHSColumns, size_t RHSRows, size_t RHSColumns>
    inline auto Multiply(const Matrix<Type, LHSRows, LHSColumns>& lhs, const Matrix<Type, RHSRows, RHSColumns>& rhs)
      -> Matrix<Type, LHSRows, RHSColumns> {
        constexpr auto zero_positive = math::Constants<Type>::ZeroPositive;

        auto result = Matrix<Type, LHSRows, RHSColumns> {};

        static_assert(LHSRows == RHSColumns);

        for (auto lhs_rows = size_t {0}; lhs_rows < LHSRows; lhs_rows++) {
            for (auto rhs_columns = size_t {0}; rhs_columns < RHSColumns; rhs_columns++) {
                math::matrix::Write(result, lhs_rows, rhs_columns, zero_positive);

                for (auto rhs_rows = size_t {0}; rhs_rows < RHSRows; rhs_rows++) {
                    const auto current_value = math::matrix::Read(result, lhs_rows, rhs_columns);
                    const auto lhs_value     = math::matrix::Read(lhs, lhs_rows, rhs_rows);
                    const auto rhs_value     = math::matrix::Read(rhs, rhs_rows, rhs_columns);
                    const auto sum           = math::arithmetic::Multiply(lhs_value, rhs_value);
                    const auto result_value  = math::arithmetic::Plus(current_value, sum);

                    math::matrix::Write(result, lhs_rows, rhs_columns, result_value);
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
                const auto inner_value = math::matrix::Read(value, row, column);

                math::matrix::Write(result, column, row, inner_value);
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
    inline auto Negate(const Matrix<Type, Rows, Columns>& value) -> Matrix<Type, Rows, Columns> {
        auto result = Matrix<Type, Rows, Columns> {};

        for (auto row = size_t {0}; row < Rows; row++) {
            for (auto column = size_t {0}; column < Columns; column++) {
                const auto inner_value   = math::matrix::Read(value, row, column);
                const auto negated_value = math::arithmetic::Negate(inner_value);

                math::matrix::Write(result, row, column, negated_value);
            }
        }

        return result;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Clamp(const Matrix<Type, Rows, Columns>& value, Type minimum, Type maximum) -> Matrix<Type, Rows, Columns> {
        auto result = Matrix<Type, Rows, Columns> {};

        for (auto row = size_t {0}; row < Rows; row++) {
            for (auto column = size_t {0}; column < Columns; column++) {
                const auto inner_value             = math::matrix::Read(value, row, column);
                const auto is_less_than_minimum    = math::comparison::LessThan(inner_value, minimum);
                const auto is_greater_than_maximum = math::comparison::GreaterThan(inner_value, maximum);

                if (is_less_than_minimum == true) {
                    math::matrix::Write(result, row, column, minimum);
                } else if (is_greater_than_maximum == true) {
                    math::matrix::Write(result, row, column, maximum);
                } else {
                    math::matrix::Write(result, row, column, inner_value);
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
                const auto inner_value = math::matrix::Read(value, row, column);

                math::matrix::Write(result, row, column, inner_value);
            }
        }

        return result;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Difference(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Rows, Columns>& rhs) -> Type {
        constexpr auto zero_positive = math::Constants<Type>::ZeroPositive;
        constexpr auto one_negative  = math::Constants<Type>::OneNegative;

        auto result = one_negative;

        for (auto row = size_t {0}; row < Rows; row++) {
            for (auto column = size_t {0}; column < Columns; column++) {
                const auto lhs_value              = math::matrix::Read(lhs, row, column);
                const auto rhs_value              = math::matrix::Read(rhs, row, column);
                const auto difference             = math::arithmetic::Minus(lhs_value, rhs_value);
                const auto absolute_difference    = math::mapping::Absolute(difference);
                const auto is_less_than_zero      = math::comparison::LessThan(result, zero_positive);
                const auto is_greater_than_result = math::comparison::GreaterThan(absolute_difference, result);

                if (is_less_than_zero == true) {
                    result = absolute_difference;
                }

                if (is_greater_than_result == true) {
                    result = absolute_difference;
                }
            }
        }

        return result;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Trace(const Matrix<Type, Rows, Columns>& value) -> Type {
        constexpr auto zero_positive = math::Constants<Type>::ZeroPositive;

        auto result = zero_positive;

        static_assert(Rows == Columns);

        for (auto row = size_t {0}; row < Rows; row++) {
            for (auto column = size_t {0}; column < Columns; column++) {
                const auto is_diagonal = math::comparison::Equal(row, column);

                if (is_diagonal == true) {
                    const auto inner_value = math::matrix::Read(value, row, column);

                    result = math::arithmetic::Plus(result, inner_value);
                }
            }
        }

        return result;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Determinant(const Matrix<Type, Rows, Columns>& value) -> Type {
        constexpr auto zero_positive = math::Constants<Type>::ZeroPositive;

        auto result = zero_positive;

        static_assert(Rows == Columns);

        // TODO(wpieterse): Implement me!

        return result;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Compare(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Rows, Columns>& rhs, Type epsilon) -> bool {
        for (auto row = size_t {0}; row < Rows; row++) {
            for (auto column = size_t {0}; column < Columns; column++) {
                const auto lhs_value = math::matrix::Read(lhs, row, column);
                const auto rhs_value = math::matrix::Read(rhs, row, column);
                const auto is_same   = math::comparison::Compare(lhs_value, rhs_value, epsilon);

                if (is_same == false) {
                    return false;
                }
            }
        }

        return true;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Compare(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Columns, Rows>& rhs) -> bool {
        constexpr auto zero_positive = math::Constants<Type>::ZeroPositive;

        return math::matrix::Compare(lhs, rhs, zero_positive);
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Equal(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Columns, Rows>& rhs, Type epsilon) -> bool {
        const auto result = math::matrix::Compare(lhs, rhs, epsilon);

        return result == true;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto NotEqual(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Columns, Rows>& rhs, Type epsilon) -> bool {
        const auto result = math::matrix::Compare(lhs, rhs, epsilon);

        return result == false;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Equal(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Columns, Rows>& rhs) -> bool {
        const auto result = math::matrix::Compare(lhs, rhs);

        return result == true;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto NotEqual(const Matrix<Type, Rows, Columns>& lhs, const Matrix<Type, Columns, Rows>& rhs) -> bool {
        const auto result = math::matrix::Compare(lhs, rhs);

        return result == false;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsZero(const Matrix<Type, Rows, Columns>& value, Type epsilon) -> bool {
        // TODO(wpieterse): Simplify this.

        for (auto row = size_t {0}; row < Rows; row++) {
            for (auto column = size_t {0}; column < Columns; column++) {
                const auto inner_value    = math::matrix::Read(value, row, column);
                const auto absolute_value = math::mapping::Absolute(inner_value);
                const auto is_not_zero    = math::comparison::GreaterThan(absolute_value, epsilon);

                if (is_not_zero == true) {
                    return false;
                }
            }
        }

        return true;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsZero(const Matrix<Type, Rows, Columns>& value) -> bool {
        constexpr auto zero_positive = math::Constants<Type>::ZeroPositive;

        return math::matrix::IsZero(value, zero_positive);
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsDiagonal(const Matrix<Type, Rows, Columns>& value, Type epsilon) -> bool {
        // TODO(wpieterse): Simplify this.

        static_assert(Rows == Columns);

        for (auto row = size_t {0}; row < Rows; row++) {
            for (auto column = size_t {0}; column < Columns; column++) {
                const auto is_diagonal = math::comparison::Equal(row, column);

                if (is_diagonal == false) {
                    const auto inner_value    = math::matrix::Read(value, row, column);
                    const auto absolute_value = math::mapping::Absolute(inner_value);
                    const auto is_not_zero    = math::comparison::GreaterThan(absolute_value, epsilon);

                    if (is_not_zero == true) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsDiagonal(const Matrix<Type, Rows, Columns>& value) -> bool {
        constexpr auto zero_positive = math::Constants<Type>::ZeroPositive;

        return math::matrix::IsDiagonal(value, zero_positive);
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsIdentity(const Matrix<Type, Rows, Columns>& value, Type epsilon) -> bool {
        constexpr auto zero_positive = math::Constants<Type>::ZeroPositive;
        constexpr auto one_positive  = math::Constants<Type>::OnePositive;

        static_assert(Rows == Columns);

        for (auto row = size_t {0}; row < Rows; row++) {
            for (auto column = size_t {0}; column < Columns; column++) {
                const auto lhs_value   = math::matrix::Read(value, row, column);
                const auto is_diagonal = math::comparison::Equal(row, column);
                auto       rhs_value   = zero_positive;

                if (is_diagonal == true) {
                    rhs_value = one_positive;
                }

                const auto is_correct = math::comparison::Compare(lhs_value, rhs_value, epsilon);

                if (is_correct == false) {
                    return false;
                }
            }
        }

        return true;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsIdentity(const Matrix<Type, Rows, Columns>& value) -> bool {
        constexpr auto zero_positive = math::Constants<Type>::ZeroPositive;

        return math::matrix::IsIdentity(value, zero_positive);
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsTriDiagonal(const Matrix<Type, Rows, Columns>& value, Type epsilon) -> bool {
        // TODO(wpieterse): Simplify this.

        constexpr auto RowsMinusTwo = Rows - 2;

        static_assert(Rows == Columns);

        for (auto row = size_t {0}; row < RowsMinusTwo; row++) {
            const auto initial_column = row + 2;

            for (auto column = initial_column; column < Columns; column++) {
                const auto left_value          = math::matrix::Read(value, row, column);
                const auto absolute_left_value = math::mapping::Absolute(left_value);
                const auto is_left_not_zero    = math::comparison::GreaterThan(absolute_left_value, epsilon);

                if (is_left_not_zero == true) {
                    return false;
                }

                const auto right_value          = math::matrix::Read(value, column, row);
                const auto absolute_right_value = math::mapping::Absolute(right_value);
                const auto is_right_not_zero    = math::comparison::GreaterThan(absolute_right_value, epsilon);

                if (is_right_not_zero == true) {
                    return false;
                }
            }
        }

        return true;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsTriDiagonal(const Matrix<Type, Rows, Columns>& value) -> bool {
        constexpr auto zero_positive = math::Constants<Type>::ZeroPositive;

        return math::matrix::IsTriDiagonal(value, zero_positive);
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsSymmetric(const Matrix<Type, Rows, Columns>& value, Type epsilon) -> bool {
        constexpr auto RowsMinusTwo = Rows - 2;

        static_assert(Rows == Columns);

        for (auto row = size_t {0}; row < RowsMinusTwo; row++) {
            const auto initial_column = row + 2;

            for (auto column = initial_column; column < Columns; column++) {
                const auto left_value  = math::matrix::Read(value, row, column);
                const auto right_value = math::matrix::Read(value, column, row);
                const auto is_same     = math::comparison::Compare(left_value, right_value, epsilon);

                if (is_same == false) {
                    return false;
                }
            }
        }

        return true;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto IsSymmetric(const Matrix<Type, Rows, Columns>& value) -> bool {
        constexpr auto zero_positive = math::Constants<Type>::ZeroPositive;

        return math::matrix::IsSymmetric(value, zero_positive);
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
    inline auto Multiply(const Matrix<Type, Rows, Columns>& lhs, const Vector<Type, Columns>& rhs) -> Vector<Type, Columns> {
        constexpr auto zero_positive = math::Constants<Type>::ZeroPositive;

        auto result = Vector<Type, Columns> {};

        for (auto row = size_t {0}; row < Rows; row++) {
            math::vector::Write(result, row, zero_positive);

            for (auto column = size_t {0}; column < Columns; column++) {
                const auto current_value = math::vector::Read(result, row);
                const auto lhs_value     = math::matrix::Read(lhs, row, column);
                const auto rhs_value     = math::vector::Read(rhs, column);
                const auto sum           = math::arithmetic::Multiply(lhs_value, rhs_value);
                const auto result_value  = math::arithmetic::Plus(current_value, sum);

                math::vector::Write(result, row, result_value);
            }
        }

        return result;
    }

    template <typename Type, size_t Rows, size_t Columns>
    inline auto Print(const Matrix<Type, Rows, Columns>& value) -> void {
        constexpr auto columns_minus_one = Columns - 1;

        for (auto row = size_t {0}; row < Rows; row++) {
            std::cout << "| ";

            for (auto column = size_t {0}; column < Columns; column++) {
                const auto can_print_comma = math::comparison::LessThan(column, columns_minus_one);
                const auto inner_value     = math::matrix::Read(value, row, column);

                std::cout << inner_value;
                if (can_print_comma == true) {
                    std::cout << ", ";
                }
            }

            std::cout << " |";
            std::cout << std::endl;
        }
    }
} // namespace math::matrix
