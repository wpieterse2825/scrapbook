#include <assert.h>
#include <math.h>

#include <iostream>

#include "learning/math/math/math.hpp"

#include "learning/math/math/math.inl"
#include "learning/math/math/vector/vector.inl"
// #include "learning/math/math/matrix/matrix.inl"
// #include "learning/math/math/matrix/geometry/model_space.inl"
// #include "learning/math/math/matrix/geometry/view_space.inl"
// #include "learning/math/math/matrix/geometry/orthographic_projection.inl"
#include "learning/math/math/plane/plane.inl"

int main() {
    // auto model      = ModelMatrixGenerate(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    // auto view       = ViewMatrixGenerate(0.0, 0.0, 1920.0, 1080.0);
    // auto projection = OrthographicMatrixGenerate(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
    // auto mvp        = model * view * projection;

    auto vector = VectorFromZero<double, 3>();
    Write(vector, VectorYComponent, -254.0);

    auto plane = PlaneFromZero<double, 3>();
    WriteDistance(plane, 256.0);
    WriteNormal(plane, VectorYComponent, -1.0);

    Print(vector);
    Print(plane);

    auto side = PointSide(plane, vector);
    switch (side) {
        case Side::On:
            std::cout << "ON" << std::endl;
            break;
        case Side::Front:
            std::cout << "FRONT" << std::endl;
            break;
        case Side::Back:
            std::cout << "BACK" << std::endl;
            break;
    }

    auto type = AxialType(plane);
    switch (type) {
        case PlaneType::PositiveX:
            std::cout << "Positive - X" << std::endl;
            break;
        case PlaneType::PositiveY:
            std::cout << "Positive - Y" << std::endl;
            break;
        case PlaneType::PositiveZ:
            std::cout << "Positive - Z" << std::endl;
            break;
        case PlaneType::NegativeX:
            std::cout << "Negative - X" << std::endl;
            break;
        case PlaneType::NegativeY:
            std::cout << "Negative - Y" << std::endl;
            break;
        case PlaneType::NegativeZ:
            std::cout << "Negative - Z" << std::endl;
            break;
        case PlaneType::ZeroX:
            std::cout << "Zero - X" << std::endl;
            break;
        case PlaneType::ZeroY:
            std::cout << "Zero - Y" << std::endl;
            break;
        case PlaneType::ZeroZ:
            std::cout << "Zero - Z" << std::endl;
            break;
        case PlaneType::NonAxial:
            std::cout << "Non-Axial" << std::endl;
            break;
    }

    return 0;
}
