#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>

#define ALIGNTYPE16    __attribute__((aligned(16)))
#define ALIGNTYPE128   __attribute__((aligned(128)))
#define MAX_DMA_SIZE   (1 << 14)
#define ODS_ROUND16(x) ((x + 15) & ~15)

enum streamBufferType_t { SBT_DOUBLE = 2, SBT_QUAD = 4 };

#define CACHE_LINE_SIZE 128
#define ID_INLINE       inline

template <class T>
T Max(T x, T y) {
    return (x > y) ? x : y;
}
template <class T>
T Min(T x, T y) {
    return (x < y) ? x : y;
}

ID_INLINE void Prefetch(const void* ptr, int offset) {
}

ID_INLINE void ZeroCacheLine(void* ptr, int offset) {
    uint8_t* uint8_tPtr = (uint8_t*)((((uintptr_t)(ptr)) + (offset)) & ~(CACHE_LINE_SIZE - 1));
    memset(uint8_tPtr, 0, CACHE_LINE_SIZE);
}

ID_INLINE void FlushCacheLine(const void* ptr, int offset) {
}

template <typename _type_, int _entries_ = 8, int _associativity_ = 4, bool aligned = false>
class ALIGNTYPE128 idSoftwareCache {
  public:
    void Prefetch(const _type_* obj) {
        ::Prefetch(obj, 0);
    }
};

template <typename _type_>
class idODSObject {
  public:
    idODSObject(const _type_* obj)
      : objectPtr(obj) {
    }
    operator const _type_&() const {
        return *objectPtr;
    }
    const _type_* operator->() const {
        return objectPtr;
    }
    const _type_& Get() const {
        return *objectPtr;
    }
    const _type_* Ptr() const {
        return objectPtr;
    }
    const _type_* OriginalPtr() const {
        return objectPtr;
    }

  private:
    const _type_* objectPtr;
};

template <typename _type_, typename _cache_>
class idODSCachedObject {
  public:
    idODSCachedObject(const _type_* obj, _cache_& cache)
      : objectPtr(obj) {
    }
    operator const _type_&() const {
        return *objectPtr;
    }
    const _type_* operator->() const {
        return objectPtr;
    }
    const _type_& Get() const {
        return *objectPtr;
    }
    const _type_* Ptr() const {
        return objectPtr;
    }
    const _type_* OriginalPtr() const {
        return objectPtr;
    }

  private:
    const _type_* objectPtr;
};

template <typename _type_, int max>
class idODSArray {
  public:
    idODSArray(const _type_* array, int num)
      : arrayPtr(array)
      , arrayNum(num) {
        assert(num <= max);
        Prefetch(array, 0);
    }
    const _type_& operator[](int index) const {
        assert(index >= 0 && index < arrayNum);
        return arrayPtr[index];
    }
    const _type_* Ptr() const {
        return arrayPtr;
    }
    const int Num() const {
        return arrayNum;
    }

  private:
    const _type_* arrayPtr;
    int           arrayNum;
};

template <typename _elemType_, typename _indexType_, int max>
class idODSIndexedArray {
  public:
    idODSIndexedArray(const _elemType_* array, const _indexType_* index, int num)
      : arrayNum(num) {
        assert(num <= max);
        for (int i = 0; i < num; i++) {
            Prefetch(arrayPtr, abs(index[i]) * sizeof(_elemType_));
            arrayPtr[i] = array + abs(index[i]);
        }
    }
    const _elemType_& operator[](int index) const {
        assert(index >= 0 && index < arrayNum);
        return *arrayPtr[index];
    }
    void ReplicateUpToMultipleOfFour() {
        assert((max & 3) == 0);
        while ((arrayNum & 3) != 0) {
            arrayPtr[arrayNum++] = arrayPtr[0];
        }
    }

  private:
    const _elemType_* arrayPtr[max];
    int               arrayNum;
};

#define compile_time_assert(x)      static_assert(x, "Assertion failure")
#define CONST_ISPOWEROFTWO(x)       (((x) & ((x)-1)) == 0 && (x) > 0)
#define assert_16_byte_aligned(ptr) assert((((uintptr_t)(ptr)) & 15) == 0)

