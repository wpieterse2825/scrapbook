template <typename Type, size_t Dimensions>
inline auto GetDimensions(const Plane<Type, Dimensions>&) -> size_t {
    return Dimensions;
}

template <typename Type, size_t Dimensions>
inline auto GetNormal(const Plane<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
    return input.normal;
}

template <typename Type, size_t Dimensions>
inline auto GetDistance(const Plane<Type, Dimensions>& input) -> Type {
    return input.distance;
}

template <typename Type, size_t Dimensions>
inline auto ReadNormal(const Plane<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
    return GetNormal(input);
}

template <typename Type, size_t Dimensions>
inline auto ReadNormal(const Plane<Type, Dimensions>& input, size_t index) -> Type {
    return Read(input.normal, index);
}

template <typename Type, size_t Dimensions>
inline auto WriteNormal(Plane<Type, Dimensions>& output, const Vector<Type, Dimensions>& input) -> void {
    output.normal = input;
}

template <typename Type, size_t Dimensions>
inline auto WriteNormal(Plane<Type, Dimensions>& output, size_t index, const Type& input) -> void {
    Write(output.normal, index, input);
}

template <typename Type, size_t Dimensions>
inline auto ReadDistance(const Plane<Type, Dimensions>& input) -> Type {
    return input.distance;
}

template <typename Type, size_t Dimensions>
inline auto WriteDistance(Plane<Type, Dimensions>& output, const Type& input) -> void {
    output.distance = input;
}

template <typename Type, size_t Dimensions>
inline auto PlaneFromZero() -> Plane<Type, Dimensions> {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    auto output = Plane<Type, Dimensions> {};

    const auto zero_vector = VectorFromZero<Type, Dimensions>();

    WriteNormal(output, zero_vector);
    WriteDistance(output, zero_positive);

    return output;
}

