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
    auto r = VectorFromZero<float, 1024>();

    return r.elements[0];
}