template <typename _type_, int _bufferSize_>
class ALIGNTYPE16 idODSStreamedOutputArray {
  public:
    idODSStreamedOutputArray(_type_* array, int* numElements, int maxElements)
      : localNum(0)
      , outArray(array)
      , outNum(numElements)
      , outMax(maxElements) {
        compile_time_assert(CONST_ISPOWEROFTWO(_bufferSize_));
        compile_time_assert(((_bufferSize_ * sizeof(_type_)) & 15) == 0);
        compile_time_assert(_bufferSize_ * sizeof(_type_) < MAX_DMA_SIZE);
        assert_16_byte_aligned(array);
    }
    ~idODSStreamedOutputArray() {
        *outNum = localNum;
    }

    int Num() const {
        return localNum;
    }
    void Append(_type_ element) {
        assert(localNum < outMax);
        outArray[localNum++] = element;
    }
    _type_& Alloc() {
        assert(localNum < outMax);
        return outArray[localNum++];
    }

  private:
    int     localNum;
    _type_* outArray;
    int*    outNum;
    int     outMax;
};

/*
================================================
idODSStreamedArray
================================================
*/
template <typename _type_, int _bufferSize_, streamBufferType_t _sbt_ = SBT_DOUBLE, int _roundUpToMultiple_ = 1>
class ALIGNTYPE16 idODSStreamedArray {
  public:
    idODSStreamedArray(const _type_* array, const int numElements)
      : cachedArrayStart(0)
      , cachedArrayEnd(0)
      , streamArrayEnd(0)
      , inArray(array)
      , inArrayNum(numElements)
      , inArrayNumRoundedUp(numElements) {
        compile_time_assert(CONST_ISPOWEROFTWO(_bufferSize_));
        compile_time_assert(((_bufferSize_ * sizeof(_type_)) & 15) == 0);
        compile_time_assert(_bufferSize_ * sizeof(_type_) < MAX_DMA_SIZE);
        compile_time_assert(_roundUpToMultiple_ >= 1);
        assert_16_byte_aligned(array);
        assert((uintptr_t)array > _bufferSize_ * sizeof(_type_));
        // Fetch the first batch of elements.
        FetchNextBatch();
        // Calculate the rounded up size here making the mod effectively for free because we have to wait
        // for memory access anyway while the above FetchNextBatch() does not need the rounded up size yet.
        inArrayNumRoundedUp += _roundUpToMultiple_ - 1;
        inArrayNumRoundedUp -= inArrayNumRoundedUp % ((_roundUpToMultiple_ > 1) ? _roundUpToMultiple_ : 1);
    }
    ~idODSStreamedArray() {
        // Flush the accessible part of the array.
        FlushArray(inArray, cachedArrayStart * sizeof(_type_), cachedArrayEnd * sizeof(_type_));
    }

    // Fetches a new batch of array elements and returns the first index after this new batch.
    // After calling this, the elements starting at the index returned by the previous call to
    // FetchNextBach() (or zero if not yet called) up to (excluding) the index returned by
    // this call to FetchNextBatch() can be accessed through the [] operator. When quad-buffering,
    // the elements starting at the index returned by the second-from-last call to FetchNextBatch()
    // can still be accessed. This is useful when the algorithm needs to successively access
    // an odd number of elements at the same time that may cross a single buffer boundary.
    int FetchNextBatch() {
        // If not everything has been streamed already.
        if (cachedArrayEnd < inArrayNum) {
            cachedArrayEnd   = streamArrayEnd;
            cachedArrayStart = Max(cachedArrayEnd - _bufferSize_ * (_sbt_ - 1), 0);

            // Flush the last batch of elements that is no longer accessible.
            FlushArray(inArray, (cachedArrayStart - _bufferSize_) * sizeof(_type_), cachedArrayStart * sizeof(_type_));

            // Prefetch the next batch of elements.
            if (streamArrayEnd < inArrayNum) {
                streamArrayEnd = Min(streamArrayEnd + _bufferSize_, inArrayNum);
                for (unsigned int offset = cachedArrayEnd * sizeof(_type_); offset < streamArrayEnd * sizeof(_type_);
                     offset += CACHE_LINE_SIZE) {
                    Prefetch(inArray, offset);
                }
            }
        }
        return (cachedArrayEnd == inArrayNum) ? inArrayNumRoundedUp : cachedArrayEnd;
    }

