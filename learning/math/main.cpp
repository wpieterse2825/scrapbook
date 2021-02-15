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
    auto model = math::matrix::CreateIdentity<double, 4, 4>();
    model      = math::matrix::geometry::model_space::Create(model, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    math::matrix::Print(model);
    std::cout << std::endl;

    auto view = math::matrix::CreateIdentity<double, 4, 4>();
    view      = math::matrix::geometry::view_space::Create(view, 0.0, 0.0, 1920.0, 1080.0);
    math::matrix::Print(view);
    std::cout << std::endl;

    auto projection = math::matrix::CreateIdentity<double, 4, 4>();
    projection = math::matrix::geometry::projection_space::orthographic_projection::Create(projection, -5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
    math::matrix::Print(projection);
    std::cout << std::endl;

    auto model_view_projection = math::matrix::CreateIdentity<double, 4, 4>();
    model_view_projection      = math::matrix::geometry::Create(model_view_projection, model, view, projection);
    math::matrix::Print(model_view_projection);
    std::cout << std::endl;

    auto vertex = math::vector::CreateZero<double, 4>();
    math::vector::Write(vertex, 0, 0.0);
    math::vector::Write(vertex, 1, 0.0);
    math::vector::Write(vertex, 2, 0.0);
    math::vector::Write(vertex, 3, 1.0);
    vertex = math::matrix::Multiply(model_view_projection, vertex);
    math::vector::Print(vertex);
    std::cout << std::endl;

    return 0;
}
