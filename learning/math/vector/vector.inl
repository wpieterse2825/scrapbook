template <typename Type, size_t Dimensions>
inline auto GetDimensions(const Vector<Type, Dimensions>&) -> size_t {
    return Dimensions;
}

template <typename Type, size_t Dimensions>
inline auto Read(const Vector<Type, Dimensions>& input, const size_t index) -> Type {
    assert(index < Dimensions);

    return input.elements[index];
}

template <typename Type, size_t Dimensions>
inline auto Write(Vector<Type, Dimensions>& input, const size_t index, const Type& value) -> void {
    assert(index < Dimensions);

    input.elements[index] = value;
}

constexpr auto VectorSIMDEnabled  = true;
constexpr auto VectorSIMDUseSSE1  = true;
constexpr auto VectorSIMDUseSSE2  = true;
constexpr auto VectorSIMDUseSSE3  = true;
constexpr auto VectorSIMDUseSSSE3 = true;
constexpr auto VectorSIMDUseSSE41 = true;
constexpr auto VectorSIMDUseSSE42 = true;
constexpr auto VectorSIMDUseAVX1  = true;
constexpr auto VectorSIMDUseAVX2  = true;

namespace detail {
    namespace vector {
        namespace base {
            template <typename Type, size_t Dimensions>
            inline auto VectorFromBroadcast(const Type& input_value) -> Vector<Type, Dimensions> {
                auto output = Vector<Type, Dimensions> {};

                for (auto index = size_t {0}; index < Dimensions; index++) {
                    Write(output, index, input_value);
                }

                return output;
            }
        } // namespace base

        namespace sse_1 {
            template <typename Type, size_t Dimensions>
            inline auto VectorFromBroadcast(const Type& input_value) -> Vector<Type, Dimensions> {
                if constexpr (std::is_same_v<Type, float> == true) {
                    if constexpr (Dimensions >= 4) {
                        constexpr auto block_size     = 4;
                        constexpr auto simd_blocks    = Dimensions / block_size;
                        constexpr auto trailer_blocks = Dimensions % block_size;
                        constexpr auto trailer_start  = (simd_blocks * block_size) - 1;

                        auto output        = Vector<Type, Dimensions> {};
                        auto output_buffer = &output.elements[0];

                        const auto broadcast = _mm_set1_ps(input_value);

                        for (auto index = size_t {0}; index < simd_blocks; index += block_size) {
                            _mm_storeu_ps(output_buffer, broadcast);

                            output_buffer += block_size;
                        }

                        if constexpr (trailer_blocks != 0) {
                            for (auto index = trailer_start; index < Dimensions; index++) {
                                Write(output, index, input_value);
                            }
                        }

                        return output;
                    }
                }

                return base::VectorFromBroadcast<Type, Dimensions>(input_value);
            }
        } // namespace sse_1

        namespace sse_2 {
            template <typename Type, size_t Dimensions>
            inline auto VectorFromBroadcast(const Type& input_value) -> Vector<Type, Dimensions> {
                if constexpr (std::is_same_v<Type, float> == true) {
                    // We have the same version here for SSE 2 because we can use the storeu_si128 intrinsic, which is faster than
                    // storeu_ps.

                    if constexpr (Dimensions >= 4) {
                        constexpr auto block_size     = 4;
                        constexpr auto simd_blocks    = Dimensions / block_size;
                        constexpr auto trailer_blocks = Dimensions % block_size;
                        constexpr auto trailer_start  = (simd_blocks * block_size) - 1;

                        auto output        = Vector<Type, Dimensions> {};
                        auto output_buffer = &output.elements[0];

                        const auto broadcast     = _mm_set1_ps(input_value);
                        const auto broadcast_raw = _mm_castps_si128(broadcast);

                        for (auto index = size_t {0}; index < simd_blocks; index += block_size) {
                            _mm_storeu_si128((__m128i_u*)output_buffer, broadcast_raw);

                            output_buffer += block_size;
                        }

                        if constexpr (trailer_blocks != 0) {
                            for (auto index = trailer_start; index < Dimensions; index++) {
                                Write(output, index, input_value);
                            }
                        }

                        return output;
                    }
                }

                if constexpr (std::is_same_v<Type, double> == true) {
                    if constexpr (Dimensions >= 2) {
                        constexpr auto block_size     = 2;
                        constexpr auto simd_blocks    = Dimensions / block_size;
                        constexpr auto trailer_blocks = Dimensions % block_size;
                        constexpr auto trailer_start  = (simd_blocks * block_size) - 1;

                        auto output        = Vector<Type, Dimensions> {};
                        auto output_buffer = &output.elements[0];

                        const auto broadcast     = _mm_set1_pd(input_value);
                        const auto broadcast_raw = _mm_castpd_si128(broadcast);

                        for (auto index = size_t {0}; index < simd_blocks; index += block_size) {
                            _mm_storeu_si128((__m128i_u*)output_buffer, broadcast_raw);

                            output_buffer += block_size;
                        }

                        if constexpr (trailer_blocks != 0) {
                            for (auto index = trailer_start; index < Dimensions; index++) {
                                Write(output, index, input_value);
                            }
                        }

                        return output;
                    }
                }

                return sse_1::VectorFromBroadcast<Type, Dimensions>(input_value);
            }
        } // namespace sse_2

