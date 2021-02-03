#pragma once

#include <gtest/gtest.h>

namespace next_mode::core::simd::tests {
    template <typename UseImplementation, typename UseElementType, uint8_t UseWidth>
    struct TestParameter {
        using Implementation = UseImplementation;
        using ElementType    = UseElementType;

        static constexpr auto Width = UseWidth;
    };

    template <typename Implementation>
    using TestTypes = ::testing::Types<TestParameter<Implementation, uint8_t, 1>,
                                       TestParameter<Implementation, uint8_t, 2>,
                                       TestParameter<Implementation, uint8_t, 4>,
                                       TestParameter<Implementation, uint8_t, 8>,
                                       TestParameter<Implementation, uint8_t, 16>,
                                       TestParameter<Implementation, uint8_t, 32>,
                                       TestParameter<Implementation, uint8_t, 64>,
                                       TestParameter<Implementation, uint16_t, 1>,
                                       TestParameter<Implementation, uint16_t, 2>,
                                       TestParameter<Implementation, uint16_t, 4>,
                                       TestParameter<Implementation, uint16_t, 8>,
                                       TestParameter<Implementation, uint16_t, 16>,
                                       TestParameter<Implementation, uint16_t, 32>,
                                       TestParameter<Implementation, uint32_t, 1>,
                                       TestParameter<Implementation, uint32_t, 2>,
                                       TestParameter<Implementation, uint32_t, 4>,
                                       TestParameter<Implementation, uint32_t, 8>,
                                       TestParameter<Implementation, uint32_t, 16>,
                                       TestParameter<Implementation, uint64_t, 1>,
                                       TestParameter<Implementation, uint64_t, 2>,
                                       TestParameter<Implementation, uint64_t, 4>,
                                       TestParameter<Implementation, uint64_t, 8>,
                                       TestParameter<Implementation, int8_t, 1>,
                                       TestParameter<Implementation, int8_t, 2>,
                                       TestParameter<Implementation, int8_t, 4>,
                                       TestParameter<Implementation, int8_t, 8>,
                                       TestParameter<Implementation, int8_t, 16>,
                                       TestParameter<Implementation, int8_t, 32>,
                                       TestParameter<Implementation, int8_t, 64>,
                                       TestParameter<Implementation, int16_t, 1>,
                                       TestParameter<Implementation, int16_t, 2>,
                                       TestParameter<Implementation, int16_t, 4>,
                                       TestParameter<Implementation, int16_t, 8>,
                                       TestParameter<Implementation, int16_t, 16>,
                                       TestParameter<Implementation, int16_t, 32>,
                                       TestParameter<Implementation, int32_t, 1>,
                                       TestParameter<Implementation, int32_t, 2>,
                                       TestParameter<Implementation, int32_t, 4>,
                                       TestParameter<Implementation, int32_t, 8>,
                                       TestParameter<Implementation, int32_t, 16>,
                                       TestParameter<Implementation, int64_t, 1>,
                                       TestParameter<Implementation, int64_t, 2>,
                                       TestParameter<Implementation, int64_t, 4>,
                                       TestParameter<Implementation, int64_t, 8>,
                                       TestParameter<Implementation, float, 1>,
                                       TestParameter<Implementation, float, 2>,
                                       TestParameter<Implementation, float, 4>,
                                       TestParameter<Implementation, float, 8>,
                                       TestParameter<Implementation, float, 16>,
                                       TestParameter<Implementation, double, 1>,
                                       TestParameter<Implementation, double, 2>,
                                       TestParameter<Implementation, double, 4>,
                                       TestParameter<Implementation, double, 8>>;
} // namespace next_mode::core::simd::tests
