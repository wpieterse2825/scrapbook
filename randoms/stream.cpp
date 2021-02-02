#include <cassert>
#include <algorithm>
#include <iostream>

constexpr int64_t CacheLineSize = 64;

inline void PrefetchCacheLine(const void* pointer, int64_t offset) {
}

inline void FlushCacheLine(const void* pointer, int64_t offset) {
}

namespace stream_array {
    template <typename ElementType, int64_t CachedElementCount, int64_t RoundElementsTo>
    struct alignas(16) FStreamArrayInSequential {
        static_assert(CachedElementCount > 0);
        static_assert((CachedElementCount & (CachedElementCount - 1)) == 0);
        static_assert(((CachedElementCount * sizeof(ElementType)) & 15) == 0);
        static_assert(RoundElementsTo >= 1);

        int64_t            first_cached_element;
        int64_t            last_cached_element;
        int64_t            last_streamed_element;
        const ElementType* elements;
        int64_t            element_count;
        int64_t            element_count_rounded;

        FStreamArrayInSequential(const ElementType* elements, int64_t element_count);
        ~FStreamArrayInSequential();

        inline const ElementType& operator[](int64_t index) const;
    };

    template <typename ElementType, typename IndexType, int64_t CachedElementCount, int64_t RoundIndicesTo>
    struct alignas(16) FStreamArrayInGather {
        static_assert(CachedElementCount > 0);
        static_assert((CachedElementCount & (CachedElementCount - 1)) == 0);
        static_assert(((CachedElementCount * sizeof(ElementType)) & 15) == 0);
        static_assert(((CachedElementCount * sizeof(IndexType)) & 15) == 0);
        static_assert(RoundIndicesTo >= 1);

        int64_t            first_cached_element;
        int64_t            last_cached_element;
        int64_t            last_streamed_element;
        int64_t            first_cached_index;
        int64_t            last_cached_index;
        int64_t            last_streamed_index;
        const ElementType* elements;
        int64_t            element_count;
        const IndexType*   indices;
        int64_t            indices_count;
        int64_t            indices_count_rounded;

        FStreamArrayInGather(const ElementType* elements, int64_t element_count, const IndexType* indices, int64_t indices_count);
        ~FStreamArrayInGather();

        const ElementType& operator[](int64_t index) const;
    };
} // namespace stream_array

namespace stream_array {
    inline void FlushArray(const void* elements, int64_t element_size, int64_t first_element, int64_t last_element);

    namespace in_sequential {
        template <typename ElementType, int64_t CachedElementCount, int64_t RoundElementsTo>
        inline int64_t PrefetchNext(FStreamArrayInSequential<ElementType, CachedElementCount, RoundElementsTo>& item);
    }

    namespace in_gather {
        template <typename ElementType, typename IndexType, int64_t CachedElementCount, int64_t RoundIndicesTo>
        int64_t PrefetchNext(FStreamArrayInGather<ElementType, IndexType, CachedElementCount, RoundIndicesTo>& item);
    }
} // namespace stream_array

namespace stream_array {
    inline void FlushArray(const void* elements, int64_t element_size, int64_t first_element, int64_t last_element) {
        const uintptr_t array_address     = reinterpret_cast<uintptr_t>(elements);
        const uintptr_t array_flush_base  = (array_address + (CacheLineSize - 1)) & ~(CacheLineSize - 1);
        const uintptr_t array_flush_start = (array_address + (first_element * element_size)) & ~(CacheLineSize - 1);
        const uintptr_t array_flush_end   = (array_address + (last_element * element_size)) & ~(CacheLineSize - 1);
        const uintptr_t initial_offset    = std::max(array_flush_base, array_flush_start);

        for (uintptr_t offset = initial_offset; offset < array_flush_end; offset += CacheLineSize) {
            ::FlushCacheLine(elements, offset - array_address);
        }
    }

    template <typename ElementType, int64_t CachedElementCount, int64_t RoundElementsTo>
    FStreamArrayInSequential<ElementType, CachedElementCount, RoundElementsTo>::FStreamArrayInSequential(const ElementType* elements,
                                                                                                         int64_t            element_count)
      : first_cached_element {0}
      , last_cached_element {0}
      , last_streamed_element {0}
      , elements {elements}
      , element_count {element_count}
      , element_count_rounded {element_count} {
        assert((reinterpret_cast<uintptr_t>(elements) & 15) == 0);

        in_sequential::PrefetchNext(*this);

        element_count_rounded += RoundElementsTo - 1;
        element_count_rounded -= element_count_rounded % ((RoundElementsTo > 1) ? RoundElementsTo : 1);
    }