        namespace avx_1 {
            template <typename Type, size_t Dimensions>
            inline auto VectorFromBroadcast(const Type& input_value) -> Vector<Type, Dimensions> {
                if constexpr (std::is_same_v<Type, float> == true) {
                    if constexpr (Dimensions >= 8) {
                        constexpr auto block_size     = 8;
                        constexpr auto simd_blocks    = Dimensions / block_size;
                        constexpr auto trailer_blocks = Dimensions % block_size;
                        constexpr auto trailer_start  = (simd_blocks * block_size) - 1;

                        auto output        = Vector<Type, Dimensions> {};
                        auto output_buffer = &output.elements[0];

                        const auto broadcast     = _mm256_set1_ps(input_value);
                        const auto broadcast_raw = _mm256_castps_si256(broadcast);

                        for (auto index = size_t {0}; index < simd_blocks; index += block_size) {
                            _mm256_storeu_si256((__m256i_u*)output_buffer, broadcast_raw);

                            output_buffer += block_size;
                        }

                        if constexpr (trailer_blocks != 0) {
                            for (auto index = trailer_start; index < Dimensions; index++) {
                                Write(output, index, input_value);
                            }
                        }

                        return output;
                    }
                }

                if constexpr (std::is_same_v<Type, double> == true) {
                    if constexpr (Dimensions >= 4) {
                        constexpr auto block_size     = 4;
                        constexpr auto simd_blocks    = Dimensions / block_size;
                        constexpr auto trailer_blocks = Dimensions % block_size;
                        constexpr auto trailer_start  = (simd_blocks * block_size) - 1;

                        auto output        = Vector<Type, Dimensions> {};
                        auto output_buffer = &output.elements[0];

                        const auto broadcast     = _mm256_set1_pd(input_value);
                        const auto broadcast_raw = _mm256_castpd_si256(broadcast);

                        for (auto index = size_t {0}; index < simd_blocks; index += block_size) {
                            _mm256_storeu_si256((__m256i_u*)output_buffer, broadcast_raw);

                            output_buffer += block_size;
                        }

                        if constexpr (trailer_blocks != 0) {
                            for (auto index = trailer_start; index < Dimensions; index++) {
                                Write(output, index, input_value);
                            }
                        }

                        return output;
                    }
                }

                return sse_2::VectorFromBroadcast<Type, Dimensions>(input_value);
            }
        } // namespace avx_1
    }     // namespace vector
} // namespace detail