    // Provides access to the elements starting at the index returned by the next-to-last call
    // to FetchNextBach() (or zero if only called once so far) up to (excluding) the index
    // returned by the last call to FetchNextBatch(). When quad-buffering, the elements starting
    // at the index returned by the second-from-last call to FetchNextBatch() can still be accessed.
    // This is useful when the algorithm needs to successively access an odd number of elements
    // at the same time that may cross a single buffer boundary.
    const _type_& operator[](int index) const {
        assert((index >= cachedArrayStart && index < cachedArrayEnd) ||
               (cachedArrayEnd == inArrayNum && index >= inArrayNum && index < inArrayNumRoundedUp));
        if (_roundUpToMultiple_ > 1) {
            index &= (index - inArrayNum) >> 31;
        }
        return inArray[index];
    }

  private:
    int           cachedArrayStart;
    int           cachedArrayEnd;
    int           streamArrayEnd;
    const _type_* inArray;
    int           inArrayNum;
    int           inArrayNumRoundedUp;

    static void FlushArray(const void* flushArray, int flushStart, int flushEnd) {
#if 0
		// arrayFlushBase is rounded up so we do not flush anything before the array.
		// arrayFlushStart is rounded down so we start right after the last cache line that was previously flushed.
		// arrayFlushEnd is rounded down so we do not flush a cache line that holds data that may still be partially
		// accessible or a cache line that stretches beyond the end of the array.
		const uintptr_t arrayAddress = ( uintptr_t )flushArray;
		const uintptr_t arrayFlushBase = ( arrayAddress + CACHE_LINE_SIZE - 1 ) & ~( CACHE_LINE_SIZE - 1 );
		const uintptr_t arrayFlushStart = ( arrayAddress + flushStart ) & ~( CACHE_LINE_SIZE - 1 );
		const uintptr_t arrayFlushEnd = ( arrayAddress + flushEnd ) & ~( CACHE_LINE_SIZE - 1 );
		for( uintptr_t offset = Max( arrayFlushBase, arrayFlushStart ); offset < arrayFlushEnd; offset += CACHE_LINE_SIZE )
		{
			FlushCacheLine( flushArray, offset - arrayAddress );
		}
#endif
    }
};

/*
================================================
idODSStreamedIndexedArray

For gathering elements from an array using a sequentially read index.
This uses overlapped streaming for both the index and the array elements
where one batch of indices and/or array elements can be accessed while
the next batch is being streamed in.

NOTE: currently the size of array elements must be a multiple of 16 uint8_ts.
An index with offsets and more complex logic is needed to support other sizes.
================================================
*/
template <typename _elemType_, typename _indexType_, int _bufferSize_, streamBufferType_t _sbt_ = SBT_DOUBLE, int _roundUpToMultiple_ = 1>
class ALIGNTYPE16 idODSStreamedIndexedArray {
  public:
    idODSStreamedIndexedArray(const _elemType_* array, const int numElements, const _indexType_* index, const int numIndices)
      : cachedArrayStart(0)
      , cachedArrayEnd(0)
      , streamArrayEnd(0)
      , cachedIndexStart(0)
      , cachedIndexEnd(0)
      , streamIndexEnd(0)
      , inArray(array)
      , inArrayNum(numElements)
      , inIndex(index)
      , inIndexNum(numIndices)
      , inIndexNumRoundedUp(numIndices) {
        compile_time_assert(CONST_ISPOWEROFTWO(_bufferSize_));
        compile_time_assert(((_bufferSize_ * sizeof(_indexType_)) & 15) == 0);
        compile_time_assert(_bufferSize_ * sizeof(_indexType_) < MAX_DMA_SIZE);
        compile_time_assert(_bufferSize_ * sizeof(_elemType_) < MAX_DMA_SIZE);
        compile_time_assert((sizeof(_elemType_) & 15) == 0); // to avoid complexity due to cellDmaListGet
        compile_time_assert(_roundUpToMultiple_ >= 1);
        assert_16_byte_aligned(index);
        assert_16_byte_aligned(array);
        assert((uintptr_t)index > _bufferSize_ * sizeof(_indexType_));
        assert((uintptr_t)array > _bufferSize_ * sizeof(_elemType_));
        // Fetch the first batch of indices.
        FetchNextBatch();
        // Fetch the first batch of elements and the next batch of indices.
        FetchNextBatch();
        // Calculate the rounded up size here making the mod effectively for free because we have to wait
        // for memory access anyway while the above FetchNextBatch() do not need the rounded up size yet.
        inIndexNumRoundedUp += _roundUpToMultiple_ - 1;
        inIndexNumRoundedUp -= inIndexNumRoundedUp % ((_roundUpToMultiple_ > 1) ? _roundUpToMultiple_ : 1);
    }
    ~idODSStreamedIndexedArray() {
        // Flush the accessible part of the index.
        FlushArray(inIndex, cachedIndexStart * sizeof(_indexType_), cachedIndexEnd * sizeof(_indexType_));
        // Flush the accessible part of the array.
        FlushArray(inArray, cachedArrayStart * sizeof(_elemType_), cachedArrayEnd * sizeof(_elemType_));
    }

