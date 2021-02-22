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
    auto v1 = VectorFromZero<double, 15>();

    v1.elements[14] = -4.0;

    auto v2 = VectorFromZero<double, 15>();

    v2.elements[14] = -4.0;

    std::cout << std::boolalpha;
    std::cout << "Compare (No Epsilon):" << std::endl;
    std::cout << " * General : " << detail::vector::general::Compare(v1, v2) << std::endl;
    std::cout << " * SSE 1   : " << detail::vector::sse_1::Compare(v1, v2) << std::endl;
    std::cout << " * SSE 2   : " << detail::vector::sse_2::Compare(v1, v2) << std::endl;
    std::cout << " * AVX 1   : " << detail::vector::avx_1::Compare(v1, v2) << std::endl;

    return 0;
}