template <typename Type, size_t Dimensions>
inline auto VectorFromBroadcast(const Type& input_value) -> Vector<Type, Dimensions> {
    if constexpr (VectorSIMDEnabled == true) {
        if constexpr (VectorSIMDUseAVX1 == true) {
            return detail::vector::avx_1::VectorFromBroadcast<Type, Dimensions>(input_value);
        }

        if constexpr (VectorSIMDUseSSE2 == true) {
            return detail::vector::sse_2::VectorFromBroadcast<Type, Dimensions>(input_value);
        }

        if constexpr (VectorSIMDUseSSE1 == true) {
            return detail::vector::sse_1::VectorFromBroadcast<Type, Dimensions>(input_value);
        }
    }

    return detail::vector::base::VectorFromBroadcast<Type, Dimensions>(input_value);
}

template <typename Type, size_t Dimensions>
inline auto VectorFromZero() -> Vector<Type, Dimensions> {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    return VectorFromBroadcast<Type, Dimensions>(zero_positive);
}

namespace detail {
    namespace vector {
        namespace internal {
            template <typename Type, size_t Dimensions>
            inline auto CompareWorker(const Vector<Type, Dimensions>& lhs,
                                      const Vector<Type, Dimensions>& rhs,
                                      const Type&                     epsilon,
                                      size_t                          start_index,
                                      size_t                          end_index) -> bool {
                for (auto index = start_index; index < end_index; index++) {
                    const auto lhs_value           = Read(lhs, index);
                    const auto rhs_value           = Read(rhs, index);
                    const auto difference          = Minus(lhs_value, rhs_value);
                    const auto absolute_difference = Absolute(difference);
                    const auto over_epsilon        = GreaterThan(absolute_difference, epsilon);

                    if (over_epsilon == true) {
                        return false;
                    }
                }

                return true;
            }
        } // namespace internal

        namespace base {
            template <typename Type, size_t Dimensions>
            inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool {
                return internal::CompareWorker(lhs, rhs, epsilon, 0, Dimensions);
            }
        } // namespace base

        namespace sse_1 {
            template <typename Type, size_t Dimensions>
            inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool {
                if constexpr (std::is_same_v<Type, float> == true) {
                    if constexpr (Dimensions >= 4) {
                        constexpr auto block_size     = 4;
                        constexpr auto simd_blocks    = Dimensions / block_size;
                        constexpr auto trailer_blocks = Dimensions % block_size;

                        auto lhs_buffer = &lhs.elements[0];
                        auto rhs_buffer = &rhs.elements[0];

                        const auto epsilon_simd = _mm_set1_ps(epsilon);
                        const auto sign_simd    = _mm_set1_ps(-0);

                        for (auto index = size_t {0}; index < simd_blocks; index += block_size) {
                            const auto lhs_value           = _mm_loadu_ps(lhs_buffer);
                            const auto rhs_value           = _mm_loadu_ps(rhs_buffer);
                            const auto difference          = _mm_sub_ps(lhs_value, rhs_value);
                            const auto absolute_difference = _mm_and_ps(sign_simd, difference);
                            const auto over_epsilon        = _mm_cmpgt_ps(absolute_difference, epsilon_simd);
                            const auto over_epsilon_mask   = _mm_movemask_ps(over_epsilon);

                            if (over_epsilon_mask != 0) {
                                return false;
                            }

                            lhs_buffer += block_size;
                            rhs_buffer += block_size;
                        }

                        if constexpr (trailer_blocks != 0) {
                            constexpr auto trailer_start = (simd_blocks * block_size) - 1;
                            constexpr auto trailer_end   = trailer_start + trailer_blocks;

                            return internal::CompareWorker(lhs, rhs, epsilon, trailer_start, trailer_end);
                        }

                        return true;
                    }
                }

                return base::Compare(lhs, rhs, epsilon);
            }
        } // namespace sse_1