    // Fetches a new batch of array elements and returns the first index after this new batch.
    // After calling this, the elements starting at the index returned by the previous call to
    // FetchNextBach() (or zero if not yet called) up to (excluding) the index returned by
    // this call to FetchNextBatch() can be accessed through the [] operator. When quad-buffering,
    // the elements starting at the index returned by the second-from-last call to FetchNextBatch()
    // can still be accessed. This is useful when the algorithm needs to successively access
    // an odd number of elements at the same time that may cross a single buffer boundary.
    int FetchNextBatch() {
        // If not everything has been streamed already.
        if (cachedArrayEnd < inIndexNum) {
            if (streamIndexEnd > 0) {
                cachedArrayEnd   = streamArrayEnd;
                cachedArrayStart = Max(cachedArrayEnd - _bufferSize_ * (_sbt_ - 1), 0);
                cachedIndexEnd   = streamIndexEnd;
                cachedIndexStart = Max(cachedIndexEnd - _bufferSize_ * (_sbt_ - 1), 0);

                // Flush the last batch of indices that are no longer accessible.
                FlushArray(inIndex, (cachedIndexStart - _bufferSize_) * sizeof(_indexType_), cachedIndexStart * sizeof(_indexType_));
                // Flush the last batch of elements that is no longer accessible.
                FlushArray(inArray, (cachedArrayStart - _bufferSize_) * sizeof(_elemType_), cachedArrayStart * sizeof(_elemType_));

                // Prefetch the next batch of elements.
                if (streamArrayEnd < inIndexNum) {
                    streamArrayEnd = cachedIndexEnd;
                    for (int i = cachedArrayEnd; i < streamArrayEnd; i++) {
                        assert(i >= cachedIndexStart && i < cachedIndexEnd);
                        assert(inIndex[i] >= 0 && inIndex[i] < inArrayNum);

                        Prefetch(inArray, inIndex[i] * sizeof(_elemType_));
                    }
                }
            }

            // Prefetch the next batch of indices.
            if (streamIndexEnd < inIndexNum) {
                streamIndexEnd = Min(streamIndexEnd + _bufferSize_, inIndexNum);
                for (unsigned int offset = cachedIndexEnd * sizeof(_indexType_); offset < streamIndexEnd * sizeof(_indexType_);
                     offset += CACHE_LINE_SIZE) {
                    Prefetch(inIndex, offset);
                }
            }
        }
        return (cachedArrayEnd == inIndexNum) ? inIndexNumRoundedUp : cachedArrayEnd;
    }

    // Provides access to the elements starting at the index returned by the next-to-last call
    // to FetchNextBach() (or zero if only called once so far) up to (excluding) the index
    // returned by the last call to FetchNextBatch(). When quad-buffering, the elements starting
    // at the index returned by the second-from-last call to FetchNextBatch() can still be accessed.
    // This is useful when the algorithm needs to successively access an odd number of elements
    // at the same time that may cross a single buffer boundary.
    const _elemType_& operator[](int index) const {
        assert((index >= cachedArrayStart && index < cachedArrayEnd) ||
               (cachedArrayEnd == inIndexNum && index >= inIndexNum && index < inIndexNumRoundedUp));
        if (_roundUpToMultiple_ > 1) {
            index &= (index - inIndexNum) >> 31;
        }
        return inArray[inIndex[index]];
    }

  private:
    int                cachedArrayStart;
    int                cachedArrayEnd;
    int                streamArrayEnd;
    int                cachedIndexStart;
    int                cachedIndexEnd;
    int                streamIndexEnd;
    const _elemType_*  inArray;
    int                inArrayNum;
    const _indexType_* inIndex;
    int                inIndexNum;
    int                inIndexNumRoundedUp;

