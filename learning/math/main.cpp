#include <assert.h>
#include <math.h>

#include <iostream>

#include "learning/math/math/math.hpp"

#include "learning/math/math/arithmetic/arithmetic.inl"
#include "learning/math/math/comparison/comparison.inl"
#include "learning/math/math/mapping/mapping.inl"
#include "learning/math/math/trigonometry/trigonometry.inl"
#include "learning/math/math/trigonometry/radians/radians.inl"
#include "learning/math/math/trigonometry/degrees/degrees.inl"
#include "learning/math/math/vector/vector.inl"
#include "learning/math/math/matrix/matrix.inl"
#include "learning/math/math/matrix/geometry/geometry.inl"
#include "learning/math/math/matrix/geometry/model_space/model_space.inl"
#include "learning/math/math/matrix/geometry/view_space/view_space.inl"
#include "learning/math/math/matrix/geometry/projection_space/orthographic_projection/orthographic_projection.inl"

int main() {
    auto model      = math::matrix::geometry::model_space::Create(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    auto view       = math::matrix::geometry::view_space::Create(0.0, 0.0, 1920.0, 1080.0);
    auto projection = math::matrix::geometry::projection_space::orthographic_projection::Create(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
    auto mvp        = math::matrix::geometry::Create(model, view, projection);

    auto vertex = math::vector::CreateZero<double, 4>();
    math::vector::Write(vertex, 0, 0.0);
    math::vector::Write(vertex, 1, 0.0);
    math::vector::Write(vertex, 2, 0.0);
    math::vector::Write(vertex, 3, 1.0);
    vertex = math::matrix::Multiply(mvp, vertex);

    math::matrix::Print(model);
    std::cout << std::endl;

    math::matrix::Print(view);
    std::cout << std::endl;

    math::matrix::Print(projection);
    std::cout << std::endl;

    math::matrix::Print(mvp);
    std::cout << std::endl;

    math::vector::Print(vertex);
    std::cout << std::endl;

    return 0;
}
