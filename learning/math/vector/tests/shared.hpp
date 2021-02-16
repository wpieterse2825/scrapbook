#pragma once

#include <assert.h>
#include <math.h>

#include <immintrin.h>

#include <limits>
#include <iostream>

#include <gtest/gtest.h>

#include "learning/math/math.hpp"
#include "learning/math/math.inl"
#include "learning/math/vector/vector.inl"

template <typename InType, size_t InDimensions>
struct TestParameter {
    using Type = InType;

    static constexpr auto Dimensions = InDimensions;
};

using TestTypeCollection = testing::Types<TestParameter<float, 1>,
                                          TestParameter<float, 2>,
                                          TestParameter<float, 3>,
                                          TestParameter<float, 4>,
                                          TestParameter<float, 5>,
                                          TestParameter<float, 6>,
                                          TestParameter<float, 7>,
                                          TestParameter<float, 8>,
                                          TestParameter<float, 9>,
                                          TestParameter<float, 10>,
                                          TestParameter<float, 11>,
                                          TestParameter<float, 12>,
                                          TestParameter<float, 13>,
                                          TestParameter<float, 14>,
                                          TestParameter<float, 15>,
                                          TestParameter<float, 16>,
                                          TestParameter<float, DefaultTestDimensions>,
                                          TestParameter<double, 1>,
                                          TestParameter<double, 2>,
                                          TestParameter<double, 3>,
                                          TestParameter<double, 4>,
                                          TestParameter<double, 5>,
                                          TestParameter<double, 6>,
                                          TestParameter<double, 7>,
                                          TestParameter<double, 8>,
                                          TestParameter<double, 9>,
                                          TestParameter<double, 10>,
                                          TestParameter<double, 11>,
                                          TestParameter<double, 12>,
                                          TestParameter<double, 13>,
                                          TestParameter<double, 14>,
                                          TestParameter<double, 15>,
                                          TestParameter<double, 16>,
                                          TestParameter<double, DefaultTestDimensions>>;