        namespace sse_2 {
            template <typename Type, size_t Dimensions>
            inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool {
                if constexpr (std::is_same_v<Type, double> == true) {
                    if constexpr (Dimensions >= 2) {
                        constexpr auto block_size     = 2;
                        constexpr auto simd_blocks    = Dimensions / block_size;
                        constexpr auto trailer_blocks = Dimensions % block_size;

                        auto lhs_buffer = &lhs.elements[0];
                        auto rhs_buffer = &rhs.elements[0];

                        const auto epsilon_simd = _mm_set1_pd(epsilon);
                        const auto sign_simd    = _mm_set1_pd(-0);

                        for (auto index = size_t {0}; index < simd_blocks; index += block_size) {
                            const auto lhs_value           = _mm_loadu_pd(lhs_buffer);
                            const auto rhs_value           = _mm_loadu_pd(rhs_buffer);
                            const auto difference          = _mm_sub_pd(lhs_value, rhs_value);
                            const auto absolute_difference = _mm_and_pd(sign_simd, difference);
                            const auto over_epsilon        = _mm_cmpgt_pd(absolute_difference, epsilon_simd);
                            const auto over_epsilon_mask   = _mm_movemask_pd(over_epsilon);

                            if (over_epsilon_mask != 0) {
                                return false;
                            }

                            lhs_buffer += block_size;
                            rhs_buffer += block_size;
                        }

                        if constexpr (trailer_blocks != 0) {
                            constexpr auto trailer_start = (simd_blocks * block_size) - 1;
                            constexpr auto trailer_end   = trailer_start + trailer_blocks;

                            return internal::CompareWorker(lhs, rhs, epsilon, trailer_start, trailer_end);
                        }

                        return true;
                    }
                }

                return sse_1::Compare(lhs, rhs, epsilon);
            }
        } // namespace sse_2

        namespace avx_1 {
            template <typename Type, size_t Dimensions>
            inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool {
                if constexpr (std::is_same_v<Type, float> == true) {
                    if constexpr (Dimensions >= 8) {
                        constexpr auto block_size     = 8;
                        constexpr auto simd_blocks    = Dimensions / block_size;
                        constexpr auto trailer_blocks = Dimensions % block_size;

                        auto lhs_buffer = &lhs.elements[0];
                        auto rhs_buffer = &rhs.elements[0];

                        const auto epsilon_simd = _mm256_set1_ps(epsilon);
                        const auto sign_simd    = _mm256_set1_ps(-0);

                        for (auto index = size_t {0}; index < simd_blocks; index += block_size) {
                            const auto lhs_value           = _mm256_loadu_ps(lhs_buffer);
                            const auto rhs_value           = _mm256_loadu_ps(rhs_buffer);
                            const auto difference          = _mm256_sub_ps(lhs_value, rhs_value);
                            const auto absolute_difference = _mm256_and_ps(sign_simd, difference);
                            const auto over_epsilon        = _mm256_cmp_ps(absolute_difference, epsilon_simd, _CMP_GT_OS);
                            const auto over_epsilon_mask   = _mm256_movemask_ps(over_epsilon);

                            if (over_epsilon_mask != 0) {
                                return false;
                            }

                            lhs_buffer += block_size;
                            rhs_buffer += block_size;
                        }

                        if constexpr (trailer_blocks != 0) {
                            constexpr auto trailer_start = (simd_blocks * block_size) - 1;
                            constexpr auto trailer_end   = trailer_start + trailer_blocks;

                            return internal::CompareWorker(lhs, rhs, epsilon, trailer_start, trailer_end);
                        }

                        return true;
                    }
                }

                if constexpr (std::is_same_v<Type, double> == true) {
                    if constexpr (Dimensions >= 4) {
                        constexpr auto block_size     = 4;
                        constexpr auto simd_blocks    = Dimensions / block_size;
                        constexpr auto trailer_blocks = Dimensions % block_size;

                        auto lhs_buffer = &lhs.elements[0];
                        auto rhs_buffer = &rhs.elements[0];

                        const auto epsilon_simd = _mm256_set1_pd(epsilon);
                        const auto sign_simd    = _mm256_set1_pd(-0);

                        for (auto index = size_t {0}; index < simd_blocks; index += block_size) {
                            const auto lhs_value           = _mm256_loadu_pd(lhs_buffer);
                            const auto rhs_value           = _mm256_loadu_pd(rhs_buffer);
                            const auto difference          = _mm256_sub_pd(lhs_value, rhs_value);
                            const auto absolute_difference = _mm256_and_pd(sign_simd, difference);
                            const auto over_epsilon        = _mm256_cmp_pd(absolute_difference, epsilon_simd, _CMP_GT_OS);
                            const auto over_epsilon_mask   = _mm256_movemask_pd(over_epsilon);

                            if (over_epsilon_mask != 0) {
                                return false;
                            }

                            lhs_buffer += block_size;
                            rhs_buffer += block_size;
                        }

                        if constexpr (trailer_blocks != 0) {
                            constexpr auto trailer_start = (simd_blocks * block_size) - 1;
                            constexpr auto trailer_end   = trailer_start + trailer_blocks;

                            return internal::CompareWorker(lhs, rhs, epsilon, trailer_start, trailer_end);
                        }

                        return true;
                    }
                }

                return sse_1::Compare(lhs, rhs, epsilon);
            }
        } // namespace avx_1
    }     // namespace vector
} // namespace detail