    template <typename ElementType, int64_t CachedElementCount, int64_t RoundElementsTo>
    FStreamArrayInSequential<ElementType, CachedElementCount, RoundElementsTo>::~FStreamArrayInSequential() {
        stream_array::FlushArray(elements, sizeof(ElementType), first_cached_element, last_cached_element);
    }

    template <typename ElementType, int64_t CachedElementCount, int64_t RoundElementsTo>
    const ElementType& FStreamArrayInSequential<ElementType, CachedElementCount, RoundElementsTo>::operator[](int64_t index) const {
        assert((index >= first_cached_element && index < last_cached_element) ||
               (last_cached_element == element_count && index >= element_count && index < element_count_rounded));

        if constexpr (RoundElementsTo > 1) {
            index &= (index - element_count_rounded) >> 31;
        }

        return elements[index];
    }

    namespace in_sequential {
        template <typename ElementType, int64_t CachedElementCount, int64_t RoundElementsTo>
        inline int64_t PrefetchNext(FStreamArrayInSequential<ElementType, CachedElementCount, RoundElementsTo>& item) {
            if (item.last_cached_element < item.element_count) {
                item.last_cached_element  = item.last_streamed_element;
                item.first_cached_element = std::max(item.last_cached_element - CachedElementCount, int64_t {0});

                stream_array::FlushArray(
                  item.elements, sizeof(ElementType), item.first_cached_element - CachedElementCount, item.first_cached_element);
                if (item.last_streamed_element < item.element_count) {
                    item.last_streamed_element = std::min(item.last_streamed_element + CachedElementCount, item.element_count);

                    const int64_t prefetch_offset_start = item.last_cached_element * sizeof(ElementType);
                    const int64_t prefetch_offset_end   = item.last_streamed_element * sizeof(ElementType);
                    for (int64_t offset = prefetch_offset_start; offset < prefetch_offset_end; offset += CacheLineSize) {
                        ::PrefetchCacheLine(item.elements, offset);
                    }
                }
            }

            return (item.last_cached_element == item.element_count) ? item.element_count_rounded : item.last_cached_element;
        }
    } // namespace in_sequential

    template <typename ElementType, typename IndexType, int64_t CachedElementCount, int64_t RoundIndicesTo>
    FStreamArrayInGather<ElementType, IndexType, CachedElementCount, RoundIndicesTo>::FStreamArrayInGather(const ElementType* elements,
                                                                                                           int64_t            element_count,
                                                                                                           const IndexType*   indices,
                                                                                                           int64_t            indices_count)
      : first_cached_element {0}
      , last_cached_element {0}
      , last_streamed_element {0}
      , first_cached_index {0}
      , last_cached_index {0}
      , last_streamed_index {0}
      , elements {elements}
      , element_count {element_count}
      , indices {indices}
      , indices_count {indices_count}
      , indices_count_rounded {indices_count} {
        assert((reinterpret_cast<uintptr_t>(elements) & 15) == 0);
        assert((reinterpret_cast<uintptr_t>(indices) & 15) == 0);

        in_gather::PrefetchNext(*this);
        in_gather::PrefetchNext(*this);

        indices_count_rounded += RoundIndicesTo - 1;
        indices_count_rounded -= indices_count_rounded % ((RoundIndicesTo > 1) ? RoundIndicesTo : 1);
    }

    template <typename ElementType, typename IndexType, int64_t CachedElementCount, int64_t RoundIndicesTo>
    FStreamArrayInGather<ElementType, IndexType, CachedElementCount, RoundIndicesTo>::~FStreamArrayInGather() {
        stream_array::FlushArray(indices, sizeof(IndexType), first_cached_index, last_cached_index);
        stream_array::FlushArray(elements, sizeof(ElementType), first_cached_element, last_cached_element);
    }

    template <typename ElementType, typename IndexType, int64_t CachedElementCount, int64_t RoundIndicesTo>
    const ElementType& FStreamArrayInGather<ElementType, IndexType, CachedElementCount, RoundIndicesTo>::operator[](int64_t index) const {
        assert((index >= first_cached_element && index < last_cached_element) ||
               (last_cached_element == indices_count && index >= indices_count && index < indices_count_rounded));
        if constexpr (RoundIndicesTo > 1) {
            index &= (index - indices_count) >> 31;
        }

        const IndexType element_index = indices[index];
        return elements[element_index];
    }