template <typename Type, size_t Dimensions>
inline auto PlaneFromParameters(const Vector<Type, Dimensions>& input_normal, Type input_distance) -> Plane<Type, Dimensions> {
    auto output = PlaneFromZero<Type, Dimensions>();

    WriteNormal(output, input_normal);
    WriteDistance(output, input_distance);

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Compare(const Plane<Type, Dimensions>& lhs, const Plane<Type, Dimensions>& rhs, Type normal_epsilon, Type distance_epsilon)
  -> bool {
    const auto lhs_normal   = GetNormal(lhs);
    const auto rhs_normal   = GetNormal(rhs);
    const auto lhs_distance = GetDistance(lhs);
    const auto rhs_distance = GetDistance(rhs);

    const auto equal_normal = Equal(lhs_normal, rhs_normal, normal_epsilon);
    if (equal_normal == false) {
        return false;
    }

    const auto distance_difference = Minus(lhs_distance, rhs_distance);
    const auto distance_absolute   = Absolute(distance_difference);
    const auto distance_inside     = LessThan(distance_absolute, distance_epsilon);
    if (distance_inside == false) {
        return false;
    }

    return true;
}

template <typename Type, size_t Dimensions>
inline auto Compare(const Plane<Type, Dimensions>& lhs, const Plane<Type, Dimensions>& rhs, Type epsilon) -> bool {
    return Compare(lhs, rhs, epsilon, epsilon);
}

template <typename Type, size_t Dimensions>
inline auto Compare(const Plane<Type, Dimensions>& lhs, const Plane<Type, Dimensions>& rhs) -> bool {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    return Compare(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto Equal(const Plane<Type, Dimensions>& lhs, const Plane<Type, Dimensions>& rhs, Type normal_epsilon, Type distance_epsilon)
  -> bool {
    const auto compare_result = Compare(lhs, rhs, normal_epsilon, distance_epsilon);

    return compare_result == true;
}

template <typename Type, size_t Dimensions>
inline auto NotEqual(const Plane<Type, Dimensions>& lhs, const Plane<Type, Dimensions>& rhs, Type normal_epsilon, Type distance_epsilon)
  -> bool {
    const auto compare_result = Compare(lhs, rhs, normal_epsilon, distance_epsilon);

    return compare_result == false;
}

template <typename Type, size_t Dimensions>
inline auto Equal(const Plane<Type, Dimensions>& lhs, const Plane<Type, Dimensions>& rhs, Type epsilon) -> bool {
    const auto compare_result = Compare(lhs, rhs, epsilon);

    return compare_result == true;
}

template <typename Type, size_t Dimensions>
inline auto NotEqual(const Plane<Type, Dimensions>& lhs, const Plane<Type, Dimensions>& rhs, Type epsilon) -> bool {
    const auto compare_result = Compare(lhs, rhs, epsilon);

    return compare_result == true;
}

template <typename Type, size_t Dimensions>
inline auto Equal(const Plane<Type, Dimensions>& lhs, const Plane<Type, Dimensions>& rhs) -> bool {
    const auto compare_result = Compare(lhs, rhs);

    return compare_result == true;
}

template <typename Type, size_t Dimensions>
inline auto NotEqual(const Plane<Type, Dimensions>& lhs, const Plane<Type, Dimensions>& rhs) -> bool {
    const auto compare_result = Compare(lhs, rhs);

    return compare_result == true;
}

template <typename Type, size_t Dimensions>
inline auto Negate(const Plane<Type, Dimensions>& input) -> Plane<Type, Dimensions> {
    auto output = PlaneFromZero<Type, Dimensions>();

    const auto input_normal   = GetNormal(input);
    const auto input_distance = GetDistance(input);

    const auto normal_negated   = Negate(input_normal);
    const auto distance_negated = Negate(input_distance);

    output.normal   = normal_negated;
    output.distance = distance_negated;

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Plus(const Plane<Type, Dimensions>& lhs, const Plane<Type, Dimensions>& rhs) -> Plane<Type, Dimensions> {
    auto output = PlaneFromZero<Type, Dimensions>();

    auto lhs_normal   = GetNormal(lhs);
    auto rhs_normal   = GetNormal(rhs);
    auto lhs_distance = GetDistance(lhs);
    auto rhs_distance = GetDistance(rhs);

    auto normal_sum   = Plus(lhs_normal, rhs_normal);
    auto distance_sum = Plus(lhs_distance, rhs_distance);

    output.normal   = normal_sum;
    output.distance = distance_sum;

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Minus(const Plane<Type, Dimensions>& lhs, const Plane<Type, Dimensions>& rhs) -> Plane<Type, Dimensions> {
    auto output = PlaneFromZero<Type, Dimensions>();

    auto lhs_normal   = GetNormal(lhs);
    auto rhs_normal   = GetNormal(rhs);
    auto lhs_distance = GetDistance(lhs);
    auto rhs_distance = GetDistance(rhs);

    auto normal_sum   = Minus(lhs_normal, rhs_normal);
    auto distance_sum = Minus(lhs_distance, rhs_distance);

    output.normal   = normal_sum;
    output.distance = distance_sum;

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Normalize(const Plane<Type, Dimensions>& input) -> Plane<Type, Dimensions> {
    auto output = PlaneFromZero<Type, Dimensions>();

    auto input_normal   = GetNormal(input);
    auto input_distance = GetDistance(input);

    auto normalized_normal = Normalize(input_normal);

    output.normal   = normalized_normal;
    output.distance = input_distance;

    return output;
}

template <typename Type, size_t Dimensions>
inline auto PointDistance(const Plane<Type, Dimensions>& input_plane, const Vector<Type, Dimensions>& input_vector) -> Type {
    const auto input_normal   = GetNormal(input_plane);
    const auto input_distance = GetDistance(input_plane);

    const auto normal_dot_vector = DotProduct(input_normal, input_vector);
    const auto dot_distance      = Plus(normal_dot_vector, input_distance);

    return dot_distance;
}

template <typename Type, size_t Dimensions>
inline auto PointSide(const Plane<Type, Dimensions>& input_plane, const Vector<Type, Dimensions>& input_vector, Type epsilon) -> Side {
    const auto distance      = PointDistance(input_plane, input_vector);
    const auto over_epsilon  = GreaterThan(distance, epsilon);
    const auto under_epsilon = LessThan(distance, epsilon);

    if (over_epsilon == true) {
        return Side::Front;
    } else if (under_epsilon == true) {
        return Side::Back;
    }

    return Side::On;
}

template <typename Type, size_t Dimensions>
inline auto PointSide(const Plane<Type, Dimensions>& input_plane, const Vector<Type, Dimensions>& input_vector) -> Side {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    return PointSide(input_plane, input_vector, zero_positive);
}

template <typename Type>
inline auto AxialType(const Plane<Type, 3>& input) -> PlaneType {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    const auto input_normal   = GetNormal(input);
    const auto input_normal_x = Read(input_normal, VectorXComponent);
    const auto input_normal_y = Read(input_normal, VectorYComponent);
    const auto input_normal_z = Read(input_normal, VectorZComponent);

    const auto is_normal_x_zero = Equal(input_normal_x, zero_positive);
    const auto is_normal_y_zero = Equal(input_normal_y, zero_positive);
    const auto is_normal_z_zero = Equal(input_normal_z, zero_positive);

    const auto is_normal_x_above_zero = GreaterThan(input_normal_x, zero_positive);
    const auto is_normal_y_above_zero = GreaterThan(input_normal_y, zero_positive);
    const auto is_normal_z_above_zero = GreaterThan(input_normal_z, zero_positive);

    if (is_normal_x_zero == true) {
        if (is_normal_y_zero == true) {
            if (is_normal_z_above_zero == true) {
                return PlaneType::PositiveZ;
            } else {
                return PlaneType::NegativeZ;
            }
        } else if (is_normal_z_zero == true) {
            if (is_normal_y_above_zero == true) {
                return PlaneType::PositiveY;
            } else {
                return PlaneType::NegativeY;
            }
        } else {
            return PlaneType::ZeroX;
        }
    } else if (is_normal_y_zero == true) {
        if (is_normal_z_zero == true) {
            if (is_normal_x_above_zero == true) {
                return PlaneType::PositiveX;
            } else {
                return PlaneType::NegativeX;
            }
        } else {
            return PlaneType::ZeroY;
        }
    } else if (is_normal_z_zero == true) {
        return PlaneType::ZeroZ;
    }

    return PlaneType::NonAxial;
}

template <typename Type, size_t Dimensions>
inline auto Print(const Plane<Type, Dimensions>& input) -> void {
    const auto input_normal   = GetNormal(input);
    const auto input_distance = GetDistance(input);

    std::cout << " * " << input_distance << " - ";

    Print(input_normal);
}

template <typename Type, size_t Dimensions>
inline auto operator==(const Plane<Type, Dimensions>& lhs, const Plane<Type, Dimensions>& rhs) -> bool {
    return Equal(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator!=(const Plane<Type, Dimensions>& lhs, const Plane<Type, Dimensions>& rhs) -> bool {
    return NotEqual(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator-(const Plane<Type, Dimensions>& input) -> Plane<Type, Dimensions> {
    return Negate(input);
}

template <typename Type, size_t Dimensions>
inline auto operator+(const Plane<Type, Dimensions>& lhs, const Plane<Type, Dimensions>& rhs) -> Plane<Type, Dimensions> {
    return Plus(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator-(const Plane<Type, Dimensions>& lhs, const Plane<Type, Dimensions>& rhs) -> Plane<Type, Dimensions> {
    return Minus(lhs, rhs);
}
