namespace math::matrix::geometry {
    template <typename Type>
    inline auto Create(const Matrix<Type, 4, 4>& value,
                       const Matrix<Type, 4, 4>& model,
                       const Matrix<Type, 4, 4>& view,
                       const Matrix<Type, 4, 4>& projection) -> Matrix<Type, 4, 4> {
        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        result = math::matrix::Multiply(result, model);
        result = math::matrix::Multiply(result, view);
        result = math::matrix::Multiply(result, projection);

        return math::matrix::Multiply(value, result);
    }

    template <typename Type>
    inline auto Create(const Matrix<Type, 4, 4>& model, const Matrix<Type, 4, 4>& view, const Matrix<Type, 4, 4>& projection)
      -> Matrix<Type, 4, 4> {
        auto result = math::matrix::CreateIdentity<Type, 4, 4>();

        return math::matrix::geometry::Create(result, model, view, projection);
    }
} // namespace math::matrix::geometry