template <typename Type, size_t Dimensions>
inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool {
    if constexpr (VectorSIMDEnabled == true) {
        if constexpr (VectorSIMDUseAVX1 == true) {
            return detail::vector::avx_1::Compare(lhs, rhs, epsilon);
        }

        if constexpr (VectorSIMDUseSSE2 == true) {
            return detail::vector::sse_2::Compare(lhs, rhs, epsilon);
        }

        if constexpr (VectorSIMDUseSSE1 == true) {
            return detail::vector::sse_1::Compare(lhs, rhs, epsilon);
        }
    }

    return detail::vector::base::Compare(lhs, rhs, epsilon);
}

namespace detail {
    namespace vector {
        namespace internal {
            template <typename Type, size_t Dimensions>
            inline auto
            CompareWorker(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, size_t start_index, size_t end_index)
              -> bool {
                for (auto index = start_index; index < end_index; index++) {
                    const auto lhs_value = Read(lhs, index);
                    const auto rhs_value = Read(rhs, index);
                    const auto is_equal  = Equal(lhs_value, rhs_value);

                    if (is_equal == false) {
                        return false;
                    }
                }

                return true;
            }
        } // namespace internal

        namespace base {
            template <typename Type, size_t Dimensions>
            inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
                return internal::CompareWorker(lhs, rhs, 0, Dimensions);
            }
        } // namespace base

        namespace sse_1 {
            template <typename Type, size_t Dimensions>
            inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
                if constexpr (std::is_same_v<Type, float> == true) {
                    if constexpr (Dimensions >= 4) {
                        constexpr auto block_size     = 4;
                        constexpr auto simd_blocks    = Dimensions / block_size;
                        constexpr auto trailer_blocks = Dimensions % block_size;

                        auto lhs_buffer = &lhs.elements[0];
                        auto rhs_buffer = &rhs.elements[0];

                        for (auto index = size_t {0}; index < simd_blocks; index += block_size) {
                            const auto lhs_value     = _mm_loadu_ps(lhs_buffer);
                            const auto rhs_value     = _mm_loadu_ps(rhs_buffer);
                            const auto is_equal      = _mm_cmpeq_ps(lhs_value, rhs_value);
                            const auto is_equal_mask = _mm_movemask_ps(is_equal);

                            if (is_equal_mask != 0) {
                                return false;
                            }

                            lhs_buffer += block_size;
                            rhs_buffer += block_size;
                        }

                        if constexpr (trailer_blocks != 0) {
                            constexpr auto trailer_start = (simd_blocks * block_size) - 1;
                            constexpr auto trailer_end   = trailer_start + trailer_blocks;

                            return internal::CompareWorker(lhs, rhs, trailer_start, trailer_end);
                        }

                        return true;
                    }
                }

