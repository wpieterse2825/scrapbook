#include <assert.h>
#include <math.h>

#include <iostream>

#include "learning/math/math/math.hpp"

#include "learning/math/math/math.inl"
#include "learning/math/math/vector/vector.inl"
#include "learning/math/math/matrix/matrix.inl"
#include "learning/math/math/matrix/geometry/model_space.inl"
#include "learning/math/math/matrix/geometry/view_space.inl"
#include "learning/math/math/matrix/geometry/orthographic_projection.inl"

int main() {
    auto model      = ModelMatrixGenerate(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    auto view       = ViewMatrixGenerate(0.0, 0.0, 1920.0, 1080.0);
    auto projection = OrthographicMatrixGenerate(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
    auto mvp        = model * view * projection;

    Print(model);
    std::cout << std::endl;

    Print(view);
    std::cout << std::endl;

    Print(projection);
    std::cout << std::endl;

    Print(mvp);
    std::cout << std::endl;

    auto v1        = ZeroVector<double, 3>();
    v1.elements[0] = 2.0;
    v1.elements[1] = 3.0;
    v1.elements[2] = 4.0;

    auto v2        = ZeroVector<double, 3>();
    v2.elements[0] = 5.0;
    v2.elements[1] = 6.0;
    v2.elements[2] = 7.0;

    auto result = CrossProduct(v1, v2);

    Print(result);

    return 0;
}