    static void FlushArray(const void* flushArray, int flushStart, int flushEnd) {
#if 0
		// arrayFlushBase is rounded up so we do not flush anything before the array.
		// arrayFlushStart is rounded down so we start right after the last cache line that was previously flushed.
		// arrayFlushEnd is rounded down so we do not flush a cache line that holds data that may still be partially
		// accessible or a cache line that stretches beyond the end of the array.
		const uintptr_t arrayAddress = ( uintptr_t )flushArray;
		const uintptr_t arrayFlushBase = ( arrayAddress + CACHE_LINE_SIZE - 1 ) & ~( CACHE_LINE_SIZE - 1 );
		const uintptr_t arrayFlushStart = ( arrayAddress + flushStart ) & ~( CACHE_LINE_SIZE - 1 );
		const uintptr_t arrayFlushEnd = ( arrayAddress + flushEnd ) & ~( CACHE_LINE_SIZE - 1 );
		for( uintptr_t offset = Max( arrayFlushBase, arrayFlushStart ); offset < arrayFlushEnd; offset += CACHE_LINE_SIZE )
		{
			FlushCacheLine( flushArray, offset - arrayAddress );
		}
#endif
    }
};

void StreamInArraySequentialTest() {
    constexpr int64_t index_count = 32;
    uint8_t*          indices     = static_cast<uint8_t*>(::malloc(index_count * sizeof(uint8_t)));

    for (int64_t index = 0; index < index_count; index++) {
        indices[index] = index;
    }

    idODSStreamedArray<uint8_t, 16, SBT_DOUBLE, 1> indices_sequential {indices, index_count};

    for (int64_t index = 0; index < index_count;) {
        const int64_t next_index = indices_sequential.FetchNextBatch() - 4;
        for (; index <= next_index; index += 4) {
            const int64_t i0 = indices_sequential[index + 0];
            const int64_t i1 = indices_sequential[index + 1];
            const int64_t i2 = indices_sequential[index + 2];
            const int64_t i3 = indices_sequential[index + 3];

            std::cout << " - " << i0 << ", " << i1 << ", " << i2 << ", " << i3 << std::endl;

            assert(i0 == (index + 0));
            assert(i1 == (index + 1));
            assert(i2 == (index + 2));
            assert(i3 == (index + 3));
        }
    }

    ::free(indices);
}

struct Vertex {
    float x;
    float y;
    float z;
    float w;
};

void StreamInArrayGatherTest() {
    constexpr int64_t vertices_count = 8;
    Vertex*           vertices       = static_cast<Vertex*>(::malloc(vertices_count * sizeof(Vertex)));

    constexpr int64_t indices_count = 12;
    uint8_t*          indices       = static_cast<uint8_t*>(::malloc(indices_count * sizeof(uint8_t)));

    vertices[0].x = 10;
    vertices[1].x = 20;
    vertices[2].x = 30;
    vertices[3].x = 40;

    vertices[4].x = 50;
    vertices[5].x = 60;
    vertices[6].x = 70;
    vertices[7].x = 80;

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;

    indices[6]  = 4;
    indices[7]  = 5;
    indices[8]  = 6;
    indices[9]  = 6;
    indices[10] = 7;
    indices[11] = 4;

    idODSStreamedIndexedArray<Vertex, uint8_t, 16, SBT_DOUBLE> indices_gather {vertices, vertices_count, indices, indices_count};

    for (int64_t i = 0, j = 0; i < indices_count;) {
        const int64_t batch_start = i;
        const int64_t batch_end   = indices_gather.FetchNextBatch();
        const int64_t index_start = j;

        for (; i <= (batch_end - 3); i += 3, j++) {
            const float v0 = indices_gather[i + 0].x;
            const float v1 = indices_gather[i + 1].x;
            const float v2 = indices_gather[i + 2].x;

            std::cout << " - " << i << " - " << j << " - " << batch_start << " - " << batch_end << " - " << index_start << " - "
                      << static_cast<uint32_t>(v0) << std::endl;
            std::cout << " - " << i << " - " << j << " - " << batch_start << " - " << batch_end << " - " << index_start << " - "
                      << static_cast<uint32_t>(v1) << std::endl;
            std::cout << " - " << i << " - " << j << " - " << batch_start << " - " << batch_end << " - " << index_start << " - "
                      << static_cast<uint32_t>(v2) << std::endl;
        }
    }

    ::free(indices);
    ::free(vertices);
}

int main() {
    std::cout << "==================================================" << std::endl;
    std::cout << "Stream-In Array (Sequential):" << std::endl;
    StreamInArraySequentialTest();
    std::cout << "==================================================" << std::endl;

    std::cout << std::endl;

    std::cout << "==================================================" << std::endl;
    std::cout << "Stream-In Array (Gather):" << std::endl;
    StreamInArrayGatherTest();
    std::cout << "==================================================" << std::endl;

    return 0;
}
