#include <assert.h>
#include <math.h>

#include <immintrin.h>

#include <iostream>

#include "learning/math/math.hpp"

#include "learning/math/math.inl"
#include "learning/math/vector/vector.inl"
// #include "learning/math/matrix/matrix.inl"
// #include "learning/math/matrix/geometry/model_space.inl"
// #include "learning/math/matrix/geometry/view_space.inl"
// #include "learning/math/matrix/geometry/orthographic_projection.inl"
#include "learning/math/plane/plane.inl"

int main() {
    auto v1 = VectorFromZero<float, 4>();

    v1.elements[0] = +1.0f;
    v1.elements[1] = +2.0f;
    v1.elements[2] = +3.0f;
    v1.elements[3] = +4.0f;

    auto v2 = VectorFromZero<float, 4>();

    v2.elements[0] = -1.0f;
    v2.elements[1] = -2.0f;
    v2.elements[2] = -3.0f;
    v2.elements[3] = -4.0f;

    std::cout << detail::vector::base::Compare(v1, v2, 0.0f) << std::endl;
    std::cout << detail::vector::sse_1::Compare(v1, v2, 0.0f) << std::endl;
    std::cout << detail::vector::sse_2::Compare(v1, v2, 0.0f) << std::endl;
    std::cout << detail::vector::avx_1::Compare(v1, v2, 0.0f) << std::endl;

    return 0;
}
