#pragma once

#include <assert.h>
#include <math.h>

#include <immintrin.h>

#include <iostream>

#include "learning/math/math.hpp"
#include "learning/math/math.inl"
#include "learning/math/vector/vector.inl"

constexpr auto SampleCount    = 10;
constexpr auto IterationCount = 10000000;

constexpr auto Elements = 127;

template <typename Type, size_t Dimensions>
class SingleItemFixture : public celero::TestFixture {
  public:
    virtual void setUp(const celero::TestFixture::ExperimentValue&) override {
        this->item = VectorFromZero<Type, Dimensions>();

        Write(this->item, Dimensions - 1, Type {+1});
    }

    Vector<Type, Dimensions> item;
};

template <typename Type, size_t Dimensions>
class DoubleItemFixture : public celero::TestFixture {
  public:
    virtual void setUp(const celero::TestFixture::ExperimentValue&) override {
        this->lhs = VectorFromZero<Type, Dimensions>();
        this->rhs = VectorFromZero<Type, Dimensions>();

        Write(this->lhs, Dimensions - 1, Type {-1});
        Write(this->rhs, Dimensions - 1, Type {+1});
    }

    Vector<Type, Dimensions> lhs;
    Vector<Type, Dimensions> rhs;
};
