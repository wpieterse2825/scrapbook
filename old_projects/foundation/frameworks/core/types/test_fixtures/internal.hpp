#pragma once

#include <gtest/gtest.h>

namespace next_mode::core::types::tests {
    template <typename UseImplementation>
    struct TestParameter {
        using Implementation = UseImplementation;
    };

    template <typename Implementation>
    using TestTypes = ::testing::Types<TestParameter<Implementation>>;
} // namespace next_mode::core::types::tests