    namespace in_gather {
        template <typename ElementType, typename IndexType, int64_t CachedElementCount, int64_t RoundIndicesTo>
        int64_t PrefetchNext(FStreamArrayInGather<ElementType, IndexType, CachedElementCount, RoundIndicesTo>& item) {
            if (item.last_cached_element < item.indices_count) {
                if (item.last_streamed_index > 0) {
                    item.last_cached_element  = item.last_streamed_element;
                    item.first_cached_element = std::max(item.last_cached_element - CachedElementCount, int64_t {0});

                    item.last_cached_index  = item.last_streamed_index;
                    item.first_cached_index = std::max(item.last_cached_index - CachedElementCount, int64_t {0});

                    stream_array::FlushArray(
                      item.indices, sizeof(IndexType), item.first_cached_index - CachedElementCount, item.first_cached_index);

                    stream_array::FlushArray(
                      item.elements, sizeof(ElementType), item.first_cached_element - CachedElementCount, item.first_cached_element);

                    if (item.last_streamed_element < item.indices_count) {
                        item.last_streamed_element = item.last_cached_index;
                        for (int64_t index = item.last_cached_element; index < item.last_streamed_element; index++) {
                            assert(index >= item.first_cached_index && index < item.last_cached_index);
                            assert(item.indices[index] >= 0 && item.indices[index] < item.element_count);

                            ::PrefetchCacheLine(item.elements, item.indices[index] * sizeof(ElementType));
                        }
                    }
                }

                if (item.last_streamed_index < item.indices_count) {
                    item.last_streamed_index = std::min(item.last_streamed_index + CachedElementCount, item.indices_count);

                    const int64_t prefetch_offset_start = (item.last_cached_index * sizeof(IndexType));
                    const int64_t prefetch_offset_end   = (item.last_streamed_index * sizeof(IndexType));
                    for (int64_t offset = prefetch_offset_start; offset < prefetch_offset_end; offset += CacheLineSize) {
                        ::PrefetchCacheLine(item.indices, offset);
                    }
                }
            }

            return (item.last_cached_element == item.indices_count) ? item.indices_count_rounded : item.last_cached_element;
        }
    } // namespace in_gather
} // namespace stream_array

void StreamInArraySequentialTest() {
    constexpr int64_t index_count = 128;
    uint8_t*          indices     = static_cast<uint8_t*>(::malloc(index_count * sizeof(uint8_t)));

    for (int64_t index = 0; index < index_count; index++) {
        indices[index] = index;
    }

    stream_array::FStreamArrayInSequential<uint8_t, 16, 4> indices_sequential {indices, index_count};

    for (int64_t index = 0; index < index_count;) {
        const int64_t next_index = stream_array::in_sequential::PrefetchNext(indices_sequential) - 4;
        for (; index <= next_index; index += 4) {
            const uint8_t i0 = indices_sequential[index + 0];
            const uint8_t i1 = indices_sequential[index + 1];
            const uint8_t i2 = indices_sequential[index + 2];
            const uint8_t i3 = indices_sequential[index + 3];

            assert(i0 == (index + 0));
            assert(i1 == (index + 1));
            assert(i2 == (index + 2));
            assert(i3 == (index + 3));
        }
    }

    ::free(indices);
}

void StreamInArrayGatherTest() {
    constexpr int64_t vertices_count = 4;
    uint8_t*          vertices       = static_cast<uint8_t*>(::malloc(vertices_count * sizeof(uint8_t)));

    constexpr int64_t indices_count = 6;
    uint8_t*          indices       = static_cast<uint8_t*>(::malloc(indices_count * sizeof(uint8_t)));

    vertices[0] = 10;
    vertices[1] = 20;
    vertices[2] = 30;
    vertices[3] = 40;

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;

    stream_array::FStreamArrayInGather<uint8_t, uint8_t, 16, 1> indices_gather {vertices, vertices_count, indices, indices_count};

    for (int64_t i = 0, j = 0; i < indices_count;) {
        const int64_t batch_start = i;
        const int64_t batch_end   = stream_array::in_gather::PrefetchNext(indices_gather);
        const int64_t index_start = j;

        for (; i <= (batch_end - 3); i += 3, j++) {
            const uint8_t v0 = indices_gather[i + 0];
            const uint8_t v1 = indices_gather[i + 1];
            const uint8_t v2 = indices_gather[i + 2];

            std::cout << i << " - " << j << " - " << batch_start << " - " << batch_end << " - " << index_start << " - "
                      << static_cast<uint32_t>(v0) << std::endl;
            std::cout << i << " - " << j << " - " << batch_start << " - " << batch_end << " - " << index_start << " - "
                      << static_cast<uint32_t>(v1) << std::endl;
            std::cout << i << " - " << j << " - " << batch_start << " - " << batch_end << " - " << index_start << " - "
                      << static_cast<uint32_t>(v2) << std::endl;
        }
    }

    ::free(indices);
    ::free(vertices);
}

int main() {
    StreamInArraySequentialTest();
    StreamInArrayGatherTest();
    return 0;
}
