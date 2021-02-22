enum class Side {
    On,
    Front,
    Back,
};

template <typename Type, size_t Dimensions>
concept SizedVector = requires(Type) {
    std::is_floating_point_v<Type>;
    Dimensions > 0;
};

template <typename Type, size_t Dimensions>
requires SizedVector<Type, Dimensions> struct Vector {
    Type elements[Dimensions];
};

template <typename Type, size_t Rows, size_t Columns>
concept SizedMatrix = requires(Type) {
    std::is_floating_point_v<Type>;
    Rows > 0;
    Columns > 0;
};

template <typename Type, size_t Rows, size_t Columns>
requires SizedMatrix<Type, Rows, Columns> struct Matrix {
    Type elements[Rows][Columns];
};

template <typename Type, size_t Dimensions>
concept SizedPlane = requires(Type) {
    std::is_floating_point_v<Type>;
    Dimensions > 0;
};

template <typename Type, size_t Dimensions>
requires SizedPlane<Type, Dimensions> struct Plane {
    Vector<Type, Dimensions> normal;
    Type                     distance;
};