                return base::Compare(lhs, rhs);
            }
        } // namespace sse_1

        namespace sse_2 {
            template <typename Type, size_t Dimensions>
            inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
                if constexpr (std::is_same_v<Type, double> == true) {
                    if constexpr (Dimensions >= 2) {
                        constexpr auto block_size     = 2;
                        constexpr auto simd_blocks    = Dimensions / block_size;
                        constexpr auto trailer_blocks = Dimensions % block_size;

                        auto lhs_buffer = &lhs.elements[0];
                        auto rhs_buffer = &rhs.elements[0];

                        for (auto index = size_t {0}; index < simd_blocks; index += block_size) {
                            const auto lhs_value     = _mm_loadu_pd(lhs_buffer);
                            const auto rhs_value     = _mm_loadu_pd(rhs_buffer);
                            const auto is_equal      = _mm_cmpeq_pd(lhs_value, rhs_value);
                            const auto is_equal_mask = _mm_movemask_pd(is_equal);

                            if (is_equal_mask != 0) {
                                return false;
                            }

                            lhs_buffer += block_size;
                            rhs_buffer += block_size;
                        }

                        if constexpr (trailer_blocks != 0) {
                            constexpr auto trailer_start = (simd_blocks * block_size) - 1;
                            constexpr auto trailer_end   = trailer_start + trailer_blocks;

                            return internal::CompareWorker(lhs, rhs, trailer_start, trailer_end);
                        }

                        return true;
                    }
                }

                return sse_1::Compare(lhs, rhs);
            }
        } // namespace sse_2

        namespace avx_1 {
            template <typename Type, size_t Dimensions>
            inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
                if constexpr (std::is_same_v<Type, float> == true) {
                    if constexpr (Dimensions >= 8) {
                        constexpr auto block_size     = 8;
                        constexpr auto simd_blocks    = Dimensions / block_size;
                        constexpr auto trailer_blocks = Dimensions % block_size;

                        auto lhs_buffer = &lhs.elements[0];
                        auto rhs_buffer = &rhs.elements[0];

                        for (auto index = size_t {0}; index < simd_blocks; index += block_size) {
                            const auto lhs_value     = _mm256_loadu_ps(lhs_buffer);
                            const auto rhs_value     = _mm256_loadu_ps(rhs_buffer);
                            const auto is_equal      = _mm256_cmp_ps(lhs_value, rhs_value, _CMP_EQ_OQ);
                            const auto is_equal_mask = _mm256_movemask_ps(is_equal);

                            if (is_equal_mask != 0) {
                                return false;
                            }

                            lhs_buffer += block_size;
                            rhs_buffer += block_size;
                        }

                        if constexpr (trailer_blocks != 0) {
                            constexpr auto trailer_start = (simd_blocks * block_size) - 1;
                            constexpr auto trailer_end   = trailer_start + trailer_blocks;

                            return internal::CompareWorker(lhs, rhs, trailer_start, trailer_end);
                        }

                        return true;
                    }
                }

                if constexpr (std::is_same_v<Type, double> == true) {
                    if constexpr (Dimensions >= 4) {
                        constexpr auto block_size     = 4;
                        constexpr auto simd_blocks    = Dimensions / block_size;
                        constexpr auto trailer_blocks = Dimensions % block_size;

                        auto lhs_buffer = &lhs.elements[0];
                        auto rhs_buffer = &rhs.elements[0];

                        for (auto index = size_t {0}; index < simd_blocks; index += block_size) {
                            const auto lhs_value     = _mm256_loadu_pd(lhs_buffer);
                            const auto rhs_value     = _mm256_loadu_pd(rhs_buffer);
                            const auto is_equal      = _mm256_cmp_pd(lhs_value, rhs_value, _CMP_EQ_OQ);
                            const auto is_equal_mask = _mm256_movemask_pd(is_equal);

                            if (is_equal_mask != 0) {
                                return false;
                            }

                            lhs_buffer += block_size;
                            rhs_buffer += block_size;
                        }

                        if constexpr (trailer_blocks != 0) {
                            constexpr auto trailer_start = (simd_blocks * block_size) - 1;
                            constexpr auto trailer_end   = trailer_start + trailer_blocks;

                            return internal::CompareWorker(lhs, rhs, trailer_start, trailer_end);
                        }

                        return true;
                    }
                }

                return sse_1::Compare(lhs, rhs);
            }
        } // namespace avx_1
    }     // namespace vector
} // namespace detail

template <typename Type, size_t Dimensions>
inline auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
    if constexpr (VectorSIMDEnabled == true) {
        if constexpr (VectorSIMDUseAVX1 == true) {
            return detail::vector::avx_1::Compare(lhs, rhs);
        }

        if constexpr (VectorSIMDUseSSE2 == true) {
            return detail::vector::sse_2::Compare(lhs, rhs);
        }

        if constexpr (VectorSIMDUseSSE1 == true) {
            return detail::vector::sse_1::Compare(lhs, rhs);
        }
    }

    return detail::vector::base::Compare(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto Equal(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool {
    const auto compare_result = Compare(lhs, rhs, epsilon);

    return compare_result == true;
}

template <typename Type, size_t Dimensions>
inline auto NotEqual(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, const Type& epsilon) -> bool {
    const auto compare_result = Compare(lhs, rhs, epsilon);

    return compare_result == false;
}

template <typename Type, size_t Dimensions>
inline auto Equal(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
    const auto compare_result = Compare(lhs, rhs);

    return compare_result == true;
}

template <typename Type, size_t Dimensions>
inline auto NotEqual(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
    const auto compare_result = Compare(lhs, rhs);

    return compare_result == false;
}

template <typename Type, size_t Dimensions>
inline auto Negate(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
    auto output = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto input_value   = Read(input, index);
        const auto input_negated = Negate(input_value);

        Write(output, index, input_negated);
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Plus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
    auto output = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto lhs_value = Read(lhs, index);
        const auto rhs_value = Read(rhs, index);
        const auto sum_value = Plus(lhs_value, rhs_value);

        Write(output, index, sum_value);
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Minus(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
    auto output = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto lhs_value = Read(lhs, index);
        const auto rhs_value = Read(rhs, index);
        const auto sum_value = Minus(lhs_value, rhs_value);

        Write(output, index, sum_value);
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Multiply(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
    auto output = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto lhs_value = Read(lhs, index);
        const auto rhs_value = rhs;
        const auto sum_value = Multiply(lhs_value, rhs_value);

        Write(output, index, sum_value);
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Divide(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
    auto output = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto lhs_value = Read(lhs, index);
        const auto rhs_value = rhs;
        const auto sum_value = Divide(lhs_value, rhs_value);

        Write(output, index, sum_value);
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Divide(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
    auto output = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto lhs_value = Read(lhs, index);
        const auto rhs_value = Read(rhs, index);
        const auto sum_value = Divide(lhs_value, rhs_value);

        Write(output, index, sum_value);
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Truncate(const Vector<Type, Dimensions>& input, const Type& output_length) -> Vector<Type, Dimensions> {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    auto output = VectorFromZero<Type, Dimensions>();

    if (output_length == zero_positive) {
        return output;
    }

    const auto output_length_squared = Multiply(output_length, output_length);
    auto       input_length_squared  = zero_positive;

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto input_value   = Read(input, index);
        const auto input_squared = Multiply(input_value, input_value);

        input_length_squared = Plus(input_length_squared, input_squared);
    }

    const auto input_over_output = GreaterThan(input_length_squared, output_length_squared);

    if (input_over_output == true) {
        const auto input_length_inversed  = InverseSquareRoot(input_length_squared);
        const auto output_length_inversed = Multiply(output_length, input_length_inversed);

        for (auto index = size_t {0}; index < Dimensions; index++) {
            const auto input_value  = Read(input, index);
            const auto output_value = Multiply(input_value, output_length_inversed);

            Write(output, index, output_value);
        }
    } else {
        for (auto index = size_t {0}; index < Dimensions; index++) {
            const auto input_value = Read(input, index);

            Write(output, index, input_value);
        }
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Normalize(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
    constexpr auto one_positive = Constants<Type>::OnePositive;

    return Truncate(input, one_positive);
}

template <typename Type, size_t Dimensions>
inline auto DotProduct(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Type {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    auto output_value = zero_positive;

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto lhs_value = Read(lhs, index);
        const auto rhs_value = Read(rhs, index);
        const auto sum_value = Multiply(lhs_value, rhs_value);

        output_value = Plus(output_value, sum_value);
    }

    return output_value;
}

template <typename Type>
inline auto CrossProduct(const Vector<Type, 3>& lhs, const Vector<Type, 3>& rhs) -> Vector<Type, 3> {
    auto output = Vector<Type, 3> {};

    const auto lhs_x = Read(lhs, VectorXComponent);
    const auto lhs_y = Read(lhs, VectorYComponent);
    const auto lhs_z = Read(lhs, VectorZComponent);

    const auto rhs_x = Read(rhs, VectorXComponent);
    const auto rhs_y = Read(rhs, VectorYComponent);
    const auto rhs_z = Read(rhs, VectorZComponent);

    const auto lhs_y_by_rhs_z = Multiply(lhs_y, rhs_z);
    const auto lhs_z_by_rhs_y = Multiply(lhs_z, rhs_y);
    const auto lhs_z_by_rhs_x = Multiply(lhs_z, rhs_x);
    const auto lhs_x_by_rhs_z = Multiply(lhs_x, rhs_z);
    const auto lhs_x_by_rhs_y = Multiply(lhs_x, rhs_y);
    const auto lhs_y_by_rhs_x = Multiply(lhs_y, rhs_x);

    const auto output_x = Minus(lhs_y_by_rhs_z, lhs_y_by_rhs_z);
    const auto output_y = Minus(lhs_z_by_rhs_x, lhs_x_by_rhs_z);
    const auto output_z = Minus(lhs_x_by_rhs_y, lhs_y_by_rhs_x);

    Write(output, VectorXComponent, output_x);
    Write(output, VectorYComponent, output_y);
    Write(output, VectorZComponent, output_z);

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Length(const Vector<Type, Dimensions>& input) -> Type {
    constexpr auto zero_positive = Constants<Type>::ZeroPositive;

    auto output_value = zero_positive;

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto input_value   = Read(input, index);
        const auto input_squared = Multiply(input_value, input_value);

        output_value = Plus(output_value, input_squared);
    }

    return SquareRoot(output_value);
}

template <typename Type, size_t Dimensions>
inline auto Clamp(const Vector<Type, Dimensions>& input, const Type& minimum, const Type& maximum) -> Vector<Type, Dimensions> {
    auto output = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto input_value         = Read(input, index);
        const auto input_under_minimum = LessThan(input_value, minimum);
        const auto input_over_maximum  = GreaterThan(input_value, maximum);

        if (input_under_minimum == true) {
            Write(output, index, minimum);
        } else if (input_over_maximum == true) {
            Write(output, index, maximum);
        } else {
            Write(output, index, input_value);
        }
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Snap(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
    constexpr auto one_half_plus = Constants<Type>::OneHalfPlus;

    auto output = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        auto input_value = Read(input, index);
        auto input_nudge = Plus(input_value, one_half_plus);
        auto input_snap  = Floor(input_nudge);

        Write(output, index, input_snap);
    }

    return output;
}

template <typename Type, size_t Dimensions>
inline auto Print(const Vector<Type, Dimensions>& input) -> void {
    constexpr auto elements_minus_one = Dimensions - 1;

    std::cout << "[ ";

    for (auto index = size_t {0}; index < Dimensions; index++) {
        const auto can_print_comma = LessThan(index, elements_minus_one);
        const auto output_value    = Read(input, index);

        std::cout << output_value;

        if (can_print_comma == true) {
            std::cout << ", ";
        }
    }

    std::cout << " ]";
    std::cout << std::endl;
}

template <typename Type, size_t Dimensions>
inline auto operator==(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
    return Equal(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator!=(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> bool {
    return NotEqual(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator-(const Vector<Type, Dimensions>& input) -> Vector<Type, Dimensions> {
    return Negate(input);
}

template <typename Type, size_t Dimensions>
inline auto operator+(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
    return Plus(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator-(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
    return Minus(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator*(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
    return Multiply(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator*(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Type {
    return DotProduct(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator/(const Vector<Type, Dimensions>& lhs, const Type& rhs) -> Vector<Type, Dimensions> {
    return Divide(lhs, rhs);
}

template <typename Type, size_t Dimensions>
inline auto operator/(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs) -> Vector<Type, Dimensions> {
    return Divide(lhs, rhs);
}
